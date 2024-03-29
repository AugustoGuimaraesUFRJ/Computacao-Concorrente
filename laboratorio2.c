/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Módulo 1 - Laboratório: 2 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

float *mat_1;   //primeira matriz
float *mat_2;   //segunda matriz
float *saida; // matriz de saida
float *verificar; // verificar se a multiplicação ta certa
int nthreads; //numero de threads

typedef struct{
	int id; // identificador do elemento que a thread ira processar
	int dim; // dimensao das estruturas de entrada
}tArgs;

//funcao que as threads executarao
void* tarefa(void *arg){
	tArgs *args = (tArgs*) arg;
	for(int i = args->id;i<args->dim;i+=nthreads){
		for(int j= 0; j<args->dim;j++){
			for(int k=0;k<args->dim;k++){
				saida[i*args->dim+j]+=mat_1[i*args->dim+k]*mat_2[k*args->dim+j];}}}
	pthread_exit(NULL);
}

//fluxo principal
int main(int argc, char*argv[]){
	int dim; //dimensao da matriz de entrada
	int i;
	int j;
	pthread_t *tid; //identificadores das threads no sistema
	tArgs *args;//identificadores locais das threads e dimensao
   	double inicio, fim, delta;

	GET_TIME(inicio);
   	//leitura e avaliacao dos parametros de entrada
	if(argc<3){
		printf("Faltam parametros");
		return 1;}

	dim = atoi(argv[1]);
	nthreads = atoi(argv[2]);
	if(nthreads>dim) nthreads=dim;

	//alocacao de memoria para as estruturas de dados
	mat_1 = (float*) malloc(sizeof(float)*dim*dim); 
	if(mat_1==NULL){
		printf("ERRO\n");
		return 2;}
	mat_2= (float*) malloc(sizeof(float)*dim*dim); 
	if(mat_2==NULL){
		printf("ERRO\n");
		return 2;}
	saida= (float*) malloc(sizeof(float)*dim*dim); 
	if(saida==NULL){
		printf("ERRO\n");
		return 2;}

	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			mat_1[i*dim+j]=j+i;
			mat_2[i*dim+j]=j;
			saida[i*dim+j]=0;}}
	GET_TIME(fim);
   	delta = fim - inicio;
  	printf("Tempo inicializacao:%lf\n", delta);
	
	//multiplicacao da matriz pelo vetor
   	GET_TIME(inicio);
   	//alocacao das estruturas
	tid=(pthread_t*)malloc(sizeof(pthread_t)*nthreads);
	if(tid==NULL) {puts("Erro"); return 2;}
	args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
	if(args==NULL) {puts("Erro"); return 2;}
	//criacao das threads
	for(int i =0; i<nthreads;i++){
		(args+i)->id=i;
		(args+i)->dim=dim;
		if(pthread_create(tid+i,NULL,tarefa,(void*)(args+i))){
			puts("Erro");
			return 3;}
	}
	//espera pelo termino das threads
	for(int i=0;i<nthreads;i++){
		pthread_join(*(tid+i),NULL);}

	GET_TIME(fim);   
   	delta = fim - inicio;
   	printf("Tempo multiplicacao:%lf\n", delta);
	
	//Para nao interferir na medição do tempo, a matriz verificar foi alocada e inicializada separadamente
	verificar= (float*) malloc(sizeof(float)*dim*dim); 
	if(verificar==NULL){
		printf("ERRO\n");
		return 2;}
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			verificar[i*dim+j]=0;}}
	for( i=0;i<dim;i++){
		for( j=0;j<dim;j++){
			for(int k=0;k<dim;k++)
				verificar[i*dim+j]+=mat_1[i*dim+k]*mat_2[k*dim+j];}}
	
	//Imprimir as matrizes para conferir
	/*for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%.1f ",mat_1[i*dim+j]);}
		printf("\n");}
	printf("\n");
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%.1f ",mat_2[i*dim+j]);}
		printf("\n");}
	printf("\n");
	for( i=0;i<dim;i++){
		for( j=0;j<dim;j++){
			printf("%.1f ",saida[i*dim+j]);}
		printf("\n");}
	printf("\n");
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%.1f ",verificar[i*dim+j]);}
		printf("\n");}
	printf("\n");*/


	int resultado=0;
	for( i=0;i<dim;i++){
		for( j=0;j<dim;j++){
			if(verificar[i*dim+j]!=saida[i*dim+j])
			resultado+=1;}}
	if(resultado==0){
		printf("--------Tudo certo--------\n");}
	else{
		printf("-------Algo deu errado-------\n");}

	//liberacao da memoria
   	GET_TIME(inicio);
	free(mat_1);
	free(mat_2);
	free(saida);
	free(args);
	free(tid);
	GET_TIME(fim);  
	free(verificar); 
   	delta = fim - inicio;
   	printf("Tempo finalizacao:%lf\n", delta);
	return 0;
}
