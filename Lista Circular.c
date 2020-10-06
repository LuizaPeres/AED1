#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TJogador
{
    int jogador, pontuacao, resultado;
} Jogador;

typedef struct Lista
{
    Jogador dados;
    struct Lista *proximo;
} TLista;

typedef TLista *PLista;

PLista Inicia_Lista()
{
    return NULL;
}

/*Função inserção no fim da lista*/
PLista Insere(PLista Ultimo,int jogador,int pontuacao)
{
    PLista novo = (PLista)malloc(sizeof(TLista));
    novo->dados.jogador = jogador;
    novo->dados.pontuacao = pontuacao;

    if(Ultimo==NULL)
    {
        novo ->proximo = novo;
    }
    else
    {
        novo->proximo = Ultimo->proximo;
        Ultimo->proximo = novo;
    }
    Ultimo = novo; /*Pois estou inserindo no final*/
    return Ultimo;
}
void Imprime_Lista(PLista Ultimo)
{
    PLista p;

    if(Ultimo != NULL)
    {
        p = Ultimo ->proximo; /*percorre o elemento até alcançar novamente o inicio*/

        do
        {
            printf("\njogador  %d  pontuacao = %d",p->dados.jogador, p->dados.pontuacao);/* imprime informação do nó */
            p = p->proximo;
        }
        while(p!=Ultimo->proximo);
    }
}/*Função que elimina o jogador que tem pontuação maior que 21*/
void Elimina_jogador(PLista Ultimo, int jogador)
{
    PLista p;
    PLista anterior = Ultimo;
    if(Ultimo == NULL)
    {
        printf("Sem jogadores\n\n");
    }
    //printf("removendo %d - %d pontos\n", Ultimo->dados.jogador,Ultimo->dados.pontuacao);
    for (p = Ultimo->proximo; p->proximo != Ultimo; p = p->proximo)
    {
        //printf("%d \n", p->dados.jogador);
    }

    p->proximo=Ultimo->proximo;
    printf("Jogador %d eliminado\n", Ultimo->dados.jogador);
    Imprime_Lista(Ultimo);
    free(Ultimo);
    return;
    /*verifica se achou o jogador*/
    if(Ultimo == anterior)
    {
        Ultimo->proximo = p->proximo;/*retira o jogador do inicio da lista*/
    }
    else
    {
        anterior->proximo = p->proximo;/*retira o jogador do meio da lista*/
    }

    free(p);
}
/*Funcao que libera os espacos alocado*/
void Libera(PLista Ultimo)
{
    PLista paux = Ultimo->proximo;
    PLista q = Ultimo;

    while(paux!= Ultimo)
    {
        q = paux;
        paux = paux ->proximo;
        free(q);
    }
    printf("\nFim de jogo!");
    free(Ultimo);
}
/*Função para a leitura das cartas*/
int Le_carta(PLista aux)
{
    char letra_carta[2];


    scanf("%s", letra_carta);

    if(strcmp(letra_carta,"A")==0)
        aux->dados.pontuacao+= 11;
    else if(strcmp(letra_carta,"Q")==0 || strcmp(letra_carta,"K")==0 || strcmp(letra_carta,"J")==0 || strcmp(letra_carta,"10")==0)
        aux->dados.pontuacao+=10;
    else if(letra_carta[0]>='2' && letra_carta[0]<='9' && letra_carta[1]=='\0')
        aux->dados.pontuacao+= letra_carta[0]- '0' ;
    else
        return 0;

    return 1;
}
int main()
{
    PLista Jogo;
    PLista aux;/*auxiliar que vai apontar para o novo jogador*/
    PLista proximo;
    int num_jogador = 0, pontuacao = 0, i, a=1;
    /*Definindo a quantidade de jogadores*/
    printf("Digite a quantidade de jogadores: ");
    scanf("%d", &num_jogador);

    Jogo = Inicia_Lista();
    /*inserindo os jogadores antes de comecar a rodada*/
    for(i=0; i<num_jogador; i++)
    {
        Jogo = Insere (Jogo, i+1, 0);
    }
    i = 0;
    PLista comeco = Jogo->proximo;

    PLista AuX2=comeco->proximo;
    aux=comeco;
    while( aux->dados.pontuacao != 21)
    {

        /*Distribuindo as cartas para os jogadores e calculando sua pontuação*/
        printf("\nDigite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q):\n");
        a=Le_carta(aux);
        /*condição para caso o valor da carta seja inválido*/
        while(a==0)
        {
            printf("\nValor invalido!! Digite novamente um novo valor");
            a=Le_carta(aux);
        }
        if(aux->dados.pontuacao==21)
        {
            printf("Jogador vencedor: %d. Pontuacao: %d",aux->dados.jogador, aux->dados.pontuacao);
            return 0;
        }
        if(aux->dados.pontuacao>21)
        {
            if(comeco == aux)
                comeco=aux->proximo;
            Elimina_jogador(aux,0);

        }
        if(comeco == aux->proximo)
        {
            i = 0;
            printf("\nSituacao da lista: ");
            Imprime_Lista(Jogo);
            printf("\n");
        }
        aux=aux->proximo;

    }
    /*Caso fique apenas um jogador no jogo, ele será o vencedor*/
    if (aux->proximo==aux)
    {
        printf("Jogador vencedor: %d. Pontuacao: %d",aux->dados.jogador, aux->dados.pontuacao);
        return 0;
    }

    Libera(Jogo);
    return 0;
}


