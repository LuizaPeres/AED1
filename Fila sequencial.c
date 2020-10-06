#include <stdio.h>
#include<stdlib.h>
#define  Max_fila 100

typedef struct
{
    int posicao[Max_fila];
    int n;// quantidade de candidatos
    int inicio;//inicio da fila
} TFila;
typedef TFila *PFila;

PFila Cria_Fila(void)
{
    PFila fila = (PFila)malloc(sizeof(TFila));
    fila->n=0;
    fila ->inicio = 0;
    return fila;
}
int Fila_vazia (PFila fila)
{
    return  (fila->n);
}
/*Função para inserir os candidatos a fila*/
int Insere(PFila fila, int valor)
{
    int Fim;
    if(fila == NULL)
    {
        printf("Fila nao inicializada\n");
        return -1;
    }
    if (fila->n == Max_fila)
    {
        printf("A fila esta cheia!\n");
        return -1;
    }
    Fim = (fila ->inicio) + (fila ->n)%Max_fila;/*Achar a posição que posso inserir o ultimo candidatos*/
    fila ->posicao[Fim] = valor;
    fila ->n++; /*atualizando o numero de candidatos, cada vez que insiro mais um candidato*/
    return 0;
}
/*Essa função é porque a fila está sendo implementada utilizando fila circular*/
int incr_indice( int i)
{
    if (i == Max_fila -1)
    {
        return 0;
    }
    else
    {
        return i+1;
    }
}
int Retira (PFila fila, int *valor)/*Função para retirar da fila*/
{
    if(fila == NULL)
    {
        printf("Fila nao inicializada!\n");
        return -1;
    }
    if(fila ->n == 0)
    {
        printf("Fila esta vazia\n");
        return -1;
    }
    *valor = fila ->posicao[fila->inicio];
    fila ->inicio = incr_indice(fila->inicio);
    fila -> n--;
    return 0;
}
/* Função que ordena os candidatos em ordem decrescente*/
int Ordena_Fila(int *nota, int id[], int candidatos)
{
    int j, aux1, aux2, i;
    for ( i = 1; i<candidatos; i++)
    {
        for(j=0; j< candidatos -1; j++)
        {
            if(nota[j]< nota [j+1])
            {
                aux1 = nota[j];
                aux2 = id[j];
                nota [j] = nota [j+1];
                id[j]=id[j+1];
                nota [j+1] =aux1;
                id[j+1]=aux2;
            }
        }
    }

    return 1;
}
int main()
{
    PFila Candidatos;
    int i, nota[Max_fila],candidatos =0,v =0, id [Max_fila];
    int aux, Aprovado[Max_fila],cont;
    char resposta;
    Candidatos = Cria_Fila();
    do
    {
        printf("Quantidade de candidatos: ");
        scanf(" %d", &candidatos);
    }
    while(candidatos<1);

    do
    {
        printf("Quantidade de vagas: ");
        scanf(" %d", &v);
    }
    while (v <1);

    for(i= 0; i < candidatos ; i++)
    {
        nota [i] = -1;

        do
        {
            printf("\nNumero Identificador do candidato:");
            scanf(" %d", &id[i]);

            printf("Nota do candidato %d :", id [i]);
            scanf(" %d", &nota [i]);
        }
        while (nota[i]<0 || nota [i] >100);
        printf("Candidato inserido!\n");

    }

    printf("\n-Impressao da fila-\n");

    Ordena_Fila(nota,id,candidatos);/*Ordenando a fila antes de imprimi-la*/

    /*Inserindo os candidatos na fila e imprimindo-os*/
    for(i = 0; i< candidatos; i++)
    {
        if ((Insere(Candidatos, id[i])==-1))
        {
            break;
        }
        printf("Candidato %d, nota: %d\n ", id[i], nota[i]);

    }

    i=0;
    cont = 0;// auxiliar porque o numero de vagas diminui
    while(v!=0 && Candidatos->n)
    {
        Retira(Candidatos, &aux);

        printf("\nResposta recebida pelo candidato de id %d (s/n): ",aux);
        scanf(" %c", &resposta);
        if (resposta == 's')
        {
            Aprovado[cont]= aux;/* cont = conta o numero de aprovados*/
            v--;/*O numero de vagas diminui*/
            cont++;/*Incremento o cont, pois pode ter mais candidato do que vaga*/
        }
    }
    printf("\n-Lista de Novos Alunos-\n");
    for(i=0; i<cont; i++)
    {
        printf("\nCandidatos id %d ", Aprovado [i]);
    }
    free(Candidatos);/*Liberando a memória*/
}
