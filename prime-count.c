/* Disciplina: Computacao Concorrente */
/* Atividade 6: Produtor/Consumidor usando semáforos */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <math.h>

long long int *BUFFER;
int IN = 0;
int OUT = 0;
int M;

sem_t EMPTY;
sem_t FULL;
sem_t MUTEX;

int *count_primos;
int C;

// Uncomment if you want to know when threads end
// #define PRINT_THREAD_END

int ehPrimo(long long int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0) return 0;
    return 1;
}

void *produtor(void *arg) {
    long long int N = (long long int)arg;
    for (int i = 1; i <= N; i++) {
        sem_wait(&EMPTY);
        sem_wait(&MUTEX);
        BUFFER[IN] = i;
        IN = (IN + 1) % M;
        sem_post(&MUTEX);
        sem_post(&FULL);
    }
    for (int i = 0; i < C; i++) {
        sem_wait(&EMPTY);
        sem_wait(&MUTEX);
        BUFFER[IN] = -1;
        IN = (IN + 1) % M;
        sem_post(&MUTEX);
        sem_post(&FULL);
    }
    pthread_exit(NULL);
}

void *consumidor(void *arg) {
    long long int id = (long long int) arg;
    int total_local = 0;
    while (1) {
        sem_wait(&FULL);
        sem_wait(&MUTEX);
        long long int val = BUFFER[OUT];
        OUT = (OUT + 1) % M;
        sem_post(&MUTEX);
        sem_post(&EMPTY);

        if (val == -1) break;
        if (ehPrimo(val))
            total_local++;
    }
    count_primos[id] = total_local;

    #ifdef PRINT_THREAD_END
    printf("Consumidor %lld terminou com %d primos.\n", id + 1, total_local);
    #endif

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    long long int N;
    long long int i;
    if (argc < 4) {
        fprintf(stderr, "Digite: %s <valor de N> <tamanho M do buffer> <quantidade de consumidores C> \n", argv[0]);
        return 1;
    }
    N = atoll(argv[1]);
    M = atoi(argv[2]);
    C = atoi(argv[3]);

    BUFFER = malloc(sizeof(long long int) * M);
    count_primos = calloc(C, sizeof(int));

    sem_init(&EMPTY, 0, M);
    sem_init(&FULL,  0, 0);
    sem_init(&MUTEX, 0, 1);

    pthread_t tid_prod;
    pthread_t *tid_cons = malloc(sizeof(pthread_t) * C);

    pthread_create(&tid_prod, NULL, produtor, (void *) N);

    for (i = 0; i < C; i++) {
        pthread_create(&tid_cons[i], NULL, consumidor, (void *) i);
    }

    pthread_join(tid_prod, NULL);
    for (i = 0; i < C; i++)
        pthread_join(tid_cons[i], NULL);

    int total_primos = 0;
    int vencedor = 0;
    for (i = 0; i < C; i++) {
        total_primos += count_primos[i];
        if (count_primos[i] > count_primos[vencedor])
            vencedor = i;
    }

    printf("Total de primos encontrados: %d\n", total_primos);
    printf("Consumidor vencedor: %d\n", vencedor + 1);

    sem_destroy(&EMPTY);
    sem_destroy(&FULL);
    sem_destroy(&MUTEX);
    free(BUFFER);
    free(count_primos);
    free(tid_cons);

    return 0;
}

