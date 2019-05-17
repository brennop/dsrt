// ------------------------------------
// 
//  DSRT Game - APC Turma D  - 2019.1
//  Brenno Cordeiro - 180098632
// 
// ------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

// pr�totipo de fun��es �teis
int input();
int create();
int mainGame();
int riddle();
int riddleInput();
int jokenpo();
int arrow();

int main(){
    // faz os acentos funcionarem
    setlocale(LC_ALL, "");

    // coloca a seed pro prng
    srand(time(NULL));

    // declara e inicializa as vari�veis
    // personagem e op��o no menu principal
    int character = 0, opt = 0;

    // splash art
    printf("\
     .    _    +     .  ______   .          .     '      .\n\
  (      /|\\      _   _|      \\___   .   +    '    .         *\n\
    /\\  ||||| .  | | |   | |      |       .    '                    .    '\n\
 __||||_|||||____| |_|_____________\\________________________________________\n\
 . |||| |||||  /\\   _____      _____  . ______   _______  _______ _________\n\
  . \\|`-'|||| ||||    __________       (. __  \\ ( -____ \\(  ____.)\\__ . __/ \n\
     \\__ |||| ||||      .          .   | (  \\  )| (    \\/| (    )|   ) (  \n\
  __    ||||`-'|||  .       .    ______|_|_. ) || (_____ | (____)| . | | ,\n\
 .    . |||| ___/  ___________     .   |-|   | |(_____  )|     __)   | | \n\
 _   ___|||||__  _           .    -    | | - ) |.  -  ) || (\\ (  .   | | .\n\
      _ `---'    .   .    .   _   .   .| (__/  )/\\____) || ) \\ \\__ - | |\n\
 _  ^      .  -    .    -    .       - (______/ \\_______)|/ . \\__/.  )_(\n\
 ");

    // Loop do menu principal
    while(opt != 3){
        printf("\n1 - Criar Personagem\n2 - Novo Jogo\n3 - Sair\n");

        opt = input("", 3);
        
        if(opt == 1){
            character = create();
        }else if(opt == 2){
            if(character == 0){
                printf("Precisa criar um personagem primeiro!");
            }else{
                mainGame(character);
            }
        }
    }

    return 0;
}


// Fun��o para pegar um input de op��es
int input(char txt[], int opts){
    int chosen = 0;
    while(chosen > opts || chosen <= 0){
        printf("%s: ", txt);
        scanf("%d", &chosen);
        printf("\n");
    }
    return chosen;
}


// Fun��o para criar o personagem
// Retorna um inteiro, a cada dois bits � um atributo
int create(){
    int character = 0, current_attr = 0 ;
    printf("Criar personagem\n");

    // Ra�a: dois primeiros bits
    printf("Ra�a\n");
    current_attr = input("( Humano | An�o | Elfo )", 3);
    character += current_attr;

    // Alinhamento: bits 3 e 4 (shift 2)
    printf("Alinhamento\n");
    current_attr = input("( Mal | Neutro | Bom )", 3);
    character += current_attr * 4;

    // Profiss�o: bits 5 e 6 (shift 4)
    printf("Profiss�o\n");

    // Se for bom, n�o pode ser ladino
    if((character >> 2 & 3) == 3){
        current_attr = input("( Guerreiro | Mago )", 2);
    }else{
        current_attr = input("( Guerreiro | Mago | Ladino )", 3);
    }
    character += current_attr * 16;

    // Meta: bits 7 e 8 (shift 6)
    printf("Meta\n");
    // Se for mal, n�o pode destruir o mal
    if((character >> 2 & 1) == 1){
        current_attr = input("( Governar o reino | Ficar rico )", 2);
    }else{
        current_attr = input("( Governar o reino | Ficar rico | Destruir o mal )", 3);
    }
    character += current_attr * 64;

    // Meio: bits 9 e 10 (shift 8)
    printf("Meio que vive\n");

    // Se for ladino, n�o pode ser tribal
    if((character >> 4 & 3) == 3){
        current_attr = input("( Urbano | Rural )", 2);
    }else{
        current_attr = input("( Urbano | Rural | Tribal )", 3);
    }
    character += current_attr * 256;

    // Porte: bits 11 e 12 (shift 10)
    printf("Porte\n");
    
    // Se for an�o, n�o pode ser grande
    if((character & 2) == 2){
        current_attr = input("( M�dio | Pequeno )", 2) + 1;
    }else{
        current_attr = input("( Grande | M�dio | Pequeno )", 3);
    }
    character += current_attr * 1024;

    printf("Personagem criado!");
    return character;
}

