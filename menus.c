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

    ///MUESTRA EL MENU INICIAL///
char menuInicial()
{
        char opcion;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t MENU INICIAL\n\n");
    printf("\n 1 - ALTAS");
    printf("\n 2 - MODIFICA DATOS DEL CLIENTE");
    printf("\n 3 - BUSCAR PARA MOSTRAR");
    printf("\n 4 - BAJA");
    printf("\n 5 - REALIZA BACKUP DE LOS CLIENTES");
    printf("\n 6 - ACTIVA ESTADO DE TODOS LOS CLIENTES");
    printf("\n 7 - BORRAR TODOS LOS CLIENTES INACTIVOS");
    printf("\n 8 - BUSQUEDA CLIENTES EN ARBOL");



    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcion=getch();

    return opcion;
}

  ///MENU CASE 1 ALTA DE CONSUMOS O CLIENTES///

char menuAltas()
{
        char opcionAltas;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t MENU ALTAS\n\n");
    printf("\n 1 - CLIENTES");
    printf("\n 2 - CONSUMOS");
    printf("\n 3 - ALTA CONSUMOS ALEATORIOS");
    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcionAltas=getch();

    return opcionAltas;
}

 ///MENU CASE 2-BUSCA CLIENTES PARA ALTAS O MODIFICAR DATOS///

char menuBusca()
{
        char opcionBusca;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t BUSCA CLIENTE \n\n");
    printf("\n 1 - BUSCA POR DNI");
    printf("\n 2 - BUSCA POR NUMERO DE CLIENTE");
    printf("\n 3 - BUSCA POR APELLIDO");
    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcionBusca=getch();

    return opcionBusca;
}


///MENU CASE 3-BUSCA CLIENTES PARA MOSTRAR DATOS Y CONSUMOS///

char menuMostrar()
{
        char opcionMostrar;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t MUESTRA CLIENTES \n\n");
    printf("\n 1 - BUSCA POR FECHA");
    printf("\n 2 - BUSCA POR DNI");
    printf("\n 3 - BUSCA POR NUMERO DE CLIENTE");
    printf("\n 4 - BUSCA POR APELLIDO");
    printf("\n 5 - MUESTRA CLIENTES ACTIVOS");
    printf("\n 6 - MUESTRA TODOS LOS CLIENTES");
    printf("\n");
    printf("////////  CONSUMOS ////// \n");
    printf("\n A - MOSTRAR LISTA DE CONSUMOS DE TODOS LOS CLIENTES");
    printf("\n B - CAMBIA CONSUMO POR FECHA");
    printf("\n C - MUESTRA CLIENTES CON CONSUMOS");


    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcionMostrar=getch();

    return opcionMostrar;
}

///MENU CASE 8 ARBOLES///

char menuBuscaEnArbol()
{
        char opcionBuscaEnArbol;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t BUSCA CLIENTE \n\n");
    printf("\n 1 - BUSCAR CLIENTE POR ID");
    printf("\n 2 - MOSTRAR CONSUMO TOTAL DEL ANIO POR ID");
    printf("\n 3 - MOSTRAR CONSUMO TOTAL DEL MES POR ID");
    printf("\n 4 - BORRAR CLIENTE");
    printf("\n 5 - MUESTRA CLIENTES Y SUS CONSUMOS");
    printf("\n 6 - ALTA CLIENTE");
    printf("\n 7 - ALTA CONSUMO");
    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcionBuscaEnArbol=getch();

    return opcionBuscaEnArbol;
}
