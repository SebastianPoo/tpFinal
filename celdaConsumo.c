#include "celdaConsumo.h"
#include "clientes.h"
#include "consumos.h"
#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int alta(stCelda adl[], stConsumos e, int validos){
    nodoLista* nuevo = crearNodoLista(e);
    int pos = buscarPorID(adl, validos, e.idCliente);

    if(pos == -1){
        validos = agregarEnArreglo(adl, validos, e.idCliente);
        pos = validos - 1;
    }

    adl[pos].listaConsumos = agregarAlPrincipio(adl[pos].listaConsumos, nuevo);

    return validos;
}

int buscarPorID(stCelda adl[], int validos, int id){
    int rta = -1;
    int i=0;
    while(i<validos && rta == -1){
        if(adl[i].id==id){
            rta = i;
        }
        i++;
    }

    return rta;
}

int agregarEnArreglo(stCelda adl[], int validos, int id){
     adl[validos].id = id;
    adl[validos].listaConsumos = inicLista();
    validos++;
    return validos;
}

int archivo2Celda(char archivo [], stCelda adl[],int validos){
    stConsumos e;
    FILE *pArchiConsumos = fopen(archivo, "rb");
    if(pArchiConsumos ){

        while(fread(&e, sizeof(stConsumos), 1, pArchiConsumos)>0){
           validos=alta(adl,e,validos);
        }
        fclose(pArchiConsumos);
    }

    return validos;
}
