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
void altaConsumo (char archivoConsumos[], int idStCliente) {
    int mes[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
     int validacion=0;
    int validacion2=0;
    int vDia=0;
    int idCliente=idStCliente;
    int vMes=0;
    int vAnio=0;
    char opcion=0;
    int suma=0;
    stConsumos con;
    int id = cuentaRegistros(archivoConsumos, sizeof(stConsumos));

    FILE *pArchi = fopen(archivoConsumos,"ab");
    if (pArchi!= NULL) {
        do {


             do {
                printf("\n A%co ",164);
                scanf("%d" , &con.anio);
                vAnio=cargaAnio(con.anio);
             }while(vAnio==0);
            do {
                printf("\nMes ");
                scanf("%d" , &con.mes);
                vMes=cargaMes(con.mes);
             }while(vMes==0);
             do {
                printf("\nDia\t");
                scanf("%d" , &con.dia);
                vDia=cargaDia(con.dia);
             }while(vDia==0);

            printf("\n MB consumidos en la fecha: ");
            scanf("%d", &con.datosConsumidos);
            con.idCliente=idCliente;
            con.estado=1;
            id++;
            con.id = id;
             if (sumaConsumoFecha(con)>0){
                suma=sumaConsumoFecha(con);
                con.datosConsumidos=suma;
                }
            fwrite(&con, sizeof(stConsumos), 1, pArchi);
            printf("\n ESC para salir.");
            opcion=getch();
            system("cls");
        } while(opcion!=27);
        fclose(pArchi);
    } else {
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

void muestraUnConsumo (stConsumos consumo) {


        printf("\n Id Numero              %d", consumo.id);
        printf("\n Id de Cliente numero   %d", consumo.idCliente);
        printf("\n A%co                  [%d]",164, consumo.anio);
        printf("\n Mes                   [%d]", consumo.mes);
        printf("\n Dia                   [%d]", consumo.dia);
        printf("\n Consumos del dia      [%d]mb", consumo.datosConsumidos);
        printf("\n[1]activo[0]inactivo  -[%d]-", consumo.estado);///0 para inactivo, 1 para activo
        printf("\n-------------------------------------------------------");

}

///MUESTRA LISTA DE CLIENTES DESDE UN ARCHIVO////
void muestraListaConsumos () {
    stConsumos con;
    FILE *pArchi= fopen(nomArchiConsumos, "rb");

    if(pArchi) {
            system("cls");
        while(fread(&con, sizeof(stConsumos), 1, pArchi)>0) {
            muestraUnConsumo(con);
        }
        fclose(pArchi);

    } else {
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

char menuConsumo() {
    char opcion;


    system("cls");
    system("color 3F");
    printf("\n\t\t\t Busqueda por:");
    printf("\n 1 - Fecha");
    printf("\n 2 - id");
    //system("cls");
    printf("\n\nESC para salir");
    printf("\n\n\t Elija una opcion\n\n");

    opcion=getch();
    system("cls");
    return opcion;
}

void muestraConsumoPorIdCliente (int idClien) {
    stConsumos aux;
    int flag=0;
    FILE *pArchiCons= fopen(nomArchiConsumos, "rb");
    if(pArchiCons) {
        while(flag!=1&&fread(&aux, sizeof(stConsumos), 1, pArchiCons)>0) {
            if(aux.idCliente==idClien) {
                muestraUnConsumo(aux);
                }
            }
            fclose(pArchiCons);
        } else {
            printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

/// busca por fecha
int sumaConsumoFecha(stConsumos a){
    stConsumos fecha;
    stConsumos arrayConsumos [100];
    int i=0;
    FILE *archi=fopen ("consumos.dat", "rb");
    if (archi) {
        while (fread(&fecha, sizeof(stConsumos), 1, archi)>0){
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia){
                i=fecha.datosConsumidos+a.datosConsumidos;
                }
            }
            fclose(archi);
    }
    return i;
}


///funcion de suma
int sumaConsumo(int a) {
    int suma=0;
    suma= suma + a;
    return suma;
}
/// verifica si el cliente existe
int existeConsumoCliente(char archivo[],int idCliente) {
    int flag=0;
    stClientes aux;
    stConsumos auxC;
    FILE *pArchi= fopen(archivo, "rb");
    if (pArchi) {
        while(fread(&aux, sizeof(stClientes), 1, pArchi)>0 && flag==0) {
            if(aux.id==idCliente) {
                auxC.idCliente=idCliente;
                flag=1;
            }
        }
        fclose(pArchi);
    }
    return flag;
}

///CARGA MES VALIDANDO DATO///
int cargaMes(int fecha) {
    int flag=0;
        if (fecha>=1 && fecha<=12) {
            flag=1;
        } else {
            printf("\n Mes incorrecto\n");
            system("pause");
        }
    return flag;
}


///CARGA DIA VALIDANDO DATO///
int cargaDia (int dato) {
    int flag=0;
        if (dato > 0 && dato < 31) {
            flag=1;
            }else{
    printf("\n Dia incorrecto\n");
    system("pause");
    }
            return flag;
}


///CARGA AÑO VALIDANDO DATO///
int cargaAnio(int anio) {
 int flag = 0;
    if(anio<=ANIO && anio > (ANIO-20)) {
        flag=1;
    }else{
    printf("\n Ingrese a%co dentro los ultimos 20 a%os\n",164,164);
    system("pause");
    }
  return flag;
}

///MUESTRA POR FECHA AXACTA///
void mostrarXFecha(char archivoConsumo[]) {
    stConsumos fecha;
    stConsumos a;
    int flag=0;
    system("cls");

    printf(" Ingrese la Fecha a Buscar Consumos \n");
    printf("\n ingrese el a%co\n",164);
    scanf("\n %d", &fecha.anio);
    printf("\n ingrese el mes\n");
    scanf("\n %d", &fecha.mes);
    printf("\n ingrese un dia\n");
    scanf("\n %d", &fecha.dia);

    FILE *archi=fopen ("consumos.dat", "rb");
    if (archi) {
        while (fread(&a, sizeof(stConsumos), 1, archi)>0){
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia){
                muestraUnConsumo(a);
                flag=1;
            } else {
             flag=2;
            }
        }
        fclose(archi);
    }
     if (flag==2){
        printf("\nEn la Fecha Ingresada No Existen Consumos");
     }

}

///CAMBIA CONSUMO POR FECHA////

void cambiaConsumo(char archivoConsumo []){
    stConsumos fecha;
    stConsumos a;
    int consumo=0;
    int flag=0;

    printf("Ingrese el numero de cliente");
    scanf("%d", &fecha.idCliente);
    printf(" Ingrese la Fecha del Consumo a Cambiar \n");
    printf("\n ingrese el anio\n");
    scanf("\n %d", &fecha.anio);
    printf("\n ingrese el mes\n");
    scanf("\n %d", &fecha.mes);
    printf("\n ingrese un dia\n");
    scanf("\n %d", &fecha.dia);

    FILE *archi = fopen(archivoConsumo, "r+b");
     if (archi) {
            while (fread(&a, sizeof(stConsumos), 1, archi)){
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia && fecha.idCliente==a.idCliente && flag==0){
                fseek(archi, sizeof(stConsumos)*(-1), SEEK_CUR);
                printf("\nINGRESE EL NUEVO CONSUMO\n");
                scanf("%d", &a.datosConsumidos);
                fwrite(&a, sizeof(stConsumos), 1, archi);
                fseek(archi, sizeof(stConsumos), SEEK_SET);
                flag=1;
            }

    }
        fclose(archi);

}
}

            /// FUNCIONES PARA CARGA ALEATORIO///

 int clienteRandom (){
     srand(time(NULL));
     int cantRegi;
     int random=0;
     cantRegi=cuentaRegistros(nomArchivo,sizeof(stClientes));
    int numRegistro;
        random=rand()%cantRegi;
        if(random>0){
            numRegistro=random;
            }
    return numRegistro;
 }

  /// MES ALEATORIO///
 int mesRandom (){
     srand(time(NULL));
    int mesR=0;

    while (mesR==0){
            mesR=rand()%12;
            }
    return mesR;
 }
        /// DIA ALEATORIO///
 int diaRandom (){
     srand(time(NULL));
    int diaR=0;

    while (diaR==0){
            diaR=rand()%30;
            }
    return diaR;
 }
        ///  CARGA CONSUMO A UN CLIENTE, EN EL DIA Y UN MES ALEATORIO///
 void altaConsumoRandom (char archivoConsumos[], int idStCliente, int mesR, int dia) {
    int mes[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    int idCliente=idStCliente;
    char opcion=0;
    int suma=0;
    stConsumos con;
    int id = cuentaRegistros(archivoConsumos, sizeof(stConsumos));

    FILE *pArchi = fopen(archivoConsumos,"ab");
    if (pArchi) {
            con.anio=2021;
            con.mes=mesR;
            con.dia=dia;

            con.datosConsumidos=1000;
            con.idCliente=idCliente;
            con.estado=1;
            id++;
            con.id = id;
             if (sumaConsumoFecha(con)>0){
                suma=sumaConsumoFecha(con);
                con.datosConsumidos=suma;
                }
            fwrite(&con, sizeof(stConsumos), 1, pArchi);


        fclose(pArchi);
    } else {
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

///BUSCA UN CLIENTE DESDE LA POSICION DEL ARCHIVO///
stClientes buscaIdCliente(char archivo[], int pos){
    stClientes aux;
    FILE *pArch = fopen(archivo, "rb");

    if(pArch && pos >= 0 && pos <= cuentaRegistros(archivo, sizeof(stClientes))){
        fseek(pArch, sizeof(stClientes)*pos, 0);
        fread(&aux, sizeof(stClientes), 1, pArch);

        fclose(pArch);
    }

    return aux;
}


///BUSCA CLIENTE POR NUMERO DE ID///
stClientes buscaPorId ( int id){

    stClientes aux;
    stClientes cliente;
    cliente.id=-1;


    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(aux.id==id){
            cliente=aux;
            flag=1;
            }
        }
        fclose(pArchi);
        }
    return cliente;
}

/// consumos ////

void altaConsumoRandomOk (char archivoConsumos[], int idStCliente) {
    int mes[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    int idCliente=idStCliente;
    int i =0;
    int suma=0;
    stConsumos con;
    int id = cuentaRegistros(archivoConsumos, sizeof(stConsumos));

    FILE *pArchi = fopen(archivoConsumos,"ab");
    if (pArchi) {
            while (i<30){
            con.anio=getYear();
            con.mes=rand()%12;
            con.dia=rand()%30;
            con.datosConsumidos=rand()%1000;
            con.idCliente=idStCliente;
            con.estado=1;
            con.id = id++;

            fwrite(&con, sizeof(stConsumos), 1, pArchi);

            i++;
            }
        fclose(pArchi);
    } else {
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

int* getYear(){
    int* year = (int*)malloc(sizeof(int)*6);
    int years[6]={2021,2020,2019,2018};
    year= years[rand()%4];

    return year;
}

stConsumos altaConsumoArbol () {
    int mes[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
     int validacion=0;
    int validacion2=0;
    int vDia=0;
    int idCliente=0;
    int id=0;
    int vMes=0;
    int vAnio=0;
    char opcion=0;
    int suma=0;
    stConsumos con;

               printf("\n Ingrese El Id del Cliente \n");
               scanf("%d", &con.id);
             do {
                printf("\n A%co ",164);
                scanf("%d" , &con.anio);
                vAnio=cargaAnio(con.anio);
             }while(vAnio==0);
            do {
                printf("\nMes ");
                scanf("%d" , &con.mes);
                vMes=cargaMes(con.mes);
             }while(vMes==0);
             do {
                printf("\nDia\t");
                scanf("%d" , &con.dia);
                vDia=cargaDia(con.dia);
             }while(vDia==0);

            printf("\n MB consumidos en la fecha: ");
            scanf("%d", &con.datosConsumidos);
            con.idCliente=100+cargaNroCliente();
            con.estado=1;



  return con;
}


void persistirConsumo (char archivo [], stConsumos consumo){
  FILE *archi = fopen("consumosRandom.dat", "ab");

  if (archi){

       fwrite(&consumo, sizeof(stConsumos), 1, archi);
  }
    fclose(archi);
}
