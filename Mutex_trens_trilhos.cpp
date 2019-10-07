#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "BlackGPIO/BlackGPIO.h"
#include "../ADC/Adc.h"
#include <unistd.h>
#include <vector>
#include <array>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

/*
  Pedro Victor
  Francisco Kennedi 
  Projeto: controle de região crítica com mutex, 
           no contexto da movimentação de trens

  Usar -lpthread para compilar

Esquemático:
	
	TRILHO 1                 TRILHO 2                  TRILHO 3
		 Região Crítica            Região Crítica
	Trem2_T1-----------------Trem2_T2-------------------Trem2_T3
Trem1_T1	Trem3_T1  Trem1_T2	  Trem3_T2  Trem1_T3        Trem3_T3
	Trem4_T1------------------Trem4_T2-------------------Trem4_T3	

*/

using namespace BlackLib;

int tempo_T1 = 0;
int tempo_T2 = 0;
int tempo_T3 = 0;

void *thread_function_T1(void *arg);
void *thread_function_T2(void *arg);
void *thread_function_T3(void *arg);
pthread_mutex_t work_mutex1; /* proteção para: work_area e time_to_exit */
pthread_mutex_t work_mutex2;

#define WORK_SIZE 1024
char work_area1[WORK_SIZE];
char work_area2[WORK_SIZE];
int time_to_exit = 0; 

int main(int argc, char * argv[]) {
 
    // Configura entradas analógicas para os potenciômetros (controle de velocidade dos trens)
    ADC vel_T1(AINx::AIN0); //pino P9_39
    ADC vel_T2(AINx::AIN1); //pino P9_40
    ADC vel_T3(AINx::AIN2); //pino p9_37 

    // Configurando como saida os LEDs dos trens do trilho 1
    BlackGPIO Trem1_T1(GPIO_26, output);
    BlackGPIO Trem2_T1(GPIO_44, output);
    BlackGPIO Trem3_T1(GPIO_68, output);
    BlackGPIO Trem4_T1(GPIO_67, output);
    // Configurando como saida os LEDs dos trens do trilho 2
    BlackGPIO Trem1_T2(GPIO_60, output);
    BlackGPIO Trem2_T2(GPIO_47, output);
    BlackGPIO Trem3_T2(GPIO_45, output);
    BlackGPIO Trem4_T2(GPIO_49, output);
    // Configurando como saida os LEDs dos trens do trilho 3
    BlackGPIO Trem1_T3(GPIO_48, output);
    BlackGPIO Trem2_T3(GPIO_46, output);
    BlackGPIO Trem3_T3(GPIO_27, output);
    BlackGPIO Trem4_T3(GPIO_69, output);
    
    // Os trens comecam parados, ou seja, os LEDs ficam apagados no inicio
  
    Trem1_T1.setValue(low);
    Trem2_T1.setValue(low);
    Trem3_T1.setValue(low);
    Trem4_T1.setValue(low);

    Trem1_T2.setValue(low);
    Trem2_T2.setValue(low);
    Trem3_T2.setValue(low);
    Trem4_T2.setValue(low);

    Trem1_T3.setValue(low);
    Trem2_T3.setValue(low);
    Trem3_T3.setValue(low);
    Trem4_T3.setValue(low);

    int res;
    pthread_t thread_T1;
    pthread_t thread_T2;
    pthread_t thread_T3;
    void *thread_result;
    // Inicialização dos Mutexs 1 e 2
    res = pthread_mutex_init(&work_mutex1, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex1 falhou");
        exit(EXIT_FAILURE);
    }
    res = pthread_mutex_init(&work_mutex2, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex2 falhou");
        exit(EXIT_FAILURE);
    }

    // Criação da thread_T1
    res = pthread_create(&thread_T1, NULL, thread_function_T1, NULL);
    if (res != 0) {
        perror("Criação da thread_T1 falhou");
        exit(EXIT_FAILURE);
    }
     // Criação da thread_T2
     res = pthread_create(&thread_T2, NULL, thread_function_T2, NULL);
    if (res != 0) {
        perror("Criação da thread_T2 falhou");
        exit(EXIT_FAILURE);
    }
     // Criação da thread_T3
     res = pthread_create(&thread_T3, NULL, thread_function_T3, NULL);
    if (res != 0) {
        perror("Criação da thread_T3 falhou");
        exit(EXIT_FAILURE);
    }
   

    while (true) {
	    tempo_T1 = vel_T1.getIntValue();
        tempo_T2 = vel_T2.getIntValue();
        tempo_T3 = vel_T3.getIntValue();

    }

    sleep(5);
    return 0;
}

void *thread_function_T1(void *arg) {
    Trem1_T1.setValue(high);
    sleep(tempo_T1);
    Trem1_T1.setValue(low);
    Trem2_T1.setValue(high);
    sleep(tempo_T1);
    Trem2_T1.setValue(low);
    //-------------------------------
    pthread_mutex_lock(&work_mutex1); 
    //-------------------------------
    Trem3_T1.setValue(high);
    sleep(tempo_T1);
    Trem3_T1.setValue(low);
    //-------------------------------
    pthread_mutex_unlock(&work_mutex1);
    //-------------------------------
    Trem4_T1.setValue(high);
    sleep(tempo_T1);

    pthread_exit(0);
}

void *thread_function_T2(void *arg) {
    //-------------------------------
    pthread_mutex_lock(&work_mutex1);
    //-------------------------------
    Trem1_T2.setValue(high);
    sleep(tempo_T2);
    Trem1_T2.setValue(low);
    //-------------------------------
    pthread_mutex_unlock(&work_mutex1);
    //-------------------------------
    Trem2_T2.setValue(high);
    sleep(tempo_T2);
    Trem2_T2.setValue(low);
    //-------------------------------
    pthread_mutex_lock(&work_mutex2);
    //-------------------------------
    Trem3_T2.setValue(high);
    sleep(tempo_T2);
    Trem3_T2.setValue(low);
    //-------------------------------
    pthread_mutex_unlock(&work_mutex2);
    //-------------------------------
    Trem4_T2.setValue(high);
    sleep(tempo_T2);
   
    pthread_exit(0);
}

void *thread_function_T3(void *arg) {
    //-------------------------------
    pthread_mutex_lock(&work_mutex2);
    //-------------------------------
    Trem1_T3.setValue(high);
    sleep(tempo_T3);
    Trem1_T3.setValue(low);
    //-------------------------------
    pthread_mutex_unlock(&work_mutex2);
    //-------------------------------
    Trem2_T3.setValue(high);
    sleep(tempo_T3);
    Trem2_T3.setValue(low);
    Trem3_T3.setValue(high);
    sleep(tempo_T3);
    Trem3_T3.setValue(low);
    Trem4_T3.setValue(high);
    sleep(tempo_T3);
    
    pthread_exit(0);
}
