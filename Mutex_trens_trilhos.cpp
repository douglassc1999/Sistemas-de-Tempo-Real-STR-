
// #include "thread7.hpp"

// http: pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_init.html

// Programa que sincroniza threads utilizando-se mutexes
// Para compilá-lo utilise: g++ -o thread7 thread7.cpp -lpthread


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void *thread_function(void *arg);
pthread_mutex_t m1; /* proteção para: work_area e time_to_exit */
void L(int trem, int trilho);

int main() {
    int res;
    pthread_t thread1, thread2;
    void *trem1, *trem2;
    void *thread_result;
    
    // ----- Criacao do multex m1 -----
    res = pthread_mutex_init(&m1, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }
    // ----- Criacao da thread 1 que executará a função trem1
    res = pthread_create(&thread1, NULL, trem1, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }
    // ----- Criacao da thread 2 que executará a função trem2
    res = pthread_create(&thread2, NULL, trem2, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }
     res = pthread_join(thread1, NULL, trem2, NULL);
     res = pthread_join(thread2, NULL, trem2, NULL);
    
     printf("");
     pthread_mutex_destroy(&m1);
    
}

void *thread_function(void *arg) {
    sleep(1);
    pthread_mutex_lock(&work_mutex);
    while(strncmp("fim", work_area, 3) != 0) {
        printf("THREAD() --> Seu texto tem %lu caracteres\n", strlen(work_area) -1);
        work_area[0] = '\0';
        pthread_mutex_unlock(&work_mutex);
        sleep(1);
        pthread_mutex_lock(&work_mutex);
        while (work_area[0] == '\0' ) {
            pthread_mutex_unlock(&work_mutex);
            sleep(1);
            pthread_mutex_lock(&work_mutex);
        }
    }
    time_to_exit = 1;
    work_area[0] = '\0';
    pthread_mutex_unlock(&work_mutex);
    pthread_exit(0);
}
