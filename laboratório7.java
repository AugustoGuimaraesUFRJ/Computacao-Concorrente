#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <semaphore.h>

sem_t condt1, condt2, condt3;

void *thread1(void *args){
    sem_wait(&condt2);
    sem_wait(&condt3);
    printf("Volte sempre!\n");
}

void *thread2(void *args){
    sem_wait(&condt1);
    printf("Fique a vontade\n");
    sem_post(&condt2);
    pthread_exit(NULL);
}
void *thread3(void *args){
    sem_wait(&condt1);
    printf("Sente-se por favor.\n");
    sem_post(&condt3);
    pthread_exit(NULL);
}
void *thread4(void *args){
    printf("Seja bem-vindo!\n");
    sem_post(&condt1);
    sem_post(&condt1);
    pthread_exit(NULL);
}

int main(){

    pthread_t tid[4];

  //inicia os semaforos
  sem_init(&condt1, 0, 0);
  sem_init(&condt2, 0, 0);
  sem_init(&condt3, 0, 0);

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
