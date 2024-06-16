//
// Created by isidoro.hernan on 11/03/2024.
//

#ifndef COLAPRIORIDAD_TCOLAPRIORIDAD_H
#define COLAPRIORIDAD_TCOLAPRIORIDAD_H
#include "TCola.h"

#define NUMPRIORIDADES 7

typedef
   TCola TColaPrioridad [NUMPRIORIDADES];

// POST: Devuelve una cola vacia
void crearColaPrioridad (TColaPrioridad cola);
// PRE: la prioridad es un número entre 0 (Maxima) y NUMPRIORIDADES-1 (Minima)
// POST: Añade un elemento a la cola con la prioridad dada
void push (TColaPrioridad cola, int prioridad, TElemento nuevo);

//PRE: La cola no puede estar vacía
// POST: Devuelve una copia del elemento con mayor prioridad de la cola
TElemento pop(TColaPrioridad cola);


// POST: Visualiza cada subcola de la cola de prioridad
void visualizarColaPrioridad(TColaPrioridad cola);


// POST: La cola pasa a estar vacía
void destruirColaPrioridad(TColaPrioridad cola);


// POST: Devuelve el número de elementos de la cola
int longitudColaPrioridad (TColaPrioridad cola);


// POST: Devuelve un entero positivo si la cola está vacia (no tiene elementos) y 0 en caso contrario
int esColaPrioridadVacio(TColaPrioridad cola);


#endif //COLAPRIORIDAD_TCOLAPRIORIDAD_H
