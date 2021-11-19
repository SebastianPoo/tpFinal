#include "clientes.h"
#include "consumos.h"
#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define nomArchivo "clientes.dat"
#define backupClientes "backupArchivo.dat"
#define nomArchiConsumos "consumos.dat"
#define ANIO 2021
#include "listaConsumo.h"
#include "arbolClientes.h"
#include "celdaConsumo.h"


nodoArbol* inicArbol()
{
    return NULL;
}

nodoArbol* crearNodoArbol(stClientes dato)
{
    nodoArbol* nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevo->dato = dato;
    nuevo->consumo = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

nodoArbol* agregarArbol(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL)
    {
        arbol = nuevo;
    }
    else
    {
        if(nuevo->dato.id < arbol->dato.id)
        {
            arbol->izq = agregarArbol(arbol->izq, nuevo);
        }
        else
        {
            arbol->der = agregarArbol(arbol->der, nuevo);
        }
    }

    return arbol;
}


nodoArbol* alta_nadl(nodoArbol* adl, stClientes c, stConsumos a)
{
    nodoLista* nuevoCon=crearNodoLista(a);
    nodoArbol* respuesta = buscarCliente(adl, c.nroCliente);
    if(respuesta==NULL)
    {
        nodoArbol* nuevoNodoArb=crearNodoArbol(c);
        nuevoNodoArb->consumo = agregarAlPrincipio(nuevoNodoArb->consumo, nuevoCon);
        adl=agregarArbol(adl,nuevoNodoArb);
    }
    else
    {
        respuesta->consumo=agregarAlPrincipio(respuesta->consumo,nuevoCon);
    }

    return adl;
}

nodoArbol* buscarCliente(nodoArbol* adl, int numCliente)
{
    nodoArbol* respuesta =inicArbol();
    if(adl)
    {
        if(numCliente == adl->dato.nroCliente)
        {
            respuesta=adl;
        }
        else
        {
            if(numCliente == adl->dato.nroCliente)
            {
                respuesta=buscarCliente(adl->der, numCliente);
            }
            if(respuesta==NULL);
            {
                respuesta=buscarCliente(adl->izq, numCliente);
            }
        }
    }
    return respuesta;
}

nodoArbol* arrayToArbol (stClientes c[], int base, int tope)
{
    int medio;

    nodoArbol* arbol=NULL;

    if(!(base>tope))
    {

        medio=(base+tope)/2;

        arbol=crearNodoArbol(c[medio]);

        arbol->izq=arrayToArbol(c,base,medio-1);
        arbol->der=arrayToArbol(c,medio+1,tope);
    }

    return arbol;
}
nodoArbol* archivo2ArbolConConsumos(char archivo [],char archivoCom[], nodoArbol* arbol)
{
    stClientes e;
    stConsumos c;
    FILE *pArchiClientes = fopen(archivo, "rb");
    FILE *pArchiCom = fopen(archivoCom, "rb");
    if(pArchiClientes)
    {

        while(fread(&e, sizeof(stClientes), 1, pArchiClientes)>0)
        {
            arbol = agregarArbol(arbol,crearNodoArbol(e));
            while(fread(&c,sizeof(stConsumos),1,pArchiCom)>0)
            {
                if (c.idCliente == e.nroCliente)
                {
                    arbol->consumo = agregarAlPrincipio(arbol->consumo,crearNodoLista(c));
                }
            }
            fclose(pArchiCom);
        }
        fclose(pArchiClientes);
    }

    return arbol;
}

nodoArbol* archivo2Arbol(char archivo [], nodoArbol* arbol)
{
    stClientes e;

    FILE *pArchiClientes = fopen(archivo, "rb");

    if(pArchiClientes)
    {

        while(fread(&e, sizeof(stClientes), 1, pArchiClientes)>0)
        {
            arbol = agregarArbol(arbol,crearNodoArbol(e));

        }
        fclose(pArchiClientes);
    }

    return arbol;
}


void preOrdenPersona(nodoArbol* arbol)
{
    if(arbol)
    {
        muestraNodoArbolcliente(arbol);
        preOrdenPersona(arbol->izq);
        preOrdenPersona(arbol->der);
    }
}

void enOrdenPersona(nodoArbol* arbol)
{
    if(arbol)
    {
        enOrdenPersona(arbol->izq);
        muestraNodoArbolcliente(arbol);
        enOrdenPersona(arbol->der);
    }
}

