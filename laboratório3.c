/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Módulo 1 - Laboratório: 3 */
/* Série Madhava–Leibniz */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include "timer.h"

long long int N; //numero de elementos da serie
int nthreads; //numero de threads

/* Função das threads
 * As somas foram feitas de forma invertida com o objetivo de tentar minimizar o erro, pois, assim,
 * cada thread começa somando números menores. O mesma logica foi utilizada para o cálculo sequencial.*/
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   double *somaLocal; //variavel local da soma de elementos
   somaLocal = (double*) malloc(sizeof(double));
   
   if(somaLocal==NULL) {exit(1);}

   long int tamBloco = N/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   if(id == nthreads-1) fim = N;
   else fim = ini + tamBloco; //trata o resto se houver

   //soma os elementos do bloco da thread
   for(long int i = fim - 1; i >= ini; i--){
      *somaLocal += pow(-1,i)*(1.0/(1.0+2.0*i)); 
   }
   //retorna o resultado da soma local
   pthread_exit((void *) somaLocal); 
}

//fluxo principal
int main(int argc, char *argv[]) {
   double somaSeq= 0; //soma sequencial
   double somaConc= 0; //soma concorrente
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema
   double *retorno; //valor de retorno das threads
   double tempo_1, tempo_2;

   //recebe e valida os parametros de entrada 
   if(argc < 3) {
       fprintf(stderr, "Digite: %s <dimensao da serie> <numero threads>\n", argv[0]);
       return 1; 
   }
   N = atoll(argv[1]);
   nthreads = atoi(argv[2]);

   //soma sequencial dos elementos
   GET_TIME(ini);
   for(long int i=N - 1; i >= 0; i--){
      somaSeq += pow(-1,i)*(1.0/(1.0+2.0*i));}
   GET_TIME(fim);
   tempo_1=fim-ini;
   printf("Tempo sequencial:  %lf\n", tempo_1);

   //soma concorrente dos elementos
   GET_TIME(ini);
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }

   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), (void**) &retorno)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
      //soma global
      somaConc += *retorno;
   }
   GET_TIME(fim);
   tempo_2=fim-ini;
   printf("Tempo concorrente:  %lf\n", tempo_2);

   // A medida que aumentamos o numero de elementos da serie podemos observar um aumento no ganho.
   printf("Ganho: %lf\n", tempo_1/tempo_2);

   /*Exibir os resultados
    *Os resultados coincidem. Em alguns casos, existem um diferença bastante pequena (de 0.00000000000001) entre eles*/
    printf("%.15f  -> Erro sequencial.\n", fabs(M_PI - 4*somaSeq));
    printf("%.15f  -> Erro concorrente.\n", fabs(M_PI - 4*somaConc));

   //libera as areas de memoria alocadas
   free(tid);
   return 0;
}
