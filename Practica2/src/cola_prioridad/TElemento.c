//
// Created by isidoro.hernan on 20/02/2024.
//

#include "TElemento.h"
#include <stdio.h>

void visualizar(TElemento elemento){
    //Visualizar un número entero es inmediato
    //Si el tipo del elementos fuera complejo, habría que elaborarlo más
    printf(" %d ", elemento);
}

int sonIguales(TElemento uno, TElemento dos){
    //Aquí se implementa cuando dos elementos son iguales
    //En nuestro caso, al ser enteros es muy fácil
    int resultado = 0; //Suponemos que son diferentes
    if (uno==dos){
        resultado = 1;
    }
    return resultado;
}

int esMenorQue(TElemento uno, TElemento dos){
    //Aquí se implementa cuando el elemento uno es menor que el elemento dos
    //Post: Devuelve 1 si el elemento uno es menor que el dos
    //En nuestro caso, al ser enteros es muy fácil
    int resultado = 0; //Suponemos que son iguales o mayor que
    if (uno<dos){
        resultado = 1;
    }
    return resultado;

}