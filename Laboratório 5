#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

/* Variaveis globais */
int bloqueadas = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
int *a; //vetor para soma prefixo concorrente
int *b; //vetor para soma prefixo sequencial
int Nthreads;
int n;  //tamanho vetor

//funcao barreira
void barreira(int nthreads) {
    pthread_mutex_lock(&x_mutex); //inicio secao critica
    if (bloqueadas == (nthreads-1)) { 
      //ultima thread a chegar na barreira
      pthread_cond_broadcast(&x_cond);
      bloqueadas=0;
    } else {
      bloqueadas++;
      pthread_cond_wait(&x_cond, &x_mutex);
    }
    pthread_mutex_unlock(&x_mutex); //fim secao critica
}

//funcao das threads
void *tarefa (void *arg) {
  int id = *(int*)arg;
  int auxiliar = 0;
  int passo=1;
  float lg;
  while(passo<n+1){
    lg=log10(passo)/log10(2); // faz com que só saiam passos potencias de 2
    if(lg<=(int)lg){
        if((id-passo)<0){       
		auxiliar=0;}
	else{
		auxiliar = a[id-passo];}
        /*if(auxiliar==0){
		printf("T%d (%d - %d) -->> posicao invalida, não faz nada\n", id,id,passo);}
        else{
		printf("T%d (%d - %d) -->> na posicao %d auxiliar = %d\n", id,id,passo,(id-passo),auxiliar);}*/
        //Para garantir que todas leem antes de alguma delas alterar a sua posicao
    	barreira(Nthreads);
    	a[id]= auxiliar + a[id];
	//printf("T%d = %d\n", id,a[id]);
    	//Para garantir que todas escrevem antes de alguma delas ler na proxima iteração
    	barreira(Nthreads);}
    passo++;
  }
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  if(argc<2){
		fprintf(stderr, "Digite: %s <numero de pontos> \n", argv[0]);
		return 1;}
  int m = atoi(argv[1]);
  n = pow(2,m);
  Nthreads = n;
  pthread_t threads[Nthreads];
  int id[Nthreads];

  //Aloca os vetores
  a= (int*) malloc(sizeof(int)*(n));
  if(a==NULL){
	printf("ERRO\n");
	return 2;}
  b= (int*) malloc(sizeof(int)*(n));
  if(b==NULL){
	printf("ERRO\n");
	return 2;}


  // Inicializa os vetores
  for(int i=0;i<n;i++){
		a[i]=i+1;
		b[i]=i+1;}


  //Soma prefixo sequencial
  for(int i=1; i<n+1; i++)
		b[i] = b[i] + b[i-1];

  

  //Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao 
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  //Cria as threads 
  for(int k=0;k<Nthreads;k++) {
     id[k]=k;
     pthread_create(&threads[k], NULL, tarefa, (void *) &id[k]);
  }

  // Espera todas as threads completarem 
  for (int i = 0; i < Nthreads; i++) {
    pthread_join(threads[i], NULL);
  }

  // Desaloca variaveis e termina 
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);

  /*Imprime os vetores modificados
  printf("\n");
  for(int j = 0; j<n ; j++){
	printf("%d\n",a[j]);}
  printf("\n");
  for(int j = 0; j<n ; j++){
	printf("%d\n",b[j]);}
  printf("\n");*/

  // Verifica se a soma esta correta
  int re=0;
  for(int p = 0; p<n ; p++){
	if(a[p]!=b[p]){
		re++;}
	}
  if(re==0){
	printf("Soma correta!\n");}
  else{
	printf("Algo deu errado!\n");}
  return 0;
}
