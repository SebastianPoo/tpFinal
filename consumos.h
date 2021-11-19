#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED
#include "clientes.h"
typedef struct{
    int id;
    int idCliente;
    int anio;
    int mes;
    int dia;
    int datosConsumidos;
    int totalConsumosMomento;
    int estado; ///0 cliente dado de baja, 1 cliente activo
}stConsumos;
///CONSUMOS//
int cargaAnio(int anio);
int existeConsumoCliente(char archivo[],int idCliente);
int sumaConsumoFecha(stConsumos a);
int cargaMes(int fecha);
int cargaDia (int dato);

int clienteRandom();
int mesRandom ();
int diaRandom ();
void altaConsumoRandom (char archivoConsumos[], int idStCliente, int mes, int dia);
stClientes buscaPorId ( int id);


        ///BUSCA///
int cargaNombresABuscar (char n[][40], int dim);
void modificaCliente (stClientes clientes[], int validos,  int idModificar);
stClientes buscaDni ( char dni[]);
stClientes buscaApellido ( char apellido []);
stClientes buscaPorCliente ( int numCliente);
stClientes buscaIdCliente(char archivo[], int pos);
void buscaPorClienteModEstado ( int numCliente);
int buscaPos (int numClient);
        ///CONSUMOS///
void mostrarXFecha(char archivoConsumo[]);
void cambiaConsumo(char archivoConsumo []);
void muestraConsumoPorIdCliente (int idClien);
void muestraUnConsumo (stConsumos consumo);

        ///MUESTRA///
void buscaClienteApellido (char archivoClientes [],char apellido[]);
void muestraUnCliente (stClientes c);
void muestraListaClientes (char archivoClientes []);
void muestraClientesId (char archivoClientes [], int clienteBuscar);
void muestrasNomOapellido ( char n[][40], int v);
void muestraActivos ();


/// FUNCIONES DE CONSUMO ///

void altaConsumo (char archivoConsumos[], int idStCliente);
void muestraListaConsumos ();

/// FUNCIONES DE CONSUMO ///
void altaConsumoRandomOk (char archivoConsumos[], int idStCliente);
int* getYear();
stConsumos altaConsumoArbol ();
void persistirConsumo (char archivo [], stConsumos consumo);

#endif // CONSUMOS_H_INCLUDED
