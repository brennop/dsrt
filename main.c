// ------------------------------------
// 
//  Teres Game - APC Turma D  - 2019.1
// 
// -------------------------------------

#include <stdio.h>
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

    int jar, hasKey = 0, oldMan;

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

    printf("Você segue andando pelo deserto e avista uma figura. Ao se aproximar, percebe que é umi " BLU "velho" RST " à beira da morte.\n");

    if(alinhamento == 1){
        // Saquear
        if(input("( saquear o velho | conversar com o velho )", 2) == 1){
            // Ladino
            if(profissao == 3){
                printf("Não há resistência quando se abaixa para olhar os bolsos do velho.\n");
                printf(ITL "Uma chave dourada foi adicionada ao seu inventário.\n" RST);
                hasKey = 1;
            }else{
                printf("Você vasculha os bolsos do velho procurando algo, mas não há nada.\n");
            }
        }else{ //Conversar
            printf("O velho olha para o horizonte e responde com dificuldade.\n");
            printf(ITL"\"Eu sou como você.\"\n"RST);
        }
        
    }else{
        // Se possui a jarra
        if(jar == 3){
            oldMan = input("(conversar com o velho | oferecer ajuda ao velho | oferecer a jarra ao velho )", 3);
        }else{
            oldMan = input("(conversar com o velho | oferecer ajuda ao velho )", 2);
        }

        //Conversar
        if(oldMan == 1){ 
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
        }else if(oldMan == 2){ // Ajuda
            
        }
        
    }




    return 0;
}