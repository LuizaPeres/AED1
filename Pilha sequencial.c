#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXTAM 50
//Cada célula de uma pilha contém um item da pilha e um apontador para outra célula
typedef struct TipoCelula *TipoApontador;

struct TipoCelula
{
    char dado;
    TipoApontador proximo;
} TipoCelula;

typedef struct
{
    TipoApontador topo;
    int Tamanho;//O campo tamanho evita a contagem do num de itens da função tamanho
} TPilha;

// Criação da pilha
void CriaPilha(TPilha *pPilha)
{
    pPilha ->topo = NULL;
    pPilha ->Tamanho = 0;
}
int Tamanho_pilha(TPilha *pPilha)
{
    return pPilha->Tamanho;
}

//Empilhando na pilha com a função push
int push(TPilha *pPilha, char x)
{
    TipoApontador NovaCelula;
    NovaCelula = (TipoApontador)malloc(sizeof(TipoCelula));
//O item dessa NovaCelula será o item recebido como parâmetro
//de função
    NovaCelula -> dado =x;
    NovaCelula ->proximo = pPilha ->topo;
//Atualizando o topo da pilha
    pPilha ->topo =NovaCelula;
//Número de células na pilha
    pPilha ->Tamanho++;

    return 1;

}
//Usando a função pop para desempilhar
int pop(TPilha *pPilha, char *px)
{
    TipoApontador Aux;
//Verifica se a pilha esta vazia
    if(pPilha ->Tamanho == 0)
    {
        printf("A pilha esta vazia!");
        return 0;
    }
    Aux = pPilha ->topo;
    pPilha ->topo = Aux ->proximo;//Atualizando o topo
    *px = Aux ->dado;
    pPilha ->Tamanho--;
    free(Aux);// Liberando o espaço da memória
    return 1;
}
void Conv_Posfixa(TPilha *Pilha,char op[],TPilha *Resultado)
{
    int i;
    char X;

    //Analisando cada caractere da string
    for(i=0; i < strlen(op); i++)
    {
        switch(op[i])
        {
        case ' ':
            break;
        case '^':
        {
            while (Pilha->topo != NULL && Pilha->topo->dado == '^')
            {
                pop(Pilha, &X);
                printf("%c",X);
                push(Resultado, X);
            }
            push(Pilha,'^');
            break;
        }
        case '*':
        {
            while (Pilha->topo != NULL && (Pilha->topo->dado == '/' || Pilha->topo->dado == '*' || Pilha->topo->dado == '^'))
            {
                pop(Pilha, &X);
                printf("%c",X);
                push(Resultado, X);
            }
            push(Pilha,'*');
            break;
        }
        case '/':
        {
            while (Pilha->topo != NULL && (Pilha->topo->dado == '*' || Pilha->topo->dado == '/' || Pilha->topo->dado == '^'))
            {
                pop(Pilha, &X);
                printf("%c",X);
                push(Resultado, X);
            }
            push(Pilha,'/');
            break;
        }
        case '+':
        {
            while (Pilha->topo != NULL && (Pilha->topo->dado == '*' || Pilha->topo->dado == '/' || Pilha->topo->dado == '^' || Pilha->topo->dado == '+' || Pilha->topo->dado == '-'))
            {
                pop(Pilha, &X);
                printf("%c",X);
                push(Resultado, X);
            }
            push(Pilha,'+');
            break;
        }
        case '-':
        {
            while (Pilha->topo != NULL && (Pilha->topo->dado == '*' || Pilha->topo->dado == '/' || Pilha->topo->dado == '^' || Pilha->topo->dado == '+' || Pilha->topo->dado == '-'))
            {
                pop(Pilha, &X);
                printf("%c",X);
                push(Resultado, X);
            }
            push(Pilha,'-');
            break;
        }
        case '(':
        {
            push(Pilha,'(');
            break;
        }
        case ')':
        {
            while(Pilha->topo != NULL && Pilha->topo->dado != '(')
            {
                pop(Pilha, &X);
                printf("%c",X);
                push(Resultado, X);
            }
            pop(Pilha, &X);
            break;
        }
        default:
        {
            printf("%c",op[i]);
            push(Resultado, op[i]);
            break;
        }
        }
    }
    while(Pilha->topo != NULL)
    {
        pop(Pilha, &X);
        printf("%c",X);
        push(Resultado, X);
    }
} //Função para calcular a operação, nessa função crio uma string para armazenar os dados da operação na pilha
void imprimeResultado(TPilha *Resultado)
{   //t é para armazernar o tamanho do vetor
    int t=0, i, j = Resultado->Tamanho-1;
    char x, result[MAXTAM];
    double a = 0, b = 0;
    while(Resultado->topo != NULL)//Desempilho minha pilha para fazer uma string
    {
        pop(Resultado, &x);
        //Coloco um dado que desempilhei na posição j do meu vetor e depois diminui o j.
        result[j] = x;
        j--;
        t++; //Toda vez que desempilho,aumento 1 no t
    }
    for (i=0; i < t; i++)
    {
        switch(result[i])
        {
        case '^':
            pop(Resultado, &x);
            b = x - 48; //A irá receber o valor convertido de char para double, usasse -48 para compensação na tabela ASCII
            pop(Resultado, &x);
            a = x - 48;
            a = pow(a, b);
            x = a + 48; //Conversão de Double para Char
            push(Resultado, x); 
            break;
        case '*':
            pop(Resultado, &x);
            b = x - 48;
            pop(Resultado, &x);
            a = x - 48;
            a = a * b;
            x = a + 48;
            push(Resultado,x);
            break;
        case '/':
            pop(Resultado, &x);
            b = x - 48;
            pop(Resultado, &x);
            a = x - 48;
            a = a / b;
            x = a + 48;
            push(Resultado, x);
            break;
        case '+':
            pop(Resultado, &x);
            b = x - 48;
            pop(Resultado, &x);
            a = x - 48;
            a = a + b;
            x = a + 48;
            push(Resultado,  x);
            break;
        case '-':
            pop(Resultado, &x);
            b = x - 48;
            pop(Resultado, &x);
            a = x - 48;
            a = a - b;
            x = a + 48;
            push(Resultado,x);
            break;
        default:
            push(Resultado, result[i]);
            break;
        }
    }
    pop(Resultado, &x);
    a= x-48;
    printf("\n%.2lf\n", a);
}
int main()
{
// A pilha Resultado mando para a função Conv_Posfixa, pois todo valor que eu imprimir já empilho nela.
    TPilha Pilha, Resultado;
    char op[MAXTAM];

    CriaPilha(&Pilha);
    CriaPilha(&Resultado);

    printf("\nDigite a operacao infixa: ");
    scanf("%[^\n]s",op);
    printf("\nA Operacao Posfixa eh: ");
    Conv_Posfixa(&Pilha, op, &Resultado);
    printf("\n O resultado da operacao eh: ");
    imprimeResultado(&Resultado);
    return 0;
}