// Jogo
int mainGame(int character){
    // Declara as vari�veis do personagem
    int raca, alinhamento, profissao, meta, meio, porte;

    // Transforma o inteiro character nas vari�veis representantes
    raca = character & 3;
    alinhamento = character >> 2 & 3;
    profissao = character >> 4 & 3;
    meta = character >> 6 & 3;
    meio = character >> 8 & 3;
    porte = character >> 10 & 3;

    // vari�veis helpers para conduzir a narrativa
    int jar, door, oldMan;
    int hasKey = 0, doorPassed = 0, jokenpoPlayed = 0;
    int r=0, riddle1=0, riddle2=0;

    // Introdu��o
    printf("Seus tornozelos querem desistir. H� dias voc� vem andando pelo deserto. A fome e a sede j� s�o personagens conhecidos.\n\
Ap�s mais alguns passos voc� encontra uma jarra. Voc� levanta a jarra e percebe h� algo dentro.\n");
    jar = input("( beber | lavar as m�os | carregar a jarra )", 3);

    if(jar == 1){
        printf("O l�quido come�a a ser derramado sobre a sua boca, e imediatamente voc� sente algo queimando em sua garganta. Voc� para logo em seguida.\n");
    }else if(jar == 2){
        if(profissao != 2){
            printf("O l�quido come�a a ser derramado sobre as suas m�os, que come�am a arder. Apesar da dor voc� se sente mais forte.\n");
        }else{
            printf("O l�quido come�a a ser derramado sobre as suas m�os. Voc� sente a magia correndo de volta em suas veias.\n");
        }
    }else{
        printf("Uma jarra cheia foi adicionada ao seu invent�rio.\n");
    }

    // Evento 2 - Encontro com o velho
    // Volta a esse evento se n�o passar pela porta
    while(doorPassed == 0){
        printf("Voc� segue andando pelo deserto e avista uma figura. Ao se aproximar, percebe que � um velho � beira da morte.\n");

        // Se for mal, pode saquear o velho, mas n�o oferecer ajuda
        if(alinhamento == 1){
            oldMan = input("( saquear o velho | conversar com o velho )", 2);
        }else{
            // Se possui a jarra
            if(jar == 3){
                oldMan = input("(conversar com o velho | oferecer ajuda ao velho | oferecer a jarra ao velho )", 3) + 1;
            }else{
                oldMan = input("(conversar com o velho | oferecer ajuda ao velho )", 2) + 1;
            }
        }
        
        // Saquear
        if(oldMan == 1){
            // Se for Ladino
            if(profissao == 3){
                printf("N�o h� resist�ncia quando se abaixa para olhar os bolsos do velho.\n");
                printf("Uma chave dourada foi adicionada ao seu invent�rio.\n");
                hasKey = 1;
            }else{
                printf("Voc� vasculha os bolsos do velho procurando algo, mas n�o h� nada.\n");
            }
        }else if(oldMan == 2){ // Conversar
            // Ladino
            if(profissao == 3){
                printf("\"Voc� tem algo que possa me ajudar\?\"\n");
                printf("O velho te entrega uma chave, sem dizer nada.\n");
                printf("Uma chave dourada foi adicionada ao seu invent�rio.\n");
                hasKey = 1;
            }  else{
                if(jokenpoPlayed){
                    printf("\"Como eu passo da porta?\"\n");
                    printf("\"O velho vira e diz para voc�\"\n");
                    printf("\"Com paci�ncia\"\n");
                }else{
                    printf("\"Quem � voc�?\"\n");
                    printf("O velho olha para o horizonte e responde com dificuldade.\n");
                    printf("\"Eu sou como voc�.\"\n");
                }
            }
        }else if(oldMan == 3){ // Ajuda
            if(jokenpoPlayed){
                printf("\"O senhor precisa de ajuda?\"\n");
                printf("O velho olha para voc� e responde:\n");
                printf("\"Acho que quem precisa de ajuda � voc�.\"\n");
            }else{
                printf("\"O senhor precisa de ajuda?\"\n");
                printf("O velho olha para o horizonte e responde com dificuldade.\ns");
                printf("\"N�o adianta. J� estamos condenados.\"\n");
            }
        }else{
            printf("O velho parece grato com o presente.\n");
            printf("Em troca ele te entrega uma chave.\n");
            printf("Uma chave dourada foi adicionada ao seu invent�rio.\n");

            hasKey = 1;
            jar = 0;
        }
        
        // Evento 3        
        printf("\n");
        printf("Voc� segue caminhando. Alguns metros a frente voc� parece identificar uma estrutura\n");
        printf("Quando se aproxima, nota uma porta de pedra.\n");
        
        // se for guerreiro, pode golpear a porta
        if(profissao == 1){
            door = input("( bater na porta | pedir ajuda ao velho | golpear a porta )", 3);
        } else if(profissao == 2){ // se for mago, pode usar magia
            door = input("( bater na porta | pedir ajuda ao velho | usar magia )", 3);
        } else{
            if(hasKey){
                door = input("( bater na porta | pedir ajuda ao velho | usar a chave )", 3);
            }else{
                door = input("( bater na porta | pedir ajuda ao velho )", 2);
            }
        }

        // bater na porta
        if(door == 1){
            printf("Knock, Knock...\n");
            doorPassed = jokenpo();
            jokenpoPlayed = 1;
        }else if(door == 3 && profissao == 1){ // golpear a porta
            printf("Com a espada empunhada, voc� golpeia a porta.\n");
            if(jar == 2){ // derramou a jarra
                printf("A porta se despeda�a e voc� descobre uma escadaria\n");
                doorPassed = 2;
            }else{ // n�o derramou a jarra
                doorPassed = jokenpo();
                jokenpoPlayed = 1;
            }
        }else if(door == 3 && profissao == 2){ // usar magia
            printf("\"Bez Organicheniy\", voc� diz olhando para a porta\n");
            if(jar == 2){ // derramou a jarra
                printf("A porta se abre e revela uma escadaria escura\n");
                doorPassed = 2;
            }else{ // n�o derramou a jarra
                doorPassed = jokenpo();
                jokenpoPlayed = 1;
            }
        }else if(door == 3 && profissao == 3){ // usar a chave
            printf("A porta se abre ao inserir a chave na fechadura, e revela uma escadaria escura.\n");
            doorPassed = 2;
        }
    }

    // Evento 4
    printf("\n");
    printf("Rapidamente voc� desce os degraus e chega a uma sala retangular.\n");
    if(doorPassed == 2){ // se usou a chave, precisa jogar o "jokenpo" dos ejetores
        if(arrow() == 0){ // se perdeu o minigame
            printf("Voc� come�a a sentir o veneno correndo por todo o seu corpo. � o fim de sua jornada\nGAME OVER!\n");
            return 0;
        };
    }



    // Evento 5
    printf("H� um al�ap�o perto dos seus p�s mas est� trancado.\n");
    printf("Voc� se abaixa e utiliza a chave para abrir.\n");
    printf("Ap�s descer mais alguns lances de escada, voc� se encontra em uma grande sala oval.\n");
    printf("H� uma figura no centro, uma est�tua talvez.\n");

    printf("Voc� da alguns passos � frente, na dire��o da est�tua.\n");
    printf("A est�tua diz: \n");
    printf("Para passar e receber o tesouro, voc� deve responder corretamente tr�s charadas.\n");

    // tr�s charadas
    for(int i = 0; i<3; i++){
        // loop para garantir que as charadas n�o sejam repetidas
        while(r == riddle1 || r == riddle2){
            r = (rand() % 10) + 1;
        }

        // salva a charada 1
        if(i==0){
            riddle1 = r;
        }else{ // salva a charada 2
            riddle2 = r;
        }

        // se errar uma charada duas vezes
        if(riddle(r) == 0){
            printf("O ch�o come�a a tremer. O teto come�a a desmoronar. � o fim de sua jornada\nGAME OVER!\n");
            return 0;
        }
    }
    
    // Fim do jogo
    printf("A est�tua se despeda�a, e debaixo dela h� um ba�. Sua jornada chegou ao fim.\n");
    return 0;

}

