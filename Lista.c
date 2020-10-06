#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TProdutos
{
    int codigo;
    char nome[60];
    float preco;
} Produtos;

typedef struct Lista /*Declarando a Lista encadeada*/
{
    Produtos info;
    struct Lista *proximo;
} TLista;
typedef TLista *PLista;

PLista Inicializa_Lista()
{
    return NULL; /*Não tem nenhum elemento na lista ainda*/
}

/*função insereo produto em ordem crescente de código*/
PLista Ordenado(Produtos x, PLista Lista)
{
    PLista NovoProduto;
    PLista anterior = NULL; /*ponteiro auxiliar para a posição anterior*/
    PLista paux = Lista; /*ponteiro auxiliar para percorrer a lista*/

    NovoProduto = (TLista*) malloc(sizeof(TLista));/*aloca um novo nodo */

//NovoProduto->info = x;/*insere a informação no novo nodo*/

    /*procurando a posição de inserção*/
    while (paux!=NULL)
    {
        printf("\nCodigo = %d",paux->info.codigo);
        printf("\nNome = %s",paux->info.nome);
        printf("\nPreco = %f", paux->info.preco);
        paux = paux->proximo;
    }
    return Lista;

}
void Insere(Produtos x, PLista Lista)
{
    PLista NovoProduto, ProdutoAtual,anterior; /*Criei um nó*/
    NovoProduto = (TLista *)malloc(sizeof(TLista));

    printf("\nInsira o codigo do produto: ");
    scanf("%d",&NovoProduto->info.codigo);

    printf("\nInsira o nome do produto: ");
    fflush(stdin);
    scanf(" %s",NovoProduto-> info.nome);

    printf("\nInsira o preco do produto: ");
    scanf("%f", &NovoProduto->info.preco);

    NovoProduto->proximo =NULL;
    /*encadeia o produto na lista*/
    if (anterior == NULL) /*o anterior não existe, será inserido na primeira posição*/
    {
        NovoProduto->proximo = Lista;
        Lista = NovoProduto;
    }
    else /*elemento inserido no meio da lista*/
    {
        NovoProduto->proximo = anterior->proximo;
        anterior->proximo =ProdutoAtual;
        if((ProdutoAtual->info.codigo)> (NovoProduto ->info.codigo))
        {

            NovoProduto ->proximo = anterior ->proximo;
            anterior->proximo = NovoProduto;
        }
        else
        {

            while(ProdutoAtual != NULL)
            {
                if((ProdutoAtual->info.codigo) < (NovoProduto ->info.codigo))
                {
                    anterior = ProdutoAtual;
                }
                else
                {
                    ProdutoAtual = NULL;
                }
            }
            NovoProduto ->proximo = anterior ->proximo;
            anterior ->proximo = NovoProduto;
        }
    }
}
/*Procurando um produto na lista*/
PLista Busca(Produtos x,PLista Lista, float preco)
{
    PLista pNova;  /*ponteiro auxiliar*/
    for(pNova = Lista; pNova!= NULL; pNova= pNova ->proximo)
    {
        if(pNova->info.preco == preco)
        {
            return pNova;
        }
        return NULL; /*Não achou o produto*/
    }
}
void Imprime(PLista Lista)
{
    PLista  NovoProduto;
    for (NovoProduto = Lista; NovoProduto != NULL; NovoProduto= NovoProduto->proximo)
        printf("\nNome: %s\nCodigo: %d \nPreco:R$%.2lf",Lista->info.nome, Lista->info.codigo, Lista->info.preco);
}
PLista Retira(Produtos *px, PLista Lista, char *nome)
{
    PLista anterior = NULL; /*Ponteiro para produto anterior*/
    PLista p; /*ponteiro para percorrer a lista*/

    /*Procura elemento na lista, guardando o anterior*/
    for(p=Lista; p!= NULL && p->info.nome != nome; p = p ->proximo)
    {
        anterior = p;
        /*verifica se achou o produto*/
        if(p == NULL)
        {
            return Lista; /*não achou: retorna a lista original*/
        }
        /*retira o produto*/
        if (anterior == NULL)
        {
            Lista = p ->proximo; /*Retira o produto do inicio*/
        }
        else
        {
            anterior ->proximo = p ->proximo;/*retira o produto do meio da lista*/
        }
        free(p);
        return Lista;
    }
}
void Destroi_Lista(PLista Lista)
{
    PLista p = Lista, t;
    while(p != NULL)
    {
        t = p ->proximo; /*Guarda referencia para o prox elemento*/
        free(p); /*libera a memória apontada por p */
        p =t; /*Faz p apontar para  proximo*/
    }
}
int main( )
{
    PLista NovoProduto, Lista;
    Produtos produto;
    char Nome_Produto;
    float preco;
    int tamanho=0, i =0;

    Inicializa_Lista();

    printf("Digite o tamanho da lista: ");
    scanf("%d", &tamanho);

    /* Enquanto nao chega no fim da lista */
    for(i=0; i<tamanho; i++)
    {
        Insere(produto, Lista);
        Ordenado(produto, Lista);
        printf("\nNome: %s\nCodigo: %d \nPreco:R$%.2lf",Lista->info.nome, Lista->info.codigo, Lista->info.preco);
        Lista = Lista->proximo; /* Faz o nó atual, Lista, apontar para o proximo no */
        
    }

    Busca(produto,Lista, preco);
    printf("\nQual produto deseja retirar da lista? ");
    Retira(&produto, Lista, &Nome_Produto);
    Destroi_Lista(Lista);

 return  0;
}
