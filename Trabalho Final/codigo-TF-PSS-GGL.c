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

void novoEvento(struct evento *novo);
void novoDia(struct dia *data);
void printaStruct(struct evento *print);
void arquiva(struct evento *guarda, FILE *db);
int contaEventos();
int bissexto(int ano);
void organiza(struct evento *v, int n); 
int compara(struct evento *a, struct evento *b, int n);
void flush_in();

int main(){
    int n, m, c, d;
    char a[2], descri[10];
    int menu, repete;
    struct evento event, *v, *i;
    struct dia dataa;

    //Fim da secao das variaveis, comeco da coleta de dados

    n = contaEventos();
    v = malloc(sizeof(struct evento) * n);
    FILE *da;
    if ((da = fopen("dados.txt", "r")) != NULL){
        for(i = v; i < v + n; i++){
            fscanf(da, "%i\n", &i->data.dia);
            fscanf(da, "%i\n", &i->data.mes);
            fscanf(da, "%i\n", &i->data.ano);
            fscanf(da, "%i", &i->hInicio.hora);
            fscanf(da, "%i", &i->hInicio.minuto);
            fscanf(da, "%i", &i->hFim.hora);
            fscanf(da, "%i", &i->hFim.minuto);
            fscanf(da, "%s", i->descricao);
            fscanf(da, "%s", i->local);
            fscanf(da, "%s", a);
        }
    }
    fclose(da);


    //Fim da coleta de dados, comeco do menu
    
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
        switch (menu){
            case 1://Cria novo evento
                novoEvento(&event);
                printf("\nInformacoes do novo evento:\n");
                c = compara(&event, v, n);
                if (c == -1){
                    printf("Ja existe um evento igual.\n");
                } else{
                    printaStruct(&event);
                    v = realloc(v, sizeof(struct evento) * (n + 1));
                    n++;
                    m = n - 1;
                    for(i = v + m; i < v + n; i++){
                        *i = event;
                        printf("Salvo com sucesso!\n\n");
                    }
                    organiza(v, n);
                    FILE *db;
                    if ((db = fopen ("dados.txt", "w")) != NULL){
                        for(i = v; i < v + n; i++){
                            arquiva(i,db);
                        }
                    }
                    fclose(db);
                }
                break;

            case 2://Mostra todos os eventos
                if(n != 0){
                    for(i = v; i < v + n; i++){
                        printaStruct(i);
                    }
                } else {printf("nao ha nada armazenado.\n");}
                break;

            case 3://Pesquisa eventos conforme data
            d = 0;
                if(n != 0){
                    printf("digite a data do evento a ser procurado(Dia/Mes/Ano)\n");
                    novoDia(&dataa);                    
                    for(i = v; i < v + n; i++){
                        if(dataa.dia == i->data.dia && dataa.mes == i->data.mes && dataa.ano == i->data.ano){
                            printaStruct(i);  
                            d++;
                        }
                    }
                    if(d < 1) printf("Nao foram encontrados eventos nesta data.");
                } else {printf("nao ha nada armazenado.\n");}
                break;

            case 4://Pesquisa eventos conforme descrição
                if(n != 0){
                    printf("digite a descricao do evento a ser procurado\n");
                    scanf("%s", &descri);                    
                    for(i = v; i < v + n; i++){
                        if(strcmp(descri, i->descricao) == 0){
                            printaStruct(i);  
                            d++;
                        }
                    }
                    if(d < 1) printf("Nao foram encontrados eventos com essa descricao0.");
                } else {printf("nao ha nada armazenado.\n");}
                break;

            default:
                printf("caso default %i", menu);
                break;
        }
        printf("se deseja voltar ao menu, digite 0, se deseja sair, digite 1: ");
        scanf("%i", &repete);
    }
    free(v);
    return 0;
}

