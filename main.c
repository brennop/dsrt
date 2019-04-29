// ------------------------------------
// 
//  Teres Game - APC Turma D  - 2019.1
// 
// -------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// terminal coloridinho
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RST "\x1B[0m"

// outros efeitos top
#define BLD "\x1B[1m"
#define ITL "\x1B[3m"
#define UND "\x1B[4m"

int input(char txt[], int opts){
    int chosen = 0;
    while(chosen > opts || chosen <= 0){
        printf("\n");
        printf("%s", txt);
        printf("\n");
        scanf("%d", &chosen);
        printf("\n");
    }
    return chosen;
}

int jokenpo();
int arrow();

unsigned int create(){
    unsigned int character = 0, current_attr = 0 ;
    printf("Criar personagem\n");

    // Raça: dois primeiros bits
    printf("Raça\n");
    current_attr = input(" 1 - Humano | 2 - Anão | 3 - Elfo", 3);
    character += current_attr;

    // Alinhamento: bits 3 e 4 (shift 2)
    printf("Alinhamento\n");
    current_attr = input(" 1 - Mal | 2 - Neutro | 3 - Bom", 3);
    character += current_attr * 4;

    // Profissão: bits 5 e 6 (shift 4)
    printf("Profissão\n");

    // Se for bom
    if((character >> 2 & 3) == 3){
        current_attr = input("1 - Guerreiro | 2 - Mago", 2);
    }else{
        current_attr = input("1 - Guerreiro | 2 - Mago | 3 - Ladino", 3);
    }
    character += current_attr * 16;

    // Meta: bits 7 e 8 (shift 6)
    printf("Meta\n");
    if((character >> 2 & 1) == 1){
        current_attr = input("1 - Governar o reino | 2 - Ficar rico", 2);
    }else{
        current_attr = input("1 - Governar o reino | 2 - Ficar rico | 3 - Destruir o mal", 3);
    }
    
    character += current_attr * 64;

    // Meio: bits 9 e 10 (shift 8)
    printf("Meio que vive\n");

    // Se for ladino
    if((character >> 4 & 3) == 3){
        current_attr = input("1 - Urbano | 2 - Rural", 2);
    }else{
        current_attr = input("1 - Urbano | 2 - Rural | 3 - Tribal", 3);
    }
    character += current_attr * 256;

    // Porte: bits 11 e 12 (shift 10)
    printf("Porte\n");
    
    // Se for anão
    if((character & 2) == 2){
        current_attr = input("1 - Médio | 2 - Pequeno", 2) + 1;
    }else{
        current_attr = input("1 - Grande | 2 - Médio | 3 - Pequeno", 3);
    }
    character += current_attr * 1024;

    return character;


}


