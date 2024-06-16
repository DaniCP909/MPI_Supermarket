//
// Created by isidoro.hernan on 06/03/2024.
//

#ifndef COLA_TCOLA_H
#define COLA_TCOLA_H
#include "TElemento.h"
#define CAPACIDAD 20
typedef struct {
    TElemento vector[CAPACIDAD];
    int inicio;
    int final;
    int numElementos;
} TCola;

void construirCola (TCola *cola);

void encolar(TCola *cola, TElemento nuevo);

TElemento desencolar(TCola *cola);

TElemento primero (TCola cola);

int esColaVacia (TCola cola);

int longitud (TCola cola);

void copiaCola (TCola original, TCola *copia);

void destruirCola (TCola *cola);

void visualizarCola (TCola cola);

#endif //COLA_TCOLA_H
