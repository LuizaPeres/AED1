#include <stdio.h>
#include <stdlib.h>

 //Função para contar o numero de votos
 
  void Num_votos(int valor, int *vetor){

    *(vetor+(valor-1)) = *(vetor+(valor-1)) + 1;
 }

 //Função para retornar o candidato com maior numero de voto
 void Maior_num_votos( int candidatos, int *v,int N)
 {
    int a = 0;
    int maior = 0;
    for(a=0; a <= N ; a++){
      if(*(v+a) >= maior){
        candidatos = a+1;
        maior = *(v+a);
        
      }
    }
    printf("\nO candidato que ganhou a eleicaoo com o maior numero de votos contabilizando %d votos foi o candidato %d! ", maior, candidatos);
  
 }
 
int main(void) {

  int aux=1,i,N=0;
  int *votos, candidatos=0 ;

  printf("Digite a quantidade de candidatos:");
  scanf("%d",&N);

  if(votos == NULL){
    printf("Não foi possivel alocar o vetor");
    exit(0);
  }

  votos = (int*)malloc((N+1)*sizeof(int));

  //Para meu vetor começar sempre a contabilizar do 0 
  for(i=0; i < N; i++){
    *(votos+i) = 0;
  }


while(aux > 0)
{
  printf("\nDigite seu voto:");
  scanf("%d",&aux);

  if(aux > 0 && aux <= N)
    Num_votos(aux,votos);
  
  if(aux > N)
    printf("\nEsse numero de candidato nao existe, digite outro!\n");
}

 //Chama a função para ver o candidato ganhador
 Maior_num_votos(candidatos,votos,N);

  free(votos);
  return 0;
  
}
