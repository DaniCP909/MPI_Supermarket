//
// Created by isidoro.hernan on 11/03/2024.
//

#include "TcolaPrioridad.h"
#include <stdio.h>

void crearColaPrioridad (TColaPrioridad cola){
    for (int i=0; i<NUMPRIORIDADES; i++){
        construirCola(&cola[i]);
    }
}

// PRE: la prioridad es un número entre 0 (Maxima) y NUMPRIORIDADES-1 (Minima)
// POST: Añade un elemento a la cola con la prioridad dada
void push (TColaPrioridad cola, int prioridad, TElemento nuevo){
    encolar(&cola[prioridad], nuevo);
}

TElemento pop(TColaPrioridad cola){
    int i = 0;
    while (i < NUMPRIORIDADES && esColaVacia(cola[i])){
        i++;
    }
    if (i < NUMPRIORIDADES) {
        return desencolar(&cola[i]);
    }
}

void visualizarColaPrioridad(TColaPrioridad cola){
    for (int i=0; i<NUMPRIORIDADES; i++){
        printf("\nCola de prioridad = %d",i);
        visualizarCola(cola[i]);
    }
}

void destruirColaPrioridad(TColaPrioridad cola){
    for (int i=0; i<NUMPRIORIDADES; i++){
        destruirCola(&cola[i]);
    }
}

int longitudColaPrioridad (TColaPrioridad cola){
    int contador = 0;
    for (int i=0; i<NUMPRIORIDADES; i++){
        contador += cola[i].numElementos;
    }
    return contador;
}

int esColaPrioridadVacio(TColaPrioridad cola){
    return longitudColaPrioridad(cola);
}