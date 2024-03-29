/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho 1 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

float *x;		// vetor para guardar pontos de x 
float *y;		// vetor para guardar pontos de y 
float *l;		// vetor para guardar os coef. de Lagrange
float xp;		// pto interpolador
int nthreads;	// numero de threads
int dim; 		// dimensao das estruturas de entrada


// funcao que as threads executarao
void* lagrange(void *arg){
	int id = (long int) arg;
	for(int i = id; i < dim; i+=nthreads)
		for(int j= 0; j < dim; j++)
			if(i!=j)
				l[i]=l[i]*(xp - x[j])/(x[i]-x[j]);		
	pthread_exit(NULL);
}

// fluxo principal
int main(int argc, char*argv[]){

	// ********************** INICIALIZAÇÃO ********************** 
	long int i,j;
	float yp=0;
   	double inicio, fim, delta1, delta2, delta3, delta4, ts, tc, aux;
	GET_TIME(inicio);
   	// leitura e avaliacao dos parametros de entrada
	if(argc<4){
		fprintf(stderr, "Digite: %s <numero de pontos> <ponto x> <numero threads> \n", argv[0]);
		return 1;}

	dim = atoi(argv[1]);
        xp = atoi(argv[2]);
	nthreads = atoi(argv[3]);
	
	if(nthreads>dim) nthreads=dim;

	// alocacao de memoria para as estruturas de dados
	x= (float*) malloc(sizeof(float)*dim);
	if(x==NULL){
		printf("ERRO\n");
		return 2;}
	y= (float*) malloc(sizeof(float)*dim);
	if(y==NULL){
		printf("ERRO\n");
		return 2;}
	l= (float*) malloc(sizeof(float)*dim);
	if(l==NULL){
		printf("ERRO\n");
		return 2;}

	for(i=0;i<dim;i++){
		x[i]=i+1;
		y[i]=i+11;
		l[i]=1;
		/*printf("%lf ",x[i]);
      	printf(" %lf\n",y[i]);*/
 	}//puts("");	
	GET_TIME(fim);
   	delta1 = fim - inicio;
  	
  	// ********************** SEQUENCIAL **********************
  	GET_TIME(inicio)
   	// Interpolação de Lagrange - SEQUENCIAL
   	for(i=0;i<dim;i++){
   		float p=1;
   		for(j=0;j<dim;j++)
   			if(i!=j)
   				p = p * (xp - x[j])/(x[i] - x[j]);
   		// printf("%lf ", p); // verificando se os coef de lagrange estão corretos
      	yp = yp + p * y[i];}
        //puts("");     	   	   	
  	printf("[SEQUENCIAL] Valor interpolado com %.3f é %.3f \n", xp, yp); // verifficando os ponto de interpolação
   	GET_TIME(fim);
   	delta2 = fim - inicio;
  

  	
  	// ********************** CONCORRENTE **********************
   	GET_TIME(inicio);
   	yp=0; //resetando o valor de yp para processamento do código concorrente 
   	
   	// alocacao das estruturas
   	pthread_t *tid; //identificadores das threads no sistema
	tid=(pthread_t*)malloc(sizeof(pthread_t)*nthreads);	
	if(tid==NULL) {puts("Erro"); return 2;}
	
	// criacao das threads
	for(i=0; i<nthreads;i++)
		if(pthread_create(tid+i,NULL,lagrange,(void*) i)){
			puts("Erro");
			return 3;}
	
	// espera pelo termino das threads
	for(i=0;i<nthreads;i++){
		pthread_join(*(tid+i),NULL);}
	
	/*for(i=0;i<dim;i++)
		printf("%lf  ",l[i]);
	puts("");*/ // verificando se os coef de lagrange estão corretos

	for(j=0;j<dim;j++){
		yp = yp + (l[j] * y[j]);}	
	printf("[CONCORRENTE] Valor interpolado com %.3f é %.3f.\n\n" ,xp, yp); // verifficando os ponto de interpolação
	GET_TIME(fim);
   	delta3 = fim - inicio;  		
   		
	// ********************** FINALIZAÇÃO ********************** 
   	GET_TIME(inicio);
   	// liberacao da memoria
	free(x);
	free(y);
	free(l);
	free(tid);
	GET_TIME(fim);
   	delta4 = fim - inicio;

   	
   	ts = delta1 + delta2 + delta4; // tempo sequencial total
   	tc = delta1 + delta3 + delta4; // tempo concorrente total
   	
   	
   	
   	printf("Tempo inicializacao: %lf\n", delta1); 
   	printf("Tempo algoritmo sequencial: %lf\n", delta2); // imprime na tela o tempo do trecho do processamento sequencial 
   	printf("Tempo algoritmo concorrente: %lf\n", delta3); // imprime na tela o tempo do trecho do processamento concorrente 
	  printf("Tempo finalizacao: %lf\n", delta4);
	  puts("");  	
   	printf("Tempo total Sequencial: %lf\n", ts);
   	printf("Tempo total Cocorrente: %lf\n", tc);
   	puts("");  	
   	aux = delta2/nthreads;
   	printf("Ganho real: %lf\n", ts/tc);
   	printf("Ganho esperado: %lf\n", ts/(aux+delta1+delta4)); 
    return 0;
}