void postOrdenPersona(nodoArbol* arbol)
{
    if(arbol)
    {
        postOrdenPersona(arbol->izq);
        postOrdenPersona(arbol->der);
        muestraNodoArbolcliente(arbol);
    }
}

void muestraNodoArbolcliente(nodoArbol* nodo)
{
    muestraUnCliente(nodo->dato);
    muestraLista(nodo->consumo);
}

void clientesConConsumos (nodoArbol* arbol, stCelda ArrayConsumos [], int validos) ///NO FUNCIONA TODAVIA///
{
    int i = 0;
    if (arbol  && i<validos)
    {
        printf("\n numero de cliente es %d-", arbol->dato.nroCliente);
        if (arbol->dato.nroCliente == ArrayConsumos [validos - 1].id)
        {
            printf("\n numero de cliente es %d-", arbol->dato.nroCliente);
//            arbol->consumo =  ArrayConsumos[validos - 1].listaConsumos;
//            validos = validos+1;
        }
        else if (ArrayConsumos[validos].id < arbol->dato.nroCliente)
        {
            clientesConConsumos(arbol->izq, ArrayConsumos, validos -1 );

        }
        else
        {
            clientesConConsumos(arbol->der, ArrayConsumos, validos -1);
        }
    }
}

void archiCon2Arbol(char archivo [], nodoArbol* arbol)
{
    int cont = 0;
    stConsumos e;
    nodoArbol* cliente;
    FILE *pArchiConsumos = fopen(archivo, "rb");
    if(pArchiConsumos )
    {

        while(fread(&e, sizeof(stConsumos), 1, pArchiConsumos)>0)
        {
            cliente = buscarCliente(arbol,e.idCliente);
            if (cliente)
            {
                arbol = alta_nadl(arbol,cliente->dato,e);
            }
        }
        fclose(pArchiConsumos);
    }
}


/// FUNCIONES OKKK ///


nodoArbol* agregarArbolOk(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL)
    {
        arbol = nuevo;
    }
    else
    {
        if(nuevo->dato.id %2 == 0)
        {
            arbol->izq = agregarArbolOk(arbol->izq, nuevo);
        }
        else
        {
            arbol->der = agregarArbolOk(arbol->der, nuevo);
        }
    }

    return arbol;
}

nodoArbol* archivo2ArbolOk(char archivo [], nodoArbol* arbol)
{
    stClientes e;
    FILE *pArchiClientes = fopen(archivo, "rb");
    if(pArchiClientes )
    {

        while(fread(&e, sizeof(stClientes), 1, pArchiClientes)>0)
        {
            arbol = agregarArbolOk(arbol, crearNodoArbol(e));
        }
        fclose(pArchiClientes);
    }

    return arbol;
}

nodoArbol* buscaNodoArbolClientePorId(nodoArbol* arbol, int id)
{
    nodoArbol* respuesta = NULL;
    if(arbol)
    {
        if(arbol->dato.id == id)
        {
            respuesta = arbol;
        }
        else
        {
            respuesta = buscaNodoArbolClientePorId(arbol->izq, id);
            if(respuesta == NULL)
            {
                respuesta = buscaNodoArbolClientePorId(arbol->der, id);
            }
        }
    }

    return respuesta;
}

nodoArbol* pasarConsumos2ArbolCliente(nodoArbol* arbol, char archivoConsumos[])
{
    FILE *archiCon = fopen(archivoConsumos, "rb");
    stConsumos e;
    nodoArbol* aux = NULL;
    if(archiCon)
    {
        while(fread(&e, sizeof(stConsumos), 1, archiCon)>0)
        {
            aux = buscaNodoArbolClientePorId(arbol, e.idCliente);
            aux->consumo= agregarAlPrincipio(aux->consumo, crearNodoLista(e));
        }
    }


    fclose(archiCon);

    return arbol;

}

/// SUMA Y MUESTRA LOS DATOS CONSUMIDOS POR ANIO Y MES
int datosConsumidosPorPeriodoMes(nodoLista* lista, int anio, int mes){
    nodoLista* seg = lista;
    int datos = 0;
    while(seg){
        if(anio == seg->dato.anio && mes == seg->dato.mes){
            datos = datos + seg->dato.datosConsumidos;
        }
        seg = seg->sig;

    }
    if (datos==0){
        printf("\n El cliente ingresado no tiene consumos en ese periodo \n");
    }
    return datos;
}