int main(){
    int raca, alinhamento, profissao, meta, meio, porte;
    unsigned int character = create();
    printf("Personagem criado.\nPressione enter para começar\n");
    scanf("");

    raca = character & 3;
    alinhamento = character >> 2 & 3;
    profissao = character >> 4 & 3;
    meta = character >> 6 & 3;
    meio = character >> 8 & 3;
    porte = character >> 10 & 3;

    int jar, door, oldMan;
    int hasKey = 0, doorPassed = 0;

    // Introdução
    printf("Seus tornozelos querem desistir. Há dias você vem andando pelo deserto. A fome e a sede já são personagens conhecidos.\n\
Após mais alguns passos você encontra uma jarra. Você levanta a jarra e percebe há algo dentro.\n");
    jar = input("( beber | lavar as mãos | carregar a jarra )", 3);

    if(jar == 1){
        printf("O líquido começa a ser derramado sobre a sua boca, e imediatamente você sente algo queimando em sua garganta. Você para logo em seguida.\n");
    }else if(jar == 2){
        if(profissao != 2){
            printf("O líquido começa a ser derramado sobre as suas mãos, que começam a arder. Apesar da dor você se sente mais forte.\n");
        }else{
            printf("O líquido começa a ser derramado sobre as suas mãos. Você sente a magia correndo de volta em suas veias.\n");
        }
    }else{
        printf(ITL "Uma jarra cheia foi adicionada ao seu inventário.\n" RST);
    }

    // Evento 2 - Encontro com o velho

    while(doorPassed == 0){
        printf("Você segue andando pelo deserto e avista uma figura. Ao se aproximar, percebe que é um " BLU "velho" RST " à beira da morte.\n");

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
            // Ladino
            if(profissao == 3){
                printf("Não há resistência quando se abaixa para olhar os bolsos do velho.\n");
                printf(ITL "Uma chave dourada foi adicionada ao seu inventário.\n" RST);
                hasKey = 1;
            }else{
                printf("Você vasculha os bolsos do velho procurando algo, mas não há nada.\n");
            }
        }else if(oldMan == 2){ // Conversar
            // Ladino
            if(profissao == 3){
                printf(ITL "\"Você tem algo que possa me ajudar\?\"\n" RST);
                printf("O velho te entrega uma chave, sem dizer nada.\n");
                printf(ITL "Uma chave dourada foi adicionada ao seu inventário.\n" RST);
                hasKey = 1;
            }  else{
                printf("\"Quem é você?\"\n");
                printf("O velho olha para o horizonte e responde com dificuldade.\n");
                printf(ITL"\"Eu sou como você.\"\n"RST);
            }
        }else if(oldMan == 3){ // Ajuda
            printf("\"O senhor precisa de ajuda?\"\n");
            printf("O velho olha para o horizonte e responde com dificuldade.");
            printf("\"Não adianta. Já estamos condenados.\"\n");
        }else{
            // TODO
        }
        
        // Evento 3

        printf("\n");
        printf("Você segue caminhando. Alguns metros a frente você parece identificar uma estrutura\n");
        printf("Quando se aproxima, nota uma " YEL "porta de pedra" RST ".\n");
        
        if(profissao == 1){
            door = input("( bater na porta | pedir ajuda ao velho |" RED " golpear a porta" RST " )", 3);
        } else if(profissao == 2){
            door = input("( bater na porta | pedir ajuda ao velho |" RED " usar magia" RST " )", 3);
        } else{
            if(hasKey){
                door = input("( bater na porta | pedir ajuda ao velho |" RED " usar a chave" RST " )", 3);
            }else{
                door = input("( bater na porta | pedir ajuda ao velho )", 2);
            }
        }

        if(door == 1){
            printf(ITL "Knock, Knock...\n" RST);
            doorPassed = jokenpo();
        }else if(door == 3 && profissao == 1){
            printf("Com a espada empunhada, você golpeia a porta.\n");
            if(jar == 2){
                printf("A porta se despedaça e você descobre uma escadaria\n");
                doorPassed = 1;
            }else{
                doorPassed = jokenpo();
            }
        }else if(door == 3 && profissao == 2){
            printf(BLD "\"Bez Organicheniy\"" RST ", você diz olhando para a porta\"");
            if(jar == 2){
                printf("A porta se abre e revela uma escadaria escura\n");
                doorPassed = 1;
            }else{
                jokenpo();
            }
        }else if(door == 3 && profissao == 3){
            printf("A porta se abre ao inserir a chave na fechadura, e revela uma escadaria escura.\n");
        }
        
        // Evento 4b
        printf("\n");
        printf("Rapidamente você desce os degraus e chega a uma sala retangular.\n");
        if(doorPassed == 1){
            arrow();
        }

        // Evento 5
        printf("Há um alçapão perto dos seus pés mas está trancado.\n");
        printf("Você se abaixa e utiliza a chave para abrir.\n");
        printf("Após descer mais alguns lances de escada, você se encontra em uma grande sala oval.\n");
        printf("Há uma figura no centro, uma estátua talvez.\n");
        printf("Você da alguns passos à frente, na direção da estátua.\n");


        
    }

    return 0;
}

int jokenpo(){
    int j, r, w=0, l=0;

    printf("Estranhos glifos começam a aparecer na porta. Você reconhece alguns. \nParece que a porta quer jogar " GRN "jokenpô" RST ".\n");
    while(w < 2 && l < 2){
        j = input("( pedra | papel | tesoura )", 3);

        r = rand() % 3;
        if(r == 0){
            printf("A porta mostra um glifo semelhante a uma mão fechada\n");
        }else if(r == 1){
            printf("A porta mostra um glifo semelhante a uma mão aberta\n");
        }else{
            printf("A porta mostra um glifo semelhante a um sinal de paz e amor\n");
        }

        if((j - r) % 3 == 2){
            printf("Você ganhou essa.\n");
            w++;
        }else if(j-1 == r){
            printf("Empate\n");
        }else{
            printf("Você perdeu dessa vez\n");
            l++;
        }
    }

    if(l == 2){input("( ficar à direita | ficar no meio | ficar à esquerda )", 3);
        printf("A porta não tem rosto, mas você sente que ela está feliz em ter ganhado\n");
        return 0;
    }
    else{
        printf("A porta se abre e revela uma escadaria subterrânea.\n");
        printf("Antes de descer você percebe algo brilhando em cima do portal.\n");
        printf(ITL "Uma chave prateada foi adicionada ao seu inventário\n" RST);
        return 2;
    }
}

int arrow(){
    int j, r, w=0, l=0;

    printf("A parede oposta contém 3 buracos alinhados horizontalmente.\n");
    printf("Você acredita que podem ser uma armadilha.\n");
    while(w < 2 && l <2){
        j = input("( ficar à direita | ficar no meio | ficar à esquerda )", 3);
        r = rand() % 3;

        if((j - r) % 3 == 2){
            printf("Do ejetor diretamente a sua frente sai um fragmento de chave.\n");
            w++;
        }else if(j-1 == r){
            printf("O ejetor diretamente a sua frente não é ativado.\n");
        }else{
            printf("Do ejetor diretamente à sua frente sai uma flecha envenada.\n");
            l++;
        }

        if(w == 2){
            input("( ficar à direita | ficar no meio | ficar à esquerda )", 3);
            printf("Você se move, mas é inútil. Com os fragmentos de chave em mão, a sala parece saber que você venceu.\n");
            printf(ITL "Uma chave prateada foi adicionada ao seu inventário\n" RST);
            return 1;
            
        }else{
            return 0;
        }
    }
    
}