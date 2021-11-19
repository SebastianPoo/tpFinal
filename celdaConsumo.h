#ifndef CELDACONSUMO_H_INCLUDED
#define CELDACONSUMO_H_INCLUDED
#include "listaConsumo.h"

typedef struct{
    int id;
    nodoLista* listaConsumos;
}stCelda;


int agregarEnArreglo(stCelda adl[], int validos, int id);
int alta(stCelda adl[], stConsumos e, int validos);
int buscarPorID(stCelda adl[], int validos, int id);
int archivo2Celda(char archivo [], stCelda adl[],int validos);
#endif // CELDACONSUMO_H_INCLUDED
