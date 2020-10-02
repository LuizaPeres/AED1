#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Lista2
{
    char letra;
    struct Lista2 *anterior;
    struct Lista2 *proximo;
} TLista2;

typedef TLista2 *PLista2;
PLista2 Inicia_Lista()
{
    return NULL;
}

/*Função para inserir no fim da lista*/
PLista2 Insere(PLista2 Lista, char letra)
{
    PLista2 novo = (PLista2)malloc(sizeof(TLista2));
    if(novo == NULL)
        return NULL;
    novo->letra =letra;
    novo->proximo = NULL;
    /*condição para inserir a primeira letra*/
    if(Lista == NULL)
    {
        novo ->anterior = NULL;
        Lista = novo;
        return novo;
    }
    else
    {
        PLista2 aux;
        aux = Lista;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux ->proximo = novo;
        novo ->anterior = aux;
    }
    return Lista;
}
PLista2 Busca_letra(PLista2 Lista, char letra)
{
    PLista2 p;
    for(p = Lista; p!=NULL; p = p->proximo)
    {
        if(p->letra ==letra)
        {
            return p;
        }
    }
    return NULL;
}
void trocaletra(PLista2 letra1, PLista2 letra2,PLista2 Lista)
{
    char aux;
    aux = letra1->letra;
    letra1->letra =letra2->letra;
    letra2->letra=aux;
    return;  
}
void Imprime_Lista(PLista2 Lista)
{
    PLista2 p;

    if(Lista == NULL)
    {
        printf("Lista vazia!!");
        return;
    }
    p = Lista;
    do
    {
        printf("%c ", p->letra);
        p = p->proximo;
    }
    while(p != NULL);
}
void Libera_lista(PLista2 Lista)
{
    PLista2 paux = Lista;
    PLista2 q;

    while(paux != NULL)
    {
        q= paux;
        paux = paux ->proximo;
        free(q);
    }
    printf("\nFim");
    free(Lista);
}
int main()
{
    PLista2 Jogo;
    char palavra[15], aux, letra1, letra2;
    int i;

    Jogo = Inicia_Lista();

    printf("Digite uma palavra com 2 letras trocadas\n");
    scanf("%s", palavra);

    for(i=0; i<strlen(palavra); i++)
    {
        aux = palavra[i];
        Jogo = Insere(Jogo, aux);
    }
    printf("Antes:\n");
    Imprime_Lista(Jogo);
    printf("\nDigite a letra que deseja inverter: ");
    scanf(" %c", &letra1);
    printf("\nDigite a letra que deseja inverter: ");
    scanf(" %c", &letra2);
    /*Chamando a função busca para encontrar as letras que quero trocar de posiçaõ */
    PLista2 aux1 = Busca_letra(Jogo, letra1);
    PLista2 aux2 = Busca_letra(Jogo, letra2);
    /* Trocando as letras de posição*/
    trocaletra(aux1, aux2,Jogo);

    printf("\nDepois:\n");
    Imprime_Lista(Jogo);/*imprimindo a palavra correta*/

    Libera_lista(Jogo);
    return 0;
}
