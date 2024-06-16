//
// Created by isidoro.hernan on 06/03/2024.
//

#include "TCola.h"
#include <stdio.h>
void construirCola (TCola *cola){
    cola->final = 0;
    cola->inicio = 0;
    cola->numElementos = 0;
}

void encolar(TCola *cola, TElemento nuevo){
    if (cola->numElementos<CAPACIDAD){
        cola->vector[cola->final] = nuevo;
        cola->final = (cola->final + 1)%CAPACIDAD;
        cola->numElementos++;
    }
}
//PRE: La cola no puede estar vacía
TElemento desencolar(TCola *cola){
    if (!esColaVacia(*cola)) {
        int i = cola->inicio;
        cola->inicio = (cola->inicio + 1) % CAPACIDAD;
        cola->numElementos--;
        return cola->vector[i];
    }
}

TElemento primero (TCola cola){
    return cola.vector[cola.inicio];
}

int esColaVacia (TCola cola){
    return cola.numElementos==0;
}

int longitud (TCola cola){
    return cola.numElementos;
}

void copiaCola (TCola original, TCola *copia){
    for (int i= original.inicio; i<original.final; i++){
        copia->vector[i]=original.vector[i];
    }
    copia->inicio=original.inicio;
    copia->final=original.final;
    copia->numElementos=original.numElementos;
}

void destruirCola (TCola *cola){
    cola->final = 0;
    cola->inicio = 0;
    cola->numElementos = 0;
}

void visualizarCola (TCola cola){
    printf("\n");
    if (esColaVacia(cola)){
        printf("La cola esta vacia");
    }
    else {
       for (int i=0; i<cola.numElementos; i++){
           visualizar(cola.vector[(i+cola.inicio)%CAPACIDAD]);
       }
    }
    printf("\n");
}