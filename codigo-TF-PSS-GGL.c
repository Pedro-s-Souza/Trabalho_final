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
    int menu = 0;
    //Fim da secao das variaveis, comeco do menu
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
        printf("caso 1 %i", menu);
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







    return 0;
}
