#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 60

typedef struct TProdutos
{
    int codigo;
    char nome[MAXTAM];
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

PLista Insere(PLista Lista)
{
    PLista NovoProduto;
    PLista anterior = (TLista *)malloc(sizeof(TLista));
    PLista ProdutoAtual = (TLista *)malloc(sizeof(TLista));

    anterior = NULL;
    ProdutoAtual = Lista;
    NovoProduto = (TLista *)malloc(sizeof(TLista));
  
    printf("\nInsira o nome do produto: ");
    fflush(stdin);
    scanf(" %s",NovoProduto-> info.nome);
    
    printf("Insira o codigo do produto: ");
    scanf("%d",&NovoProduto->info.codigo);

    printf("Insira o preco do produto: ");
    scanf("%f", &NovoProduto->info.preco);


    /*Procura a posição que vai inserir o produto, baseado no codigo*/
    while(ProdutoAtual != NULL)
    {
        if((ProdutoAtual->info.codigo) < (NovoProduto ->info.codigo))
        {
            anterior = ProdutoAtual;
        }
        ProdutoAtual = ProdutoAtual->proximo;

    }

    /*encadeia o produto na lista*/
    if (anterior == NULL) /*o anterior não existe, será inserido na primeira posição*/
    {
        NovoProduto->proximo = Lista;
        Lista = NovoProduto;
    }
    else /*elemento inserido no meio da lista*/
    {
        NovoProduto->proximo = anterior->proximo;
        anterior->proximo = NovoProduto;
    }
    return Lista;
}
/*Procurando um produto na lista*/
float Busca(PLista Lista, char nome[])
{
    PLista pNova;  /*ponteiro auxiliar*/
    for(pNova = Lista; pNova!= NULL; pNova= pNova->proximo)
    {
        if(strcmp(nome, pNova->info.nome) == 0)
            return pNova ->info.preco;
    }
    free(pNova);
    return -1; /*Não achou o produto*/
}
void Imprime(PLista Lista)
{
    /*NovoProduto é a variavel auxiliar para percorrer a lista*/
    PLista NovoProduto;

    if(NovoProduto == NULL)
    {
        printf("Lista Vazia\n");
        return;
    }
    for(NovoProduto = Lista; NovoProduto != NULL; NovoProduto = NovoProduto->proximo)
    {
        printf("\nNome: %s",NovoProduto->info.nome);
        printf("\nCodigo: %d",NovoProduto->info.codigo);
        printf("\nPreco:R$%.2f",NovoProduto->info.preco);

        printf("\n");
    }
}
PLista Retira(PLista Lista, char *nome)
{
    PLista anterior = NULL; /*Ponteiro para produto anterior*/
    PLista p; /*ponteiro para percorrer a lista*/

    /*Procura elemento na lista, guardando o anterior*/
    for(p = Lista; p != NULL && strcmp(nome,p->info.nome) != 0 ; p=p->proximo)
    {
        anterior = p;
    }
    /*verifica se achou o produto*/
    if(Lista == NULL)
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
    free (p);
    return Lista;
}
PLista Destroi_Lista(PLista Lista)
{
    PLista p = Lista, t;
    while(p != NULL)
    {
        t = p ->proximo; /*Guarda referencia para o prox produto*/
        free(p); /*libera a memória apontada por p */
        p = t; /*Faz p apontar para  proximo*/
    }
    printf("\nLista destruída");
    Lista = NULL;
    free(Lista); /*libera a memória apontada por p */
    return (p);

}
int main( )
{
    PLista Lista;
    Produtos produto;
    char Nome_Produto[MAXTAM], Nome_excluido[MAXTAM];
    float preco=0;
    int tamanho = 0, i;


    printf("Digite o tamanho da lista: ");
    scanf("%d", &tamanho);

    Lista = (TLista *)malloc(sizeof(TLista));

    Lista = Inicializa_Lista();

    /* Enquanto nao chega no fim da lista */
    for(i=0; i<tamanho; i++)
    {
        Lista = Insere(Lista);
    }
    printf("\n\n--Lista de Produtos--\n");
    Imprime(Lista);

    printf("\n");

    printf("\nInsira o nome do produto para saber o preço: ");
    scanf(" %s", Nome_Produto);
    if(Busca(Lista, Nome_Produto) != -1)
    {
        printf("\nO preco eh: R$ %.2f", Busca(Lista,Nome_Produto));
    }
    else
    {
        printf("\nO produto nao foi encontrado!");
    }

    /*Retirando o produto da lista*/
    printf("\n\nQual produto deseja retirar da lista? ");
    scanf(" %s", Nome_excluido);
    Retira(Lista, Nome_excluido);

    /*Mostrando a nova lista sem o produto excluido*/
    printf("\n--Nova Lista--\n");
    Imprime(Lista);

    /*Destuindo a lista*/
    Lista = Destroi_Lista(Lista);

    return  0;
}