void muestraConsMes (nodoLista* lista, int anio, int mes){
    nodoLista* seg = lista;
    int datos = 0;
    while(seg){
        if(anio == seg->dato.anio && mes == seg->dato.mes){
            datos = datos + seg->dato.datosConsumidos;
        }
        seg = seg->sig;

    }
    if (datos==0){

        printf("\n El cliente ingresado no tiene consumos en ese periodo \n");

        muestraPeriodoConMes(lista->dato, anio, mes, datos);
    }

}

void muestraPeriodoConMes (stConsumos consumo, int anio, int mes, int totalConsumido) {


        printf("\n Id de Cliente numero   %d", consumo.idCliente);
        printf("\n Anio                  [%d]", anio);
        printf("\n Mes                   [%d]", mes);
        printf("\n Consumos del periodo      [%d]mb", totalConsumido);
        printf("\n-------------------------------------------------------");
}

void muestraConsumosPeriodosXID (nodoArbol* arbol){

  nodoArbol* aux=inicArbol();
  int i=0;
  int anio=0;
  int mes=0;
  int datos=0;
   printf("\n Ingrese el numero de cliente a buscar\n");
   scanf("%d", &i);
   aux= buscaNodoArbolClientePorId(arbol, i);
   if (aux){
       printf("\n Ingrese Anio a Buscar\n");
       scanf("%d", &anio);
       printf("\n Ingrese Mes a Buscar\n");
       scanf("%d", &mes);
       datos=datosConsumidosPorPeriodoMes(aux->consumo, anio,mes);
       muestraPeriodoConMes(aux->consumo->dato, anio, mes, datos);

   } else {

    printf("\n El cliente no existe\n");

   }
}



/// SUMA Y MUESTRA LOS DATOS CONSUMIDOS POR ANIO

void muestraConsuAnio(nodoLista* lista, int anio){
    nodoLista* seg = lista;
    int datos = 0;
    while(seg){
        if(anio == seg->dato.anio){
            datos = datos + seg->dato.datosConsumidos;
        }
        seg = seg->sig;

    }

    if (datos==0){
        printf("\n El cliente ingresado no tiene consumos en ese periodo \n");
    }else{
        muestraPeriodoConAnio(lista->dato,anio,datos);
    }
}

int datosConsumidosPorPeriodoAnio(nodoLista* lista, int anio){
    nodoLista* seg = lista;
    int datos = 0;
    while(seg){
        if(anio == seg->dato.anio){
            datos = datos + seg->dato.datosConsumidos;
        }
        seg = seg->sig;

    }

    if (datos==0){
        printf("\n El cliente ingresado no tiene consumos en ese periodo \n");

    }
    return datos;
}



void muestraPeriodoConAnio (stConsumos consumo, int anio, int totalConsumido) {


        printf("\n Id de Cliente numero   %d", consumo.idCliente);
        printf("\n Anio                  [%d]", anio);
        printf("\n Consumos del periodo      [%d]mb", totalConsumido);
        printf("\n-------------------------------------------------------");

}


void muestraConsumosXanioXId (nodoArbol* arbol){

  nodoArbol* aux=inicArbol();
  int i=0;
  int anio=0;
  int datos=0;
   printf("\n Ingrese el numero de cliente a buscar\n");
   scanf("%d", &i);
   aux= buscaNodoArbolClientePorId(arbol, i);
   if (aux){
       printf("\n Ingrese Anio a Buscar\n");
       scanf("%d", &anio);
       datos=datosConsumidosPorPeriodoAnio(aux->consumo, anio);
       muestraPeriodoConAnio(aux->consumo->dato, anio,datos);

   } else {

    printf("\n El cliente no existe\n");

   }
}

///RETORNA EL NODO ARBOL TOPE DER
nodoArbol * arbolMasDerecha(nodoArbol * arbol){
    nodoArbol * seg = arbol;
    while(seg->der) {
        seg = seg->der;
    }
    return seg;
}

///RETORNA EL NODO ARBOL TOPE IZQ
nodoArbol * arbolMasIzquierdo(nodoArbol * arbol){
    nodoArbol * seg = arbol;
    while(seg->izq) {
        seg = seg->izq;
    }
    return seg;
}

/// RETORNA SI ES HOJA
int esHoja(nodoArbol * arbol) {
    int rta = 0;
    if(arbol) {
        if(!arbol->izq && !arbol->der){
            rta = 1;
        }
    }
    return rta;
}


