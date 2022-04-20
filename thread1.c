#include<stdio.h>
#include<pthread.h>

#define TAMANHO 1000
#define NTHREADS 2

int vetor[NTHREADS];

//funcao que a thread ira executar
void * tarefa (void * arg) {
   int ident = * (int *) arg;
   for(int i=ident*500; i<ident*500+500; i++){
     vetor[i]= vetor[i]*vetor[i];
   }
   pthread_exit(NULL);
}

//funcao principal
int main(void) {
    pthread_t tid[NTHREADS]; //identificador da thread no sistema
    int ident[NTHREADS]; //identificador local da thread
    //cria as threads
    for(int i=0; i<TAMANHO; i++){
      vetor[i] = i;
    }

    for(int i=1; i<=NTHREADS; i++) {
       ident[i-1] = i-1;
       if (pthread_create(&tid[i-1], NULL, tarefa, (void *)&ident[i-1]))
          printf("ERRO -- pthread_create\n");
    }
    //espera as threads terminarem
    for(int i=0; i<NTHREADS; i++) {
       if (pthread_join(tid[i], NULL))
          printf("ERRO -- pthread_join\n");
    }
    //imprimir o vetor de identificadores
    for(int i=0; i<TAMANHO; i++)
       printf("Posição %d : %d \n", i, vetor[i]);
    printf("\n");

    //desvincula o termino da main do termino programa
    //pthread_exit(NULL);
    return 0;
}
