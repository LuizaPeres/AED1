//Luiza Peres Viana RA: 140491 Turma: Noturno
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct Tree
{
    char id;
    struct Tree *pai;
    struct Tree *esquerda;
    struct Tree *direita;

} TArv;

typedef  TArv *PTree;

void Imprime_filhos(PTree a,char c);
void Imprime_Irmaos(PTree pNo, char c);
void Arvore_pesquisa(PTree No, char buscado,int opcao);

/*sae (subárvore à esquerda)  e sad (subárvore à direita*/
PTree Cria_Arvore( char c)
{
    int i=0;
    PTree p=(PTree)malloc (sizeof(TArv));
    p->id=c;
    p->esquerda = NULL;
    p->direita =NULL;
    return p;
}
PTree Inicia_Arvore()
{
    return NULL;
}

/*Tamanho da arvore*/
int Quantidade_no(PTree Arv)
{
    if(Arv != NULL)
    {
        return (1+Quantidade_no(Arv->esquerda)+ Quantidade_no(Arv->direita));
    }
    else
    {
        return 0;
    }
}


PTree Insere(PTree pNo, char filho,int num_filhos,char pai)
{
    PTree Aux;

    if(pNo->id!=pai)
    {

        if(pNo->esquerda!=NULL) //verfica sub arv esquerda
        {
            //printf("Verificando sae\n");
            Insere(pNo->esquerda,filho, num_filhos,pai);
        }
        if(pNo->direita!=NULL) //verifica sub arv direita
        {
            // printf("Verificando sad\n");
            Insere(pNo->direita,filho, num_filhos,pai);
        }


    }
    else if(pNo->id==pai)
    {
       /* printf("achou o pai, %c\n", pNo->id);*/
        if(pNo->esquerda==NULL)
        {
            pNo->esquerda=Cria_Arvore(filho);
        }
        else
        {
            Aux=pNo->esquerda;
            while(Aux->direita!=NULL)
            {
                Aux=Aux->direita;
            }
            Aux->direita=Cria_Arvore(filho);
        }

    }
    return  pNo;
}
/*Como para imprimir o filho, primeiro eu verifico a esquerda e depois percorro sempre a direita para verificar os irmãos, fim uma unica função Imprime2 para fazer essa leitura, assim quando eu for chama-la para o ler os filhos chamo assim: Imprime2(No->esquerda);e para os irmãos assim: Imprime2(No->direita)*/
void Imprime2(PTree No)
{
    while(No!=NULL)
    {
        printf(" %c ", No->id);
        No=No->direita;
    }
}
/*A função pesquisa é uma função recursiva e dentro dela já coloquei as opçoes 3 e 4 do meu menu, para imprimir os filhos e irmãos respectivamente*/
void Arvore_pesquisa(PTree No, char buscado,int opcao)
{

    if(No->id!=buscado)
    {
        if(No->esquerda!=NULL)
        {
            Arvore_pesquisa(No->esquerda, buscado,opcao);
        }
        if(No->direita!=NULL)
        {
            Arvore_pesquisa(No->direita,buscado,opcao);
        }
        return;
    }
    if(opcao==3)
    {
        if(No->esquerda==NULL)
        {
            printf("Nao tem filhos!\n");
        }
        else
        {

            printf("Filho:\n");
            Imprime2(No->esquerda);
        }
    }
    else if(opcao==4)
    {
        if(No->direita==NULL )
        {
            printf("Nao tem irmãos!\n");

        }
        else
        {
            printf("Irmao:\n");
            Imprime2(No->direita);
        }

    }
}

/*Função para imprimir préfixa*/
void ImprimePre(PTree a)
{
    if(a==NULL)
        return;
    printf("%c", a->id); /*Mostra a raiz*/
    ImprimePre(a->esquerda);/*Mostra asae*/
    ImprimePre(a->direita);/*Mostra a sad*/

}
/*Função para imprimir infixa*/
void ImprimeIn(PTree a)
{
    if(a == NULL)
        return;
    {

        ImprimeIn(a->esquerda);/*Mostra asae*/
        printf("%c", (a->id)); /*Mostra a raiz*/
        ImprimeIn(a->direita);/*Mostra a sad*/

    }
}
/*Função para liberar a memoria */
PTree Libera_Arvore(PTree a)
{
    if(a!= NULL)
    {
        Libera_Arvore( a->esquerda); /*LIbera sae*/
        Libera_Arvore(a->direita); /*Libera sad*/
        free(a); /*Libera raiz*/

    }
    return NULL;
}
/*Função menu, para o usuario escolher as opções de impressão*/
void Menu(PTree a)
{
    int opcao =1;
    char c;

    do
    {
        printf("\n0- Para sair.");
        printf("\n1- Imprimir a árvore resultante em pré-ordem. ");
        printf("\n2- Imprimir a árvore resultante em ordem infixa.");
        printf("\n3- Imprimir os filhos de um dado nó.");
        printf("\n4- Imprimir os irmão de um dado nó\n");


        printf("\nDigite a opcao escolhida: \n");
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            printf("\nA pré-ordem é:\n");
            ImprimePre(a);
            break;
        case 2:
            printf("\nA ordem infixa é: \n");
            ImprimeIn(a);
            break;
        case 3:
            printf("\nDigite o nó que deseja saber os filhos: ");
            scanf(" %c", &c);
            Arvore_pesquisa(a,c,opcao);
            break;
        case 4:
            printf("\nDigite o nó que deseja saber os irmãos: ");
            scanf(" %c", &c);
            Arvore_pesquisa(a, c, opcao);
            break;
        case 0:
            break;
        default:
            printf("Digite uma opção válida");
            break;
        }
    }
    while(opcao <= 4 && opcao !=0);
}
int main(void)
{
    //para usar acentuação
    setlocale(LC_ALL,"");

    PTree Raiz=NULL;
    FILE *arquivo;
    PTree tree;
    int i=0,nfilhos;
    char id,pai, filho;
    id=(char*)malloc(25*sizeof(char));
    int count;

    tree = Inicia_Arvore();
    /*Lendo o arquivo*/
    arquivo = fopen("arv.txt","r");
    
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%c ", &pai);
        if( Raiz==NULL) //arvore inexistente
        {
            printf("Criando Arvore\n");
            Raiz=Cria_Arvore(pai);
        }
        //printf("\n-------pai: %c", pai);
        fscanf(arquivo,"%d ", &nfilhos);
        //printf("\n++++++++nfilhos: %d", nfilhos);
        for(i=0; i<nfilhos; i++)
        {
            fscanf(arquivo,"%c ", &filho);
            //printf("\nFilho: %c", filho);
            Insere(Raiz, filho, nfilhos,pai);
           /* printf("\n");*/
        }
  
    }
    if(arquivo == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }


    Menu(Raiz);
    Libera_Arvore(Raiz);
    return 0;
}