/// ELIMINA NODO DEL ARBOL CLIENTES
nodoArbol* eliminaNodoArbol(nodoArbol* aux, int id){

    if(aux) {
        if(id==aux->dato.id) {

            if(aux->izq) {
                nodoArbol* masDer = arbolMasDerecha(aux->izq);
                aux->dato = masDer->dato;
                aux->consumo = masDer->consumo;
                aux->izq = eliminaNodoArbol(aux->izq, masDer->dato.id);
            } else if (aux->der) {
                nodoArbol* masIzq = arbolMasIzquierdo(aux->der);
                aux->dato = masIzq->dato;
                aux->der = eliminaNodoArbol(aux->der, masIzq->dato.id);
            } else if (esHoja(aux)) {
                aux->consumo=borrarLista(aux->consumo);
                free(aux);
                aux = NULL;
            }
        }else{
            if(id > aux->dato.id){
                aux->der = eliminaNodoArbol(aux->der, id);
            }else{
                aux->izq = eliminaNodoArbol(aux->izq, id);
            }
        }
    }
    return aux;
}

/// FUNCION DE BALANCEO
nodoArbol* arregloClientes2ArbolBalanceado(stClientes arrayCliente[],int validos){
    nodoArbol* arbol = NULL;
    int i, mitad=(validos-1)/2;
    for(i=mitad; i>=0; i--){
        if( (i%2)!=0 ){
            arbol=agregarArbolOk(arbol, crearNodoArbol(arrayCliente[i]));
        }
    }
    for(i=mitad; i>=0; i--){
        if( (i%2)==0 ){
            arbol=agregarArbolOk(arbol, crearNodoArbol(arrayCliente[i]));
        }
    }
    /// PARTE DERECHA DEL ARBOL CLIENTES
    for(i=mitad+1; i<validos; i++){
        if( (i%2)!=0 ){
            arbol=agregarArbolOk(arbol, crearNodoArbol(arrayCliente[i]));
        }
    }
    for(i=mitad+1; i<validos; i++){
        if( (i%2)==0 ){
            arbol=agregarArbolOk(arbol, crearNodoArbol(arrayCliente[i]));
        }
    }
    return arbol;
}


stClientes altaClienteArbol (){
    char opcion=0;
    int flagEmail=0;
    int flagDni=0;
    int flagMovil=0;
    int flagNombreApellido=0;
    stClientes c;

        do{

        c.nroCliente=100+cargaNroCliente();
        }while(validaNumCliente(c.nroCliente)==1);
        printf("\nNumero de cliente nuevo fue creado. ");
        printf("\nIngrese datos para el cliente [%d] ",c.nroCliente);

        do{
        printf("\n Nombre....................: ");
        fflush(stdin);
        scanf("%s", &c.nombre);
        flagNombreApellido=validaNombreyApelido(c.nombre);
        } while (flagNombreApellido==1);
        flagNombreApellido=0;
       do{
        printf("\nApellido....................: ");
        fflush(stdin);
        scanf("%s", &c.apellido);
        flagNombreApellido=validaNombreyApelido(c.apellido);
        } while (flagNombreApellido==1);
        validaDni(&c.dni);
        do{
        printf("\n Dni..................: ");
        fflush(stdin);
        scanf("%s", &c.dni);
        flagDni=validaDni(c.dni);
        } while(flagDni==1);

        fflush(stdin);
        scanf(validaEmail (&c.email));
        printf("\n Domicilio.................: ");
        fflush(stdin);
        gets(&c.domicilio);
        ///scanf("%s", &c.domicilio);
        do{
        printf("\n Movil.....................: ");
        fflush(stdin);
        scanf("%s", &c.movil);
        flagMovil=validaMovil(c.movil);
        }while(flagMovil==1);
        printf("\n Situacion del cliente.....: ");
        scanf("%d", &c.estado);
        c.id = (cuentaRegistros("clientesRandom.dat", sizeof(stClientes)))+100;



   return c;
}

void persistirNodoArbolCliente (char archivo [], stClientes cliente){
  FILE *archi = fopen(archivo, "ab");

  if (archi){

       fwrite(&cliente, sizeof(stClientes), 1, archi);
  }
    fclose(archi);
}

nodoArbol* agregarConsumoAUnNodoCliente(nodoArbol* arbol, stConsumos consumo)
{
    nodoArbol* aux = NULL;

            aux = buscaNodoArbolClientePorId(arbol, consumo.id);
            aux->consumo= agregarAlPrincipio(aux->consumo, crearNodoLista(consumo));
        return arbol;
}