void novoEvento(struct evento *novo){//Registra um evento novo
    printf("digite a data do evento(Dia/Mes/Ano)\n");
    novoDia(&novo->data);
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

void novoDia(struct dia *data){//Registra uma data
    int cheque = 0;
    int anoo;
    printf("Dia: ");
    scanf("%i", &data->dia);
    printf("\nMes: ");
    do{
        scanf("%i", &data->mes);
        if(data->mes < 1 || data->mes > 12){
            printf("Mes invalido, digite novamente\n");
        }
    }while(data->mes < 1 || data->mes > 12);
    printf("\nAno: ");
    scanf("%i", &data->ano);
    do{
        if(data->mes == 1 || data->mes == 3 || data->mes == 5 || data->mes == 7 || data->mes == 8 || data->mes == 10 || data->mes == 12){
            if(data->dia < 0 && data->dia > 31){
                printf("dia invalido, digite novamente\n");
                cheque = 0;
                scanf("%i", &data->dia);
            } else cheque = 1;
        } else if(data->mes == 4 || data->mes == 6 || data->mes == 9 || data->mes == 12){
            if(data->dia < 0 && data->dia > 30){
                printf("dia invalido, digite novamente\n");
                cheque = 0;
                scanf("%i", &data->dia);
            } else cheque = 1;
        } else{
            anoo = bissexto(data->ano);
            if(anoo == 1){
                if(data->dia < 0 && data->dia > 29){
                    printf("dia invalido, digite novamente\n");
                    cheque = 0;
                    scanf("%i", &data->dia);
                } else cheque = 1;    
            } else {
                if(data->dia < 0 && data->dia > 28){
                    printf("dia invalido, digite novamente\n");
                    cheque = 0;
                    scanf("%i", &data->dia);
                } else cheque = 1;
            } 
        }
    }while(cheque != 1);
}

void printaStruct(struct evento *print){//Pinta uma struct e todos os seus dados
    printf("\n--------------------------------------\n");
    printf("Data: %02d/%02d/%4d\n", print->data.dia, print->data.mes, print->data.ano);
    printf("Inicio: %02d:%02d\n", print->hInicio.hora, print->hInicio.minuto);
    printf("Fim: %02d:%02d\n", print->hFim.hora, print->hFim.minuto);
    printf("Descricao: %s\n", print->descricao);
    printf("Local: %s", print->local);
    printf("\n--------------------------------------\n\n");
}

void arquiva(struct evento *guarda, FILE *db){//deposita os dados no arquivo
        fprintf(db, "%i %i %i", guarda->data.dia, guarda->data.mes, guarda->data.ano);
        fprintf(db, " %i %i", guarda->hInicio.hora, guarda->hInicio.minuto);
        fprintf(db, " %i %i", guarda->hFim.hora, guarda->hFim.minuto);
        fprintf(db, " %s", guarda->descricao);
        fprintf(db, " %s", guarda->local);
        fprintf(db, " $ ");
}

int contaEventos(){//conta quantos dos separadores tem no texto
    FILE *cb;
    int n = 0;
    char c;
    if ((cb=fopen ("dados.txt", "r")) != NULL) { 
        while( (c=fgetc(cb)) != EOF) {
            if (c=='$') n++;
        }
    }
    fclose(cb);
    return n;
}

void organiza(struct evento *v, int n){//organiza o vetor, baseado em data e horário de início
    struct evento *i, *j, aux;
    for (i = v; i < v + n; i++){
        for(j = v; j < v + n - (i - v); j++){
            if(j->hInicio.hora > (j+1)->hInicio.hora){
                aux = *(j + 1);
                *(j + 1) = *j;
                *j = aux;
            }
        }
    }
    for (i = v; i < v + n; i++){
        for(j = v; j < v + n - (i - v); j++){
            if(j->data.dia > (j+1)->data.dia){
                aux = *(j + 1);
                *(j + 1) = *j;
                *j = aux;
            }
        }
    }
    for (i = v; i < v + n; i++){
        for(j = v; j < v + n - (i - v); j++){
            if(j->data.mes > (j+1)->data.mes){
                aux = *(j + 1);
                *(j + 1) = *j;
                *j = aux;
            }
        }
    }
    for (i = v; i < v + n; i++){
        for(j = v; j < v + n - (i - v); j++){
            if(j->data.ano > (j+1)->data.ano){
                aux = *(j + 1);
                *(j + 1) = *j;
                *j = aux;
            }
        }
    }
}

int bissexto(int ano){//Checa se o ano é bissexto
	if((((ano%4)==0) && ((ano%100) !=0) || ((ano%400)==0)))
		return 1;
	else
		return 0;
}

int compara(struct evento *a, struct evento *b, int n){//compara com eventos existentes, para ver se há repetições
    struct evento *i;
    int cont = 0;
    for(i = b; i < b + n; i++){
        if(a->data.dia == i->data.dia && a->data.mes == i->data.mes && a->data.ano == i->data.ano && a->hInicio.hora == i->hInicio.hora &&
        a->hInicio.minuto == i->hInicio.minuto && a->hFim.hora == i->hFim.hora && a->hFim.minuto == i->hFim.minuto);{
            cont = 1;
        }
    }
    if (cont = 1){
        return -1;
    } else {return 0;}
}

void flush_in(){//Limpa Buffer
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}