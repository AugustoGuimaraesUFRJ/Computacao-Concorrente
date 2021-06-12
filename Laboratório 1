//Ajeitar o for
90/100

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NTHREADS  2 //Total de threads a serem criadas
#define tam 10000
int matriz[tam];

void preencher(){
	for(int i = 0; i<tam; i++){
		matriz[i]=1; // Para facilitar preenchi a matriz apenas com valor 1
	}
}
//Cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int comeco, fim;
} t_Args;

//Funcao executada pelas threads
void *somar (void *arg) {
  t_Args *args = (t_Args *) arg;
  for(args->comeco; args->comeco<args->fim; args->comeco++){
		matriz[args->comeco]+=1;}
  pthread_exit(NULL);
}

//Funcao principal do programa
int main() {
  preencher();

  pthread_t tid_sistema[NTHREADS]; 

  t_Args *arg; //Receberá os argumentos para a thread

  for(int i =0; i<NTHREADS;i++){
		(arg+i)->comeco=0+(tam/2)*i;
		(arg+i)->fim=(tam/2)+(tam/2)*i;
  		if (pthread_create(&tid_sistema[NTHREADS], NULL, somar, (void*)(arg+i))) {
      			printf("--ERRO: pthread_create()\n"); exit(-1);}}

 //espera pelo termino das threads
 for(int i=0;i<NTHREADS;i++){
	pthread_join(tid_sistema[NTHREADS],NULL);}


  
  int resultado=0;
	for(int j =0;j<tam;j++){
		if(matriz[j]!=2){
			resultado+=1;}}
  if(resultado==0)
	printf("Tudo certo!");
  else
	printf("Algo deu errado!");
  return 0;
}
