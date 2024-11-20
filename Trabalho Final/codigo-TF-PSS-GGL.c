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

void desarquiva(struct evento *pega, int n);
void novoEvento(struct evento *novo);
void printaStruct(struct evento *print);
void arquiva(struct evento guarda);
void flush_in();

int main(){
    FILE *cb;
    int n = 0;
    char c;
    if ((cb=fopen ("dados.txt", "r")) != NULL) { 
        while( (c=fgetc(cb)) != EOF) {
            if (c=='$') n++;
        }
    }
    fclose(cb);
    int menu = 0, repete = 0;
    struct evento event, *v, *i;
    v = malloc(sizeof(struct evento) * n);
    
    //----------------------------
    

    //Fim da secao das variaveis, comeco do menu




    printf("Há %i Structs.", n);
    desarquiva(&v, n);
    while (repete != 1){
        menu = 0; repete = 0;
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
        case 1://Cria novo evento
            novoEvento(&event);
            printaStruct(&event);
            arquiva(event);
            break;

        case 2:
            for(i = v; i < v + n; i++){
                printaStruct(&i);
            }
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
        printf("se deseja voltar ao menu, digite 0, se deseja sair, digite 1: ");
        scanf("%i", &repete);
    }

    return 0;
}

void desarquiva(struct evento *pega, int n){
    FILE *da;
    char a;
    struct evento *i;
    if ((da = fopen("dados.txt", "r")) != NULL){
        for(i = pega; i < pega + n; i++){
            fscanf(da, "%i\n", &i->data.dia);
            fscanf(da, "%i\n", &i->data.mes);
            fscanf(da, "%i\n", &i->data.ano);
            fscanf(da, "%i", &i->hInicio.hora);
            fscanf(da, "%i", &i->hInicio.minuto);
            fscanf(da, "%i", &i->hFim.hora);
            fscanf(da, "%i", &i->hFim.minuto);
            fscanf(da, "%s", i->descricao);
            fscanf(da, "%s", i->local);
            fscanf(da, "$", &a);

        }
    }
    fclose(da);
}

void novoEvento(struct evento *novo){
    printf("digite o dia do evento(Dia/Mes/Ano)\n");
    printf("Dia: ");
    scanf("%i", &novo->data.dia);
    printf("\nMes: ");
    do{
        scanf("%i", &novo->data.mes);
        if(novo->data.mes < 1 || novo->data.mes > 12){
            printf("Mes invalido, digite novamente\n");
        }
    }while(novo->data.mes < 1 || novo->data.mes > 12);
    printf("\nAno: ");
    scanf("%i", &novo->data.ano);
    printf("digite o horario de inicio do evento(Horas:Minutos)\n");
    printf("Horas: ");
    do{
        scanf("%i", &novo->hInicio.hora);
        if(novo->hInicio.hora < 0 || novo->hInicio.hora > 24){
            printf("Hora invalida, digite novamente\n");
        }
    }while (novo->hInicio.hora < 0 || novo->hInicio.hora > 24);
    printf("\nMinutos: ");
    do{
        scanf("%i", &novo->hInicio.minuto);
        if(novo->hInicio.minuto < 0 || novo->hInicio.minuto > 60){
            printf("Minuto invalido, digite novamente\n");
        }
    }while (novo->hInicio.minuto < 0 || novo->hInicio.minuto > 60);
    printf("digite o horario de fim do evento(Horas:Minutos)\n");
    printf("Horas: ");
        do{
        scanf("%i", &novo->hFim.hora);
        if(novo->hFim.hora < 0 || novo->hFim.hora > 24){
            printf("Hora invalida, digite novamente\n");
        }
    }while (novo->hFim.hora < 0 || novo->hFim.hora > 24);
    printf("\nMinutos: ");
    do{
        scanf("%i", &novo->hFim.minuto);
        if(novo->hFim.minuto < 0 || novo->hFim.minuto > 60){
            printf("Minuto invalido, digite novamente\n");
        }
    }while (novo->hFim.minuto < 0 || novo->hFim.minuto > 60);
    flush_in();
    printf("\nDigite a descricao do evento: ");
    gets(novo->descricao);
    printf("\nDigite o local do evento: ");
    gets(novo->local);
}

void printaStruct(struct evento *print){
    printf("\n------------------------------------------------\n");
    printf("\nInformacoes do novo evento:\n\n");
    printf("Data: %02d/%02d/%4d\n", print->data.dia, print->data.mes, print->data.ano);
    printf("Inicio: %02d:%02d\n", print->hInicio.hora, print->hInicio.minuto);
    printf("Fim: %02d:%02d\n", print->hFim.hora, print->hFim.minuto);
    printf("Descricao: %s\n", print->descricao);
    printf("Local: %s\n", print->local);
    printf("\n------------------------------------------------\n\n");
}

void arquiva(struct evento guarda){
    FILE *db;
    if ((db = fopen ("dados.txt", "w")) != NULL){
        fprintf(db, "%i\n%i\n%i", guarda.data.dia, guarda.data.mes, guarda.data.ano);
        fprintf(db, "\n\n%i\n%i", guarda.hInicio.hora, guarda.hInicio.minuto);
        fprintf(db, "\n\n%i\n%i", guarda.hFim.hora, guarda.hFim.minuto);
        fprintf(db, "\n\n%s", guarda.descricao);
        fprintf(db, "\n\n%s", guarda.local);
        fprintf(db, "\n$\n");
    }
    fclose(db);
}

//Limpa Buffer
void flush_in(){
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}