// minigame jokenpo
int jokenpo(){
    // declara as variaveis, jogada | random | wins | losses
    int j, r, w=0, l=0;

    printf("Estranhos glifos come�am a aparecer na porta. Voc� reconhece alguns. \nParece que a porta quer jogar jokenp�.\n");
    // melhor de tr�s
    while(w < 2 && l < 2){ 
        j = input("( pedra | papel | tesoura )", 3);

        r = rand() % 3;
        if(r == 0){
            printf("A porta mostra um glifo semelhante a uma m�o fechada\n");
        }else if(r == 1){
            printf("A porta mostra um glifo semelhante a uma m�o aberta\n");
        }else{
            printf("A porta mostra um glifo semelhante a um sinal de paz e amor\n");
        }

        // pedra < papel < tesoura
        if((j - r) % 3 == 2){
            printf("Voc� ganhou essa.\n");
            w++;
        }else if(j-1 == r){
            printf("Empate\n");
        }else{
            printf("Voc� perdeu dessa vez\n");
            l++;
        }
    }

    // perdeu o jokenpo
    if(l == 2){
        printf("A porta n�o tem rosto, mas voc� sente que ela est� feliz em ter ganhado.\n");
        return 0;
    }
    // ganhou o jokenpo
    else{
        printf("A porta se abre e revela uma escadaria subterr�nea.\n");
        printf("Antes de descer voc� percebe algo brilhando em cima do portal.\n");
        printf("Uma chave prateada foi adicionada ao seu invent�rio\n");
        return 1;
    }
}

