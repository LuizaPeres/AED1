#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINHA 20

typedef struct streaming *pme;

struct streaming
{
    /*F: numero de filmes disponiveis no catalogo( coluna) e C:quantidade de clientes(linha) */
    int F, C;
    char genero;
    pme proximo;

};

typedef pme matriz[MAX_LINHA];

/*Inicializando a matriz esparsa */
void Inicializa(matriz M, int linha)
{
    int i;
    for(i=0; i < linha; i++)
    {
        M[i] = NULL;
    }
}
/*Função para inserir os dados na matrix esparsa*/
void Insere(matriz M, int Filme, int i, char genero)
{
    pme novo, p;
    /*novo é o nó que vai guardar o dado inserido*/
    novo=(pme)malloc(sizeof(struct streaming));
    novo->F = Filme;
    novo->genero = genero;
    novo ->proximo = NULL;
    if(M[i]== NULL)
    {
        M[i]= novo;
    }
    else
    {
        for(p = M[i]; p->proximo != NULL; p = p->proximo)
        {
          ;
        }
        p->proximo = novo;
    }
}
/*Imprime a matriz incluindo*/
void Imprime(matriz M, int C, int F)
{
    int i, j;
    pme aux;

    for(j=0; j<C; j++)
    {
        aux=M[j];
        for(i=0; i<F; i++)
        {
            if( aux!=NULL && aux->F==i+1)
            {
                printf("1");
                aux=aux->proximo;
            }
            else
            {
                printf("0");
            }
        }
        printf("\n");
    }
    printf("\n");
}
int Verifica_filme_repetido(matriz M, int i, int filme)
{
    pme aux;

    // scanf("%d", &filme);
    for(aux=M[i]; aux != NULL; aux = aux->proximo)
    {
        if(aux->F == filme)
        {
            printf("\nFilme ja inserido\n\nDigite um filme valido ");
            return 1;
        }
    }

    return 0;
}
int Escolha_genero(matriz M,char genero)
{
    /*gênero (‘A' para ação, ‘R'
    para romance, ’S' para suspense, ‘C' para comédia, ‘M' para musical, ‘D’ para drama, ‘F'
    para ficção, e ‘P' para policial).*/
    switch(genero)
    {
    case 'A':
        break;
    case 'R':
        break;
    case 'S':
        break;
    case 'C':
        break;
    case 'M':
        break;
    case 'D':
        break;
    case 'F':
        break;
    case 'P':
        break;
    default:
        printf("Genero invalido!!");
        return 1;
        break;
    }
    return 0;
}
/*Libera os espaços de memoria alocados para armazenar as listas*/
void Libera (matriz M, int Linha)
{
    pme p,q;
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
}

int main()
{
  pme aux;
  matriz M; /*vetor de lista*/
  /*C: linha e F: coluna*/
  int C, F, i, j, flag =0, maior =0;
  int filme_assistido =0, num_filme, posi_vetor;
  char genero;

    

  printf("Insira a quantidade de filmes disponiveis no catalogo: ");
  scanf("%d", &F);
  do
  {
    printf("Insira a quantidade de clientes do servico:");
    scanf("%d", &C);
  }
  while(C < 0 || C > MAX_LINHA);

  Inicializa(M, C); /*inicializando a matriz, colocando o valor de cada posição no meu vetor NULL*/

  for(i=0; i<C; i++)
  {
    printf("\nQuantos filmes o cliente %d ja assistiu?",i+1);
    scanf("%d", &filme_assistido);
    while( filme_assistido<0 || filme_assistido > F)
    {
      printf("\nQuantidade invalida!\nInsira valor de 1 ate %d: ",F);
      scanf("%d",&filme_assistido);
    }

    for(j=0; j<filme_assistido; j++)
    {   
      setbuf(stdin,NULL);
      printf("\nDigite o numero do %d º filme assistido: ", j+1);
      scanf("%d", &num_filme);
      /*Verificando se o valor do filme excedde a quantidade de filmes da streaming*/
      while(num_filme <0 || num_filme > F)
      {
        printf("\nFilme invalido\nInsira outro filme \nDigite o numero do %d º filme assistido: ", j+1);
        scanf("%d",&num_filme);
      }
      while(Verifica_filme_repetido( M,i,num_filme)==1 )
      {
        /*caso, o numero do filme já tenha sido visto pelo cliente, a função verifica pedira um novo numero, e logo depois fara a verificação para ver se o numero não excede o numero de filme da streaming*/
        scanf("%d",&num_filme);
        while(num_filme <0 || num_filme > F)
        {
          printf("\nFilme invalido\nInsira outro filme \nDigite o numero do %d º filme assistido: ", j+1);
          scanf("%d",&num_filme);
        }
      }
      printf("\nDigite o genero do filme:");
      scanf(" %c", &genero);
      while(Escolha_genero(M,genero)==1)
      {
        printf("\nDigite o genero do filme:");
        scanf(" %c", &genero);
      }
      Insere(M,num_filme,i, genero);
    }
  }
  printf("\nMatriz inteira:\n");
  Imprime(M,C,F);

  printf("\nMatriz condensada\n");
  for(i=0; i<C; i++)
  {
    aux=M[i];
    printf("Cliente %d:\n", i+1);
    printf("Filmes assistidos (filme e genero)\n");

    while( aux!=NULL )
    {
      printf("%d %c\n",aux->F,aux->genero);
      aux=aux->proximo;
    }
    printf("\n");
  }
  aux = NULL;
  int M2[8];
  for(i=0; i<8; i++)
    { /*um vetor para incrementar cada genero de filme*/
      M2[i]=0;
    }
  for(i=0; i<C; i++){
      //for(p = m[i]; p != NULL; p = p->prox)
      for(aux = M[i]; aux != NULL; aux = aux->proximo){
      // percorrendo a lista e somando os valores encontrados de cada genero em sua posicao do vetor
      if (aux!= NULL){
      switch(aux->genero){
        case 'A':
          M2[0]++;
          break;
        case 'R':
          M2[1]++;
          break;
        case 'S':
          M2[2]++;
          break;
        case 'C':
          M2[3]++;
          break;
        case 'M':
          M2[4]++;
          break;
        case 'D':
          M2[5]++;
          break;
        case 'F':
          M2[6]++;
          break;
        case 'P':
          M2[7]++;
          break;
        default:
          break;
      }
    }
  }
}
  //verificando qual repeticao é maior
  for(i = 7; i >= 0; i--)
  {
    if(M2[i] > maior)
    {
      maior = M2[i];
      posi_vetor = i;// aqui ele guarda qual posicao é a do genero q ganhou
    }
  }

   switch(posi_vetor){
        case 0:
          printf("\nO genero de filme mais assistido foi: Acao");
          break;
        case 1:
          printf("\nO genero de filme mais assistido foi: Romance");
          break;
        case 2:
          printf("\nO genero de filme mais assistido foi: Suspense");
          break;
        case 3:
          printf("\nO genero de filme mais assistido foi: Comédia");
          break;
        case 4:
          printf("\nO genero de filme mais assistido foi: Musical");
          break;
        case 5:
          printf("\nO genero de filme mais assistido foi: Drama");
          break;
        case 6:
          printf("\nO genero de filme mais assistido foi: Ficcao");
          break;
        case 7:
          printf("\nO genero de filme mais assistido foi: Policial");
          break;
        default:
          break;
   }
    Libera(M,C);
    return 0;
}
