#include <stdio.h>
#include <stdlib.h>
#define MAXVERTICE 100


typedef struct node *graph;

struct node
{
    int vertices, valor;
    graph proximo;
};
typedef graph matriz[MAXVERTICE];

void Grafo_Inicializa(matriz M, int linha)
{
    int i;
    for(i=0; i<linha; i++)
    {
        M[i]= NULL;
    }
}
void Grafo_Insere(matriz M, int i, int j,int valor)
{
    graph novo;
    graph aux;
    /*novo é o nó que vai guardar o dado inserido*/
    novo = (graph)malloc(sizeof(struct node));
    novo->vertices = i;
    novo->valor =j;
    novo->proximo = NULL;

    if(M[i]==NULL)
    {
        M[i]=novo;

    }
    else
    {
        for(aux = M[i]; aux->proximo != NULL; aux = aux->proximo);
        aux->proximo = novo;
    }
    for(aux = M[i]; aux != NULL; aux = aux->proximo)
    {
        printf("(%d, %d)\n ",aux->vertices, aux->valor);
    }
}

/*Imprime a matriz incluindo*/
void Imprime(matriz M, int linha)
{
    int i, j;
    graph aux;

    for(i=0; i<linha; i++)
    {

        for(j=0; j<linha; j++)
        {
            aux=M[i];

            while(aux!=NULL)
            {
                if(aux->valor==j+1)
                    break;
                aux=aux->proximo;
            }
            if(aux==NULL)
                printf("0");
            else
            {
                printf("1");
            }
        }
        printf("\n");
    }
    printf("\n");
}
void Verifica_adjacencia(matriz M, int vertice)
{

    graph aux=M[vertice-1];

    printf ("Os vertices adjacentes do vertice %d sao:\n", vertice);
    if(aux!=NULL)
    {
        do
        {
            printf("%d ", aux->valor);
            aux=aux->proximo;

        }
        while(aux != NULL);
    }
    else
    {
        printf("SEM ADJACENTES!\n");
    }
    printf("\n");
    //}
}
/*Libera os espaços de memoria alocados para armazenar as listas*/
void Libera (matriz M, int Linha)
{
    graph p,q;
    int i;
    for(i =0; i<Linha; i++)
    {
        p = M[i];
        while(p != NULL)
        {
            q = p;
            p = p->proximo;
            free(p);
        }
    }
    printf("\nFim!");
}
int main()
{
    matriz M;/*vetor de lista*/
    int vertice, i,j=0,aux,linha,coluna;
    int ordenado,valor;

    printf("Informe o numero de vertices: ");
    scanf("%d", &vertice);

    Grafo_Inicializa( M, vertice);

    printf("\nO grafo é orientado?(sim=1/não =0): ");
    scanf(" %d", &ordenado);
       //Não esquecer de dar o espaço entre os numeros
    printf("\nInforme as conexões, digite 0 para encerrar: ");
    scanf("%d", &i);
    int maiorj=0;
    while(i != 0)
    {
        i--;
        scanf("%d", &j);
        // comparando o valor de j com o maior j, para que sempre obedeça o numero de vertices.
        if(j > maiorj)
        {
            maiorj = j;
        }
        if(ordenado ==1)
        {
            // inserindo ordenado
            Grafo_Insere(M,  i,j,valor);

        }

        else if(ordenado==0)
        {
            // como não é ordenado, chamo a função insere 2x, trocando os indices
            Grafo_Insere(M, i,j,valor);

            Grafo_Insere(M, j-1,i+1,valor);

        }
        printf("\nInforme as conexões, digite 0 para encerrar: ");
        scanf("%d", &i);
    }
    printf("\n--Matriz de adjacencia--\n");
    Imprime (M,vertice);

    printf("\n Informe o vertice que deseja ver seus adjacentes: ");
    scanf("%d", &i);

    //Função que mostra os adjacentos do vertice escolhido
    Verifica_adjacencia( M, i);
    Libera ( M, i);
    return 0;
}
