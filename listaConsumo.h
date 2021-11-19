#ifndef LISTACONSUMO_H_INCLUDED
#define LISTACONSUMO_H_INCLUDED
#include "consumos.h"
typedef struct _nodoLista{
 	stConsumos dato;
    struct _nodoLista* sig;
}nodoLista;


nodoLista* inicLista();
nodoLista* crearNodoLista(stConsumos dato);
nodoLista* agregarAlPrincipio(nodoLista* lista, nodoLista* nuevo);
void muestraLista(nodoLista* lista);
void muestraNodo(nodoLista* nodo);
nodoLista* borrarLista(nodoLista* lista);
#endif // LISTACONSUMO_H_INCLUDED
