#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define nomArchivo "clientes.dat"
#define backupClientes "backupArchivo.dat"
#define nomArchiConsumos "consumos.dat"
#define ANIO 2021
#include "clientes.h"
#include "consumos.h"
#include "menus.h"
#include "celdaConsumo.h"
#include "arbolClientes.h"


int main()
{
    ///MENU INICIAL///
    char opcionAltas;
    char opcion;
    char opcionESC=0;
    char opcionBusca;
    char opcionBuscaEnArbol;
    char opcionMostrar;
    char dniBusca[1];
    char apellidoBusca[1];
    stClientes clienteExi;
    stClientes arregloClientes [50];
    int posicion=-1;
    int clienteN=-1;
    int salir=-1;
    int vClientes=0;
    int idModicar=0;
    ///Aleatorio prueba///
    int clienteRegistro;
    int mesRan;
    int diaRan;
    stClientes stClienteRan;
    int i =0;
    stCelda arregloCons[cuentaRegistros(nomArchiConsumos,sizeof(stConsumos))];
    int vArregloCons=0;
    nodoArbol* arbolClie = inicArbol();
    nodoArbol* clienteNodArbol = inicArbol();
    int anioAliquidar;
/// pruebas ok
    stClientes clientesRandom [400];
    stClientes altaClientePrueba;
    stConsumos altaConsumoPrueba;
    int* vClientesRandom=0;
    nodoArbol* arbolClientesOk=inicArbol();
    ///nodoArbol* aux=inicArbol();
    int idCliente=-1;
    int numCliente=-1;
    int anioOmes;
    int mes = 0;
    int anio = 0;
    int idAbuscar;
    int idEliminar;
    int vConsumos=0;

    FILE*archivoEstado;
    do
    {
        opcion=menuInicial();

        switch(opcion)
        {
        case '1':        ///===============================CASE 1 --ALTAS CLIENTES Y CONSUMOS =========================================///
            do
            {
                opcionAltas=menuAltas();
                switch(opcionAltas)
                {
                case '1':                                            ///ALTAS DE CLIENTES///
                    printf("\n ALTA DE CLIENTES");
                    altaCliente(nomArchivo);

                    break;
                case '2':                ///ALTA DE CONSUMO -- PRIMERO BUSCA EL ID DEL CLIENTE POR DNI||NUMERO DE CLIENTE||APELLIDO//
                    do
                    {
                        opcionBusca=menuBusca();
                        switch(opcionBusca)
                        {
                        case '1':                                 ///BUSCA POR DNI PARA ALTA DE CONSUMO//
                            do
                            {
                                printf("\nIngrese dni a buscar\n");
                                fflush(stdin);
                                gets(dniBusca);
                                clienteExi=buscaDni(dniBusca);
                                if (clienteExi.id !=-1)
                                {
                                    printf("\nEL cliente encontrado es");
                                    muestraUnCliente(clienteExi);
                                    altaConsumo("consumos.dat", clienteExi.id);
                                    break;
                                }
                                else
                                {
                                    printf("\nEl cliente no existe");
                                    printf("\n");
                                    break;
                                }
                            }
                            while(clienteExi.nroCliente!=-1);
                            break;
                        case '2':                        ///BUSCA POR NUMERO DE CLIENTE PARA ALTA DE CONSUMO///
                            do
                            {
                                printf("\nIngrese numero de cliente a buscar\n");
                                scanf("%d",&numCliente);
                                clienteExi=buscaPorCliente(numCliente);
                                if (clienteExi.id !=-1)
                                {
                                    printf("\nEL cliente encontrado");
                                    muestraUnCliente(clienteExi);
                                    altaConsumo("consumos.dat", clienteExi.id);
                                    break;
                                }
                                else
                                {
                                    printf("\nEl cliente no existe");
                                    printf("\n");
                                    break;
                                }
                            }
                            while(clienteExi.nroCliente!=-1);
                            break;
                        case '3':                           ///BUSCA POR APELLIDO PARA ALTA DE CONSUMO///
                            do
                            {
                                printf("\nIngrese apellido a buscar\n");
                                fflush(stdin);
                                gets(apellidoBusca);
                                clienteExi=buscaApellido(apellidoBusca);
                                if (clienteExi.id !=-1)
                                {
                                    printf("\nEL cliente encontrado");
                                    muestraUnCliente(clienteExi);
                                    altaConsumo("consumos.dat", clienteExi.id);
                                    break;
                                }
                                else
                                {
                                    printf("\nEl cliente no existe");
                                    printf("\n");
                                    break;

                                }
                            }
                            while(clienteExi.nroCliente!=-1);

                        }
                        break;
                    case '3':                           ///ALTA CONSUMOS ALEATORIO///
                        for (int i=0; i<50; i++)
                        {
                            //clienteRegistro = clienteRandom();
                            stClienteRan=buscaPorId(clienteRandom());
                            // muestraUnCliente(stClienteRan);
                            mesRan=mesRandom();
                            diaRan=diaRandom();
                            altaConsumoRandom(nomArchiConsumos,stClienteRan.id,mesRan,diaRan);
                        }
                        printf("\n Ciclo random completo\n");

                        printf("\n");
                        system("pause");
                    }
                    while(opcionBusca!=27);
                }
                printf("\n");
                system("pause");
            }
            while(opcionAltas!=27);
            break;
        case '2':       /// ===================-CASE 2-- MODIFICACIONES-PRIMERO BUSCAR CLIENTE PARA MODIFICAR =============================///
            do
            {
                opcionBusca=menuBusca();

                switch(opcionBusca)
                {

                case '1':                       ///BUSCA POR DNI PARA MODIFICAR DATOS DEL CLIENTE//
                    do
                    {
                        printf("\nIngrese dni a buscar\n");
                        fflush(stdin);
                        gets(dniBusca);
                        clienteExi=buscaDni(dniBusca);
                        idModicar=clienteExi.id;
                        if (clienteExi.id !=-1)
                        {
                            printf("\nEL cliente encontrado es");
                            muestraUnCliente(clienteExi);
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    printf("\n");
                    system("\npause");
                    despersistencia(arregloClientes,&vClientes);
                    modificaCliente(arregloClientes,vClientes,idModicar);
                    vClientes=0;
                    break;
                case '2':                        ///BUSCA POR NUMERO DE CLIENTE PARA MODIFICAR DATOS DEL CLIENTE///
                    do
                    {
                        printf("\nIngrese numero de cliente a buscar\n");
                        scanf("%d",&numCliente);
                        clienteExi=buscaPorCliente(numCliente);
                        idModicar=clienteExi.id;
                        if (clienteExi.id !=-1)
                        {
                            printf("\nEL cliente encontrado");
                            muestraUnCliente(clienteExi);
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    printf("\n");
                    system("\npause");
                    despersistencia(arregloClientes,&vClientes);
                    modificaCliente(arregloClientes,vClientes,idModicar);
                    vClientes=0;
                    break;
                case '3':                       ///BUSCA POR APELLIDO PARA MODIFICAR DATOS DEL CLIENTE///

                    do
                    {
                        printf("\nIngrese apellido a buscar\n");
                        fflush(stdin);
                        gets(apellidoBusca);
                        clienteExi=buscaApellido(apellidoBusca);
                        idModicar=clienteExi.id;
                        if (clienteExi.id !=-1)
                        {
                            printf("\nEL cliente encontrado");
                            muestraUnCliente(clienteExi);
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    printf("\n");
                    system("pause");
                    despersistencia(arregloClientes,&vClientes);
                    modificaCliente(arregloClientes,vClientes,idModicar);
                    vClientes=0;
                    break;
                case 'a':                                     ///MODIFICA CAMPOS DE CONSUMO///
                    cambiaConsumo(nomArchiConsumos);
                }
                printf("\n");
                system("pause");
            }
            while(opcionBusca!=27);
            break;
        case '3':       ///=======================================CASE 3--BUSCA PARA MOSTRAR=================================///
            printf("\nBUSCA PARA MOSTRAR\n");
            do
            {
                opcionMostrar=menuMostrar();
                switch(opcionMostrar)
                {
                case '1':                                    ///BUSCA CONSUMOS PARA MOSTRAR//
                    mostrarXFecha(nomArchiConsumos);

                    break;
                case '2':                                    ///BUSCA POR DNI PARA MOSTRAR//
                    do
                    {
                        printf("\nIngrese dni a buscar\n");
                        fflush(stdin);
                        gets(dniBusca);
                        clienteExi=buscaDni(dniBusca);
                        clienteN=clienteExi.nroCliente;
                        if (clienteExi.id !=-1)
                        {
                            printf("\nEL cliente encontrado es");
                            muestraUnCliente(clienteExi);
                            while(opcionESC!=27)
                            {
                                printf("\nPARA VER LOS CONSUMOS DEL CLIENTE %d",clienteN);
                                printf("\n ESC PARA SALIR S PARA VER");
                                opcionESC=getch();
                                if (opcionESC!=27)
                                {
                                    system("cls");
                                    muestraConsumoPorIdCliente(clienteExi.id);
                                }
                                printf("\n");
                                system("pause");
                            }
                            opcionESC=0;
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    break;
                case '3':                                    ///BUSCA POR NUMERO DE CLIENTE PARA MOSTRAR//
                    do
                    {
                        printf("\nIngrese numero de cliente a buscar\n");
                        scanf("%d",&numCliente);
                        clienteExi=buscaPorCliente(numCliente);
                        if (clienteExi.id !=-1)
                        {
                            printf("\nEL cliente encontrado");
                            muestraUnCliente(clienteExi);
                            while(opcionESC!=27)
                            {
                                printf("\nPARA VER LOS CONSUMOS DEL CLIENTE %d",numCliente);
                                printf("\n ESC PARA SALIR S PARA VER");
                                opcionESC=getch();
                                if (opcionESC!=27)
                                {
                                    system("cls");
                                    muestraConsumoPorIdCliente(clienteExi.id);
                                }
                                printf("\n");
                                system("pause");
                            }
                            opcionESC=0;
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    break;
                case '4':                                    ///BUSCA POR APELLIDO PARA MOSTRAR///
                    do
                    {
                        printf("\nIngrese apellido a buscar\n");
                        fflush(stdin);
                        gets(apellidoBusca);
                        clienteExi=buscaApellido(apellidoBusca);
                        clienteN=clienteExi.nroCliente;
                        if (clienteExi.id !=-1)
                        {
                            printf("\nEL cliente encontrado");
                            muestraUnCliente(clienteExi);
                            while(opcionESC!=27)
                            {
                                printf("\nPARA VER LOS CONSUMOS DEL CLIENTE %d",clienteN);
                                printf("\n ESC PARA SALIR S PARA VER");
                                opcionESC=getch();
                                if (opcionESC!=27)
                                {
                                    system("cls");
                                    muestraConsumoPorIdCliente(clienteExi.id);
                                }
                                printf("\n");
                                system("pause");
                            }
                            opcionESC=0;
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    break;
                case '5':                                      ///BUSCA ESTADO DEL CLIENTE PARA MOSTRAR///
                    muestraActivos();
                    break;
                case '6':                                     ///MUESTRA LISTA DE CLIENTES ///
                    muestraListaClientes(nomArchivo);
                    break;
                case 'a':
                    muestraListaConsumos(nomArchiConsumos);
                    break;
                case 'b':
                    cambiaConsumo("consumos.dat");


                }
                printf("\n");
                system("pause");
            }
            while(opcionMostrar!=27);
            break;
        case '4':        ///=============================CASE 4--DAR DE BAJA UN CLIENTE--PRIMERO LO BUSCA=============================///
            printf("\nDAR DE BAJA UN CLIENTE\n");
            do
            {
                opcionBusca=menuBusca();
                switch(opcionBusca)
                {
                case '1':                       ///BUSCA POR DNI PARA DAR DE BAJA//
                    do
                    {
                        printf("\nIngrese dni a buscar\n");
                        fflush(stdin);
                        gets(dniBusca);
                        clienteExi=buscaDni(dniBusca);
                        clienteN=clienteExi.nroCliente;
                        if (clienteExi.id !=-1&&clienteN!=-1&&clienteExi.estado!=0)
                        {
                            system("cls");
                            printf("\nEL cliente %s fue encontrado",clienteExi.dni);
                            posicion= buscaPos(clienteN);
                            cambiaEstado(posicion,0);
                            printf("\nLa baja fue exitosa");
                            printf("\n");
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe o ya esta inactivo");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    break;
                case '2':                        ///BUSCA POR NUMERO DE CLIENTE PARA DAR DE BAJA///
                    do
                    {
                        printf("\nIngrese numero de cliente a buscar\n");
                        scanf("%d",&numCliente);
                        clienteExi=buscaPorCliente(numCliente);
                        if (clienteExi.id !=-1&&clienteExi.estado!=0)
                        {
                            system("cls");
                            printf("\nEL cliente %d fue encontrado", numCliente);
                            posicion= buscaPos(numCliente);
                            cambiaEstado(posicion,0);
                            printf("\nLa baja fue exitosa");
                            printf("\n");
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe o ya esta inactivo");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);
                    break;
                case '3':                           ///BUSCA POR APELLIDO PARA DAR DE BAJA///
                    do
                    {
                        printf("\nIngrese apellido a buscar\n");
                        fflush(stdin);
                        gets(apellidoBusca);
                        clienteExi=buscaApellido(apellidoBusca);
                        clienteN=clienteExi.nroCliente;
                        if (clienteExi.id !=-1&&clienteN!=-1&&clienteExi.estado!=0)
                        {
                            system("cls");
                            printf("\nEL cliente %s fue encontrado",clienteExi.apellido);
                            posicion= buscaPos(clienteN);
                            cambiaEstado(posicion,0);
                            printf("\nLa baja fue exitosa");
                            printf("\n");
                            break;
                        }
                        else
                        {
                            printf("\nEl cliente no existe o ya esta inactivo");
                            printf("\n");
                            break;
                        }
                    }
                    while(clienteExi.nroCliente!=-1);

                }
                printf("\n");
                system("pause");
            }
            while(opcionBusca!=27);
            break;
        case '5':
            creaBackUp(nomArchivo,backupClientes);
            printf("\nCompletado Exitosamente. Ubicacion : Carpeta Del Programa");
            break;
        case '6':                         ///CAMBIA ESTADO DEL CLIENTE////
            archivoEstado=fopen(nomArchivo,"r+b");
            stClientes aux;
            if (archivoEstado)
            {
                int  i=0;
                while(fread(&aux,sizeof(stClientes),1,archivoEstado)>0)
                {
                    i++;
                    cambiaEstado(i,1);
                }
            }
            fclose(archivoEstado);
            printf("\nAhora todos los clientes estan activos");
            break;
        case '7':                       /// BORRA DEL ARCHIVO TODOS LOS CLIENTES INACTIVOS///
            printf("\n!!!CUIDADO!!!! SEGURO DESEA BORRAR DE LA BASE DE DATOS LOS CLIENTES INACTIVOS\n");
            break;
        case '8':
                arbolClientesOk=archivo2ArbolOk("clientesRandom.dat",arbolClientesOk);
                arbolClientesOk=pasarConsumos2ArbolCliente(arbolClientesOk, "consumosRandom.dat");
                do
                {

                opcionBuscaEnArbol=menuBuscaEnArbol();
                switch(opcionBuscaEnArbol)
                {
                case '1':                       ///MUESTRA CLIENTE POR ID //

                    printf("\nIngrese el id del cliente a buscar\n");
                    scanf("%d", &idAbuscar);
                    if (buscaNodoArbolClientePorId(arbolClientesOk,idAbuscar)){
                    muestraUnCliente(buscaNodoArbolClientePorId(arbolClientesOk,idAbuscar)->dato);
                    }else{
                    printf("\nEl cliente no existe");
                    }
                    break;
                case '2':                        ///MUESTRA CONSUMO POR ANIO ///
                    muestraConsumosXanioXId(arbolClientesOk);
                    break;
                case '3':                           ///MUESTRA CONSUMO POR MES///
                    muestraConsumosPeriodosXID(arbolClientesOk);
                    break;
                case '4':
                        printf("\n Ingrese El Id del Cliente a Eliminar\n\n");
                        scanf("%d", &idEliminar);
                        despersistenciaOk(clientesRandom, &vClientesRandom);
                        arbolClientesOk=arregloClientes2ArbolBalanceado(clientesRandom, vClientesRandom);
                        arbolClientesOk=eliminaNodoArbol(arbolClientesOk, idEliminar);
                        printf("\n Cliente Eliminado Correctamente\n");
                        break;
                case '5':
                         postOrdenPersona(arbolClientesOk);
                         break;
                case '6':
                        altaClientePrueba=altaClienteArbol();
                        persistirNodoArbolCliente("clientesRandom.dat", altaClientePrueba);
                        muestraUnCliente(altaClientePrueba);
                        agregarArbolOk(arbolClientesOk, crearNodoArbol(altaClientePrueba));
                        break;
                case '7':
                         printf("\nIngrese el Id Del Cliente\n");
                         scanf("%d", &vConsumos);
                         altaConsumoRandomOk("consumosRandom.dat", vConsumos);
                        break;

                }
                printf("\n");
                system("pause");
            }
            while(opcionBuscaEnArbol!=27);

            break;
        case '9':
            vArregloCons =archivo2Celda(nomArchiConsumos,arregloCons,vArregloCons);
            clientesConConsumos(arbolClie,arregloCons,vArregloCons);



        }
        printf("\n");
        system("pause");
    }
    while(opcion!=27);
    return 0;

}

// //                altaClientesRandom("clientesRandom.dat", 50);
////               muestraListaClientes("clientesRandom.dat");
////
//////                int i=0;
//////                while(i<vClientesRandom){
//////                     altaConsumoRandomOk("consumosRandom.dat",clientesRandom[i].id);
//////                     muestraConsumoPorIdCliente(clientesRandom[i].id);
//////                    i++;
//////                }
//
//
