#ifndef ARBOLCLIENTES_H_INCLUDED
#define ARBOLCLIENTES_H_INCLUDED
#include "clientes.h"
#include "celdaConsumo.h"

///======================== ARBOL DE CLIENTES ====================================/////

typedef struct _nodoArbol{
    stClientes dato;
    nodoLista* consumo;
    struct _nodoArbol* izq;
    struct _nodoArbol* der;
}nodoArbol;


nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(stClientes dato);
nodoArbol* agregarArbol(nodoArbol* arbol, nodoArbol* nuevo);
nodoArbol* alta_nadl(nodoArbol* adl, stClientes c, stConsumos a);
nodoArbol* buscarCliente(nodoArbol* adl, int numCliente);
nodoArbol* archivo2Arbol(char archivo [], nodoArbol* arbol);
void preOrdenPersona(nodoArbol* arbol);
void enOrdenPersona(nodoArbol* arbol);
void postOrdenPersona(nodoArbol* arbol);
void muestraNodoArbolcliente(nodoArbol* nodo);
void clientesConConsumos (nodoArbol* arbol, stCelda ArrayConsumos [], int validos);
nodoArbol* archivo2ArbolConConsumos(char archivo [],char archivoCom[], nodoArbol* arbol);
void archiCon2Arbol(char archivo [], nodoArbol* arbol);



/// FUNCIONES PASAR ARCHIVO A ARBOL Y SUS CONSUMOS ///
nodoArbol* agregarArbolOk(nodoArbol* arbol, nodoArbol* nuevo);
nodoArbol* archivo2ArbolOk(char archivo [], nodoArbol* arbol);
nodoArbol* buscaNodoArbolClientePorId(nodoArbol* arbol, int id);
nodoArbol* pasarConsumos2ArbolCliente(nodoArbol* arbol, char archivoConsumos[]);
int datosConsumidosPorPeriodoMes(nodoLista* lista, int anio, int mes);
int datosConsumidosPorPeriodoAnio(nodoLista* lista, int anio);
void muestraPeriodoConMes (stConsumos consumo, int anio, int mes, int totalConsumido);
void muestraPeriodoConAnio (stConsumos consumo, int anio, int totalConsumido);
void muestraConsumosXanioXId (nodoArbol* arbol);
void muestraConsumosPeriodosXID (nodoArbol* arbol);
void muestraConsuAnio(nodoLista* lista, int anio);
void muestraConsMes (nodoLista* lista, int anio, int mes);
nodoArbol* eliminaNodoArbol(nodoArbol* aux, int id);
int esHoja(nodoArbol * arbol);
nodoArbol * arbolMasIzquierdo(nodoArbol * arbol);
nodoArbol * arbolMasDerecha(nodoArbol * arbol);
nodoArbol* arregloClientes2ArbolBalanceado(stClientes arrayCliente[],int validos);
void persistirNodoArbolCliente (char archivo [], stClientes cliente);
stClientes altaClienteArbol ();
nodoArbol* agregarConsumoAUnNodoCliente(nodoArbol* arbol, stConsumos consumo);

///=========================LISTA DE CLIENTES===========================/////

typedef struct _nodoListaCli{
    stClientes dato;
    struct _nodoListaCli* siguiente;
}nodoListaCli;


#endif // ARBOLCLIENTES_H_INCLUDED
