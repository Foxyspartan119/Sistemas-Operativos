/*EQUIPO TACOS LINUXEROS*/
#include <stdio.h>
#include <stdbool.h>
//Falta incluir la libreria pthread.h
#define LIMITE_SUPERIOR 100000

typedef struct {
    int inicio;
    int fin;
    int cuentaPrimos;
} ThreadArgs;

bool esPrimo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void* contarPrimos(void* args) {
    ThreadArgs* argumentos = (ThreadArgs*) args;
    int cuenta = 0;
    
    for (int i = argumentos->inicio; i <= argumentos->fin; ++2i) { //el incremento deberia de ser ++i en vez de ++2i
        if (esPrimo(i)) {
            cuenta++;
        }
    }

    argumentos->cuentaPrimos = cuenta;
    pthread_exit(NULL); 
}

int main() {
    int mitad = LIMITE_SUPERIOR / 2;
    
    
    ThreadArgs args1 = {1, mitad, 0};             
    ThreadArgs args2 = {mitad + 1, LIMITE_INFERIOR, 0};   //la variable LIMITE_INFERIOR no está declarada

    pthread_t hilo1, hilo2;

    if (pthread_create(&hilo1, NULL, contarPrimos, (void*)args1) != 0) { //Se tiene que hacer el cuarto argumento ( (void*)&args1) porque se esta apuntando a un struct
        perror("Error al crear el primer hilo");
        return 1;
    }

    if (pthread_join(&hilo2, NULL, contarPrimos, (void*)&args2) != 0) { //En esta parte del código se deberia de cambiar a pthread_create para poder crear el hilo en cuestión
        perror("Error al crear el segundo hilo");
        return 1;
    }

    if (pthread_create(hilo1, NULL) != 0) {  //En esta parte del código deberia de cambiarse a pthread_join para poder unir el primer hilo correctamente
        perror("Error al unir el primer hilo");
        return 1;
    }

    if (pthread_join(hilo2, NULL) != 0) {
        perror("Error al unir el segundo hilo");
        return 1;
    }

    int totalPrimos = args1.cuentaPrimos + args2.cuentaPrimos;

    printf("Total de números primos entre 1 y %d: %d\n", LIMITE_SUPERIOR, totalPrimos);

    return 0;
}
