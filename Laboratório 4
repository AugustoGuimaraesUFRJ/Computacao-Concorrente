#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int controle = 0;
pthread_mutex_t lock;
pthread_cond_t cond_ex;
pthread_cond_t cond_ex1;

void *thread1(void *args){

    pthread_mutex_lock(&lock);
    if(controle<3){
	//printf("1: vai se bloquear...\n");
        pthread_cond_wait(&cond_ex1, &lock);
    }
    printf("Volte sempre!\n");
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *thread2(void *args){
    pthread_mutex_lock(&lock);
    if(controle==0){
	//printf("2: vai se bloquear...\n");
        pthread_cond_wait(&cond_ex, &lock);
    }
    printf("Fique a vontade\n");
    controle++;
    if(controle==3){
	//printf("2:  vai sinalizar a condicao \n");
	pthread_cond_signal(&cond_ex1);}
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}
void *thread3(void *args){
    pthread_mutex_lock(&lock);
    if(controle == 0){
	//printf("3: vai se bloquear...\n");
        pthread_cond_wait(&cond_ex, &lock);
    }
    printf("Sente-se por favor.\n");
    controle++;
    if(controle==3){
	//printf("3: vai sinalizar a condicao \n");
	pthread_cond_signal(&cond_ex1);}
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}
void *thread4(void *args){
    printf("Seja bem-vindo!\n");
    pthread_mutex_lock(&lock);
    controle++;
    //printf("4: controle = %d, vai sinalizar a condicao \n", controle );
    pthread_mutex_unlock(&lock);
    pthread_cond_broadcast(&cond_ex);
    pthread_exit(NULL);
}

int main(){

    pthread_t tid[4];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_ex, NULL);
    pthread_cond_init(&cond_ex1, NULL);

    if(pthread_create(&tid[0], NULL, thread1, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }
    if(pthread_create(&tid[1], NULL, thread2, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }
    if(pthread_create(&tid[2], NULL, thread3, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }
    if(pthread_create(&tid[3], NULL, thread4, NULL)) {
        fprintf(stderr, "Erro ao executar pthread_create().\n");
        return 1;
    }

    for(int thread = 0; thread < 4; thread++) {
        if(pthread_join(tid[thread], NULL)) {
            fprintf(stderr, "Erro ao executar pthread_join().\n");
            return 2;
        }
    }

    return 0;

}