int arrow(){
    // declara as variaveis, jogada | random | wins | losses
    int j, r, w=0, l=0;

    printf("A parede oposta cont�m 3 buracos alinhados horizontalmente.\n");
    printf("Voc� acredita que podem ser uma armadilha.\n");
    while(w < 2 && l <2){
        j = input("( ficar � direita | ficar no meio | ficar � esquerda )", 3);
        r = rand() % 3;

        if((j - r) % 3 == 2){
            printf("Do ejetor diretamente a sua frente sai um fragmento de chave.\n");
            w++;
        }else if(j-1 == r){
            printf("O ejetor diretamente a sua frente n�o � ativado.\n");
        }else{
            printf("Do ejetor diretamente � sua frente sai uma flecha envenada.\n");
            l++;
        }
    }

    // ganhou
    if(w == 2){ 
        input("( ficar � direita | ficar no meio | ficar � esquerda )", 3);
        printf("Voc� se move, mas � in�til. Com os fragmentos de chave em m�o, a sala parece saber que voc� venceu.\n");
        printf("Uma chave prateada foi adicionada ao seu invent�rio\n");
        return 1;    
    }else{ // perdeu / morreu
        return 0;
    }   
}

// Charadas
int riddle(int n){
    switch (n)
    {
        case 1:
            printf("Quatro irm�s est�o em um quarto: Ana est� lendo, K�tia est� jogando xadrez, Taca est� cozinhando. O que a quarta irm� est� fazendo?\n");
            return riddleInput("( matando orcs | forjando uma espada | jogando xadrez )", 3);
        case 2:
            printf("Um homem estava indo para a Bahia com suas 5 irm�s. Cada irm� carregava 5 caixas, cada caixa tinha 5 gatos, cada gato estava com 5 filhotes. Quantos estavam indo para a Bahia?\n");
            return riddleInput("( 756 | 781 |  Bahia? )", 1);
        case 3:
            printf("Voc� entra em uma sala escura. No quarto h� uma estufa � g�s, uma lumin�ria de querosene e uma vela. H� uma caixa de f�sforo com um s� f�sforo em seu bolso. O que voc� acende primeiro.\n");
            return riddleInput("( lumin�ria | vela | f�sforo )", 3);
        case 4:
            printf("Um empres�rio comprou um cavalo de 10 moedas e vendeu por 20. Logo comprou o mesmo cavalo por 30 moedas e vendeu por 40. Qual � o lucro total do empres�rio nessas duas transa��es?\n");
            return riddleInput("( 10 | 20 | 40 )", 2);
        case 5:
            printf("Um bal�o aerost�tico � levado por uma corrente de ar at� o sul. Em que dire��o v�o ondular as bandeiras da cesta?\n");
            return riddleInput("( sul | nenhuma | norte )", 2);
        case 6:
            printf("Um homem roubou 80 moedas da caixa de um mercante. Mais tarde, usou 60 moedas para comprar uma espada do mercante, usando as moedas que roubou. Qual foi o preju�zo do mercante?\n");
            return riddleInput("( 80 | 20 | 140 )", 1);
        case 7:
            printf("Dois pais e dois filhos sentaram-se para comer ovos no caf� da manh�. Cada um comeu um ovo. Quantos ovos eles comeram no total?\n");
            return riddleInput("( 1 | 3 | 5 )", 2);
        case 8:
            printf("Se 3 lenhadores derrubam 3 �rvores a cada 3 horas, quanto tempo levar�o 100 lenhadores para derrubarem 100 �rvores?\n");
            return riddleInput("( 100 | 3 | 300 )", 2);
        case 9:
            printf("Voc� est� diante de tr�s portas. Na primeira h� um assassino. Na segunda h� um le�o que n�o come h� um ano. Na terceira h� um inc�ndio. Qual porta � mais segura?\n");
            return riddleInput("( assassino | le�o | inc�ndio )", 2);
        case 10:
            printf("H� tr�s ba�s, um contendo 100 moedas de ouro, um contendo 100 moedas de prata, e um contendo 50/50. Os r�tulos est�o trocados, por�m. Voc� pode tirar uma moeda de um dos ba�s para identificar qual ba� cont�m apenas moedas de ouro. De qual ba� voc� retira a moeda?\n");
            return riddleInput("( s� ouro | s� prata | 50/50 )", 3);
    }
}

// Input das Charadas
int riddleInput(char txt[], int answer){
    // se errar a resposta, mais uma chance
    if(input(txt,3) != answer){
        printf("Resposta incorreta. Tente mais uma vez.\n");
        return input(txt,3) == answer;
    }else{
        return 1;
    }
}