#include <stdlib.h>
#include <stdio.h>


struct horario{
    int hora;
    int minuto;
};

struct dia{
    int dia;
    int mes;
    int ano;
};

struct evento{
    struct dia data;
    struct horario hInicio;
    struct horario hFim;
    char descricao[10];
    char local[10];

};

int main(){
    struct evento novo;
    int menu = 0, repete = 0;
    //Fim da secao das variaveis, comeco do menu
    
    while (repete != 1){
        while(menu < 1 || menu > 5){
            printf("\n------------------------------------------------\n");
            printf("Menu \n\n1 - Cadastrar novo evento \n2 - Mostrar todos os eventos \n3 - Pesquisa de eventos por data \n"); 
            printf("4 - Pesquisa de eventos por descricao \n5 - Remover evento");
            printf("\n------------------------------------------------\n");
            printf("Digite a opcao: ");
            scanf("%i", &menu);
            if(menu < 1 || menu > 5){
                printf("Opcao invalida, tente novamente");
            }
        }    
        switch (menu)
        {
        case 1:
            printf("digite o dia do evento: (Dia/Mes/Ano)");
            scanf("%i", &novo.data.dia);
            scanf("%i", &novo.data.mes);
            scanf("%i", &novo.data.ano);
            printf("digite o horario de inicio do evento: (Hora:Minuto)");
            scanf("%i", &novo.hInicio.hora);
            scanf("%i", &novo.hInicio.minuto);
            printf("digite o horario de fim do evento: (Hora:Minuto)");
            scanf("%i", &novo.hFim.hora);
            scanf("%i", &novo.hFim.minuto);
            flush_in();
            printf("Digite a descricao do evento");
            gets(novo.descricao);
            flush_in();
            printf("Digite o local do evento");
            gets(novo.local);
            printaStruct(novo);
            arquiva(novo);
            break;

        case 2:
            printf("caso 2 %i", menu);
            break;

        case 3:
            printf("caso 3 %i", menu);
            break;

        case 4:
            printf("caso 4 %i", menu);
            break;

        default:
            printf("caso default %i", menu);
            break;
        }
        printf("se deseja voltar ao menu, digite 0, se deseja sair, digite 1");
        scanf("%i", &repete);
    }

    return 0;
}



void printaStruct(struct evento print){
    printf("Data: %02d/%02d/%4d\n", print.data.dia, print.data.mes, print.data.ano);
    printf("Inicio: %02d:%02d\n", print.hInicio.hora, print.hInicio.minuto);
    printf("Fim: %02d:%02d\n", print.hFim.hora, print.hFim.minuto);
    printf("Descricao: %s\n", print.descricao);
    printf("Local: %s\n", print.local);
}

void arquiva(struct evento guarda){
    FILE *db;
    if ((db = fopen ("dados.txt", "w")) != NULL){
        fprintf(db, "%i\n%i\n%i", guarda.data.dia, guarda.data.mes, guarda.data.ano);
        fprintf(db, "\n\n%i\n%i", guarda.hInicio.hora, guarda.hInicio.minuto);
        fprintf(db, "\n\n%i\n%i", guarda.hFim.hora, guarda.hFim.minuto);
        fprintf(db, "\n\n%s", guarda.descricao);
        fprintf(db, "\n\n%s", guarda.local);
    }
    fclose(db);
}

//Limpa Buffer
void flush_in(){
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}