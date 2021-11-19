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

void altaCliente (char archivoClientes[]){
    char opcion=0;
    int flagEmail=0;
    int flagDni=0;
    int flagMovil=0;
    int flagNombreApellido=0;
    int id = cuentaRegistros(archivoClientes,sizeof(stClientes));
    stClientes c;
    FILE *pArchiClientes = fopen(archivoClientes,"ab");
    if (pArchiClientes!= NULL){
    do{
        do{

        printf("\n Nro de Cliente............: ");
        scanf("%d", &c.nroCliente);
        ///printf("\nValida cliente %d", validaNumCliente(c.nroCliente));
        if (validaNumCliente(c.nroCliente)==1){
            printf("El numero de clientes ingresado ya existe-Ingrese otro");
            ///printf("\nvalida Num  cliente %d", validaNumCliente(c.nroCliente));
            }
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
        id++;
        c.id = id;

        fwrite(&c, sizeof(stClientes), 1, pArchiClientes);
        printf("\n ESC para salir, otra para continuar...");
        opcion=getch();
        system("cls");
    }
    while(opcion!=27);
    fclose(pArchiClientes);
    }else{
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}
        ///MUESTRA UN CLIENTE ////
void muestraUnCliente (stClientes c){
    printf("\n Id........................: %d", c.id);
    printf("\n Nro de Cliente............: %d", c.nroCliente);
    printf("\n Nombre....................: %s", c.nombre);
    printf("\n Apellido..................: %s", c.apellido);
    printf("\n DNI.......................: %s", c.dni);
    printf("\n Email.....................: %s", c.email);
    printf("\n Domicilio.................: %s", c.domicilio);
    printf("\n Movil.....................: %s", c.movil);
    printf("\n Situacion del cliente.....: %d", c.estado);
    printf("\n-------------------------------------------------------");
}
        ///MUESTRA LISTA DE CLIENTES DESDE UN ARCHIVO////
void muestraListaClientes (char archivoClientes []){
    system("cls");
    stClientes c;
    FILE *pArchiClientes = fopen(archivoClientes, "rb");
    if(pArchiClientes != NULL){
        while(fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
            muestraUnCliente(c);
        }
        fclose(pArchiClientes);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}
        ///CUENTA REGISTROS DE UN ARCHIVO///
int cuentaRegistros(char archivo [],int tamanioSt){

    int cantidadRegistros = 0;
    FILE *p = fopen(archivo, "rb");       ///RB - Abre un archivo de binario para operaciones de lectura

    if(p!=NULL){
        fseek(p, 0, SEEK_END);      ///FSEEK - UBICA EL CURSOR EN LA POSICION INDICADA POR PARAMETRO.
        cantidadRegistros=ftell(p)/tamanioSt;  ///FTELL - INDICA LA POSICION DEL CURSOR
        fclose(p);
    }

    return cantidadRegistros;
}
        ///MUESTRA UN CLIENTE DESDE ID///
void muestraClientesId (char archivoClientes [], int clienteBuscar){
    stClientes c;
    int i=0;
    FILE *pArchiClientes = fopen(archivoClientes, "rb");
    if(pArchiClientes != NULL){
        while(fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
                i++;
                if (i== clienteBuscar){
                    muestraUnCliente(c);
                }
        }
        fclose(pArchiClientes);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}
        ///BUSCA UN CLIENTE POR APELLIDO///
void buscaClienteApellido (char archivoClientes [],char apellido[]){
    stClientes c;


    FILE *pArchiClientes = fopen(archivoClientes, "rb");
    if(pArchiClientes ){

        while(fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
                if (strcmp(c.apellido,apellido )==0){
                        muestraUnCliente(c);
                        }
        }
        fclose(pArchiClientes);
    }
}
        ///CARGA NOMBRE EN MATRIZ DE CHAR//
int cargaNombresABuscar (char n[][40], int dim){
    int i=0;
    char opcion = 0;

    while (i<dim && opcion !=27){
        printf ("\nIngrese un nombre\n");
        scanf("%s", n[i]);
        i++;
        printf("---ESC para salir---");
        opcion=getch();
        system("cls");
    }
    return i;
}
        ///MUESTRA CHAR CARGADOS EN MATRIZ//
void muestrasNomOapellido ( char n[][40], int v){

    for (int i = 0; i<v; i++){
        /*if(strcmp(n[i],"sergio")==0){
            strcpy (n[i],"otra cosa");
        }
        */
        printf("\n %s",n[i]);
    }
}
        ///MODIFICA UN CLIENTE DESDE ID///
void modificaCliente (stClientes clientes[], int validos,  int idModificar){
    stClientes c;
    int cont=0;
    int i=0;
    int nuevoValor;
    FILE *pArchi = fopen(nomArchivo, "r+b");
        if(pArchi){
            while(fread(&c, sizeof(stClientes), 1, pArchi)>0 && c.id!=idModificar){
                     i++;
                    }
            if (i < validos){
                        modificaElCliente(&clientes[i]);
                        fseek(pArchi,-1 * sizeof (stClientes),SEEK_CUR);
                        fwrite(&clientes[i], sizeof(stClientes), 1, pArchi);
                    }else{
                    printf("\n\t\tID no se encuentra en lista de clientes");
                    }
            }
            fclose(pArchi);
        }
    ///MODIFICA EL CLIENTE///
void modificaElCliente (stClientes* c){
    char opcion;
    int nuevoValor;
    do {
        opcion=menu();

        switch(opcion){
                case '1':
                    do{
                    printf("Ingrese nuevo numero de cliente\n");
                    scanf("\n%d",&nuevoValor);
                    (*c).nroCliente=nuevoValor;
                        if (validaNumCliente(nuevoValor)==1){
                            printf("\n\tNumero de cliente ya existe-Ingrese uno nuevo\n");
                        }
                    }
                    while(validaNumCliente(nuevoValor)==1);
                    break;
                case '2':
                    printf("\nIngrese un nuevo nombre\n");
                    fflush(stdin);
                    gets((*c).nombre);
                    break;
                case '3':
                    printf("\nIngrese un nuevo apellido\n");
                    fflush(stdin);
                    gets((*c).apellido);
                    break;
                case '4':
                    printf("\nIngrese un nuevo DNI\n");
                    fflush(stdin);
                    gets((*c).dni);
                    break;
                case '5':

                    fflush(stdin);
                    scanf(validaEmail((*c).email));
                    break;
                case '6':
                    printf("\nIngrese un nuevo domicilio\n");
                    fflush(stdin);
                    gets((*c).domicilio);
                    break;
                case '7':
                    printf("\nIngrese un nuevo movil\n");
                    fflush(stdin);
                    gets((*c).movil);
                    break;
                case '8':
                    printf("Situacion del cliente- 0 activo 1 inactivo\n");
                    int num;
                    scanf("%d",&num);
                    (*c).estado=num;


        }
        printf("\n");
        system("pause");
    }
    while(opcion!=27);

    return 0;
    }
    ///MENU CLIENTE///
char menu(){
        char opcion;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t Modifica datos\n\n");
    printf("\n 1 - Nro de cliente");
    printf("\n 2 - Nombre");
    printf("\n 3 - Apellido");
    printf("\n 4 - DNI");
    printf("\n 5 - Email ");
    printf("\n 6 - Domicilio");
    printf("\n 7 - Movil");
    printf("\n 8 - Situacion del cliente");
    printf("\n\nESC para salir");
    printf("\n\n\t Elija una opcion\n\n");

    opcion=getch();

    return opcion;
}
///memcpy(void *dest, const void *src, size_t n)
        ///DESPERSISTENCIA///
void despersistencia(stClientes clientes[], int* validos){
    FILE* pArch = fopen(nomArchivo,"rb");
    stClientes p;

    if (pArch != NULL){
        while (fread(&p,sizeof(stClientes),1,pArch) > 0){
            clientes[*validos] = p;
            (*validos)++;
        }
        fclose(pArch);
    }
}
    /// VALIDACION DE '@'///
void validaEmail (char pEmail[]){
    char vEmail[1][30];
    int flagEmail=0;

    do {
        if (flagEmail==0){
        printf("\n Email.....................: ");
        fflush(stdin);
        scanf("%s", &vEmail[0]);
        if (strchr(vEmail[0], 64)){
                strcpy(pEmail, vEmail[0]);
                flagEmail=1;

        } else {
          printf("Ingrese nuevamente el mail");
        }
        }
        } while (strchr(pEmail, 64)==0);

}


        /// VALIDA SI EL NUMERO DE CLIENTE YA SE ENCUENTRA///
 int validaNumCliente (int numCliente){
    int flag = 0;
    stClientes a;
    FILE*pArchi=(fopen(nomArchivo,"rb"));
    ///rewind(pArchi);                     ///NO ME SALIO COMO LO HIZO SERGIO EN LA CLASE DE 9-6-21///
    ///fseek(pArchi,0,SEEK_SET);           ///SIEMPRE RETORNA 0// ES COMO QUE NO ABRIA EL ARCHIVO//
    if (pArchi){
        while(fread(&a,sizeof(stClientes),1,pArchi)>0&&flag==0){
            if (a.nroCliente==numCliente){
                flag=1;
                return flag;
            }
        }
        fclose(pArchi);
    }
 return flag;
 }


       ///BUSCA CLIENTE POR DNI///
stClientes buscaDni ( char dni[]){

    stClientes aux;
    stClientes dniCliente;
    dniCliente.id=-1;
    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(strcmp(aux.dni,dni)==0){

            dniCliente=aux;
            flag=1;
        }
    }
    fclose(pArchi);
    }
    return dniCliente;
}


  ///BUSCA CLIENTE POR APELLIDO///
stClientes buscaApellido ( char apellido []){

    stClientes aux;
    stClientes apellidoCliente;
    apellidoCliente.id=-1;

    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(strcmp(aux.apellido,apellido)==0){

            apellidoCliente=aux;
            flag=1;
        }
    }
    fclose(pArchi);
    }
    return apellidoCliente;
}



 ///BUSCA CLIENTE POR NUMERO DE CLIENTE///
stClientes buscaPorCliente ( int numCliente){

    stClientes aux;
    stClientes cliente;
    cliente.id=-1;


    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(aux.nroCliente==numCliente){
            cliente=aux;
            flag=1;
            }
        }
        fclose(pArchi);
        }
    return cliente;
}


    ///MUESTRA LISTA DE CLIENTES ACTIVOS////
void muestraActivos (){
    system("cls");
    stClientes aux;
    FILE *pArchi = fopen(nomArchivo, "rb");
    if(pArchi){
        while(fread(&aux, sizeof(stClientes), 1, pArchi)>0){
                if (aux.estado==1){
                    muestraUnCliente(aux);

                }
        }
        fclose(pArchi);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}



///CAMBIA EL ESTADO DEL CLIENTE SEGUN POSICION/////
void cambiaEstado( int pos, int estado){
    stClientes aux;
    FILE *pArch = fopen(nomArchivo, "r+b");

    if(pArch && pos >= 0 && pos <= cuentaRegistros(nomArchivo,sizeof(stClientes))){
        fseek(pArch, sizeof(stClientes)*(pos-1), 0);
        fread(&aux, sizeof(stClientes), 1, pArch);
        aux.estado=estado;
        fseek(pArch, -1 * sizeof(stClientes), SEEK_CUR);
        fwrite(&aux, sizeof(stClientes), 1, pArch);
        fseek(pArch, sizeof(stClientes), SEEK_CUR);
        fclose(pArch);
        }
}

 ///ENCUENTRA POS A PARTIR DE NUMCLIENTES///
int buscaPos (int numClient){
    stClientes c;
    int pos=-1;
    int flag=0;


    FILE *pArchiClientes = fopen(nomArchivo, "rb");
    if(pArchiClientes ){
            while(flag !=1 && fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
                    if (c.nroCliente==numClient){
                        pos=ftell(pArchiClientes)/sizeof(stClientes);
                        flag=1;
            }
        }
        fclose(pArchiClientes);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
    return pos;
}

               /// VALIDACIONES DE DATOS ///
int validaDni (char Dni[10]){
int i=0;
int j=0;
int flag=0;

    j=strlen(Dni);

    while (i<j && flag==0){
        if (isdigit(Dni[i])){
            i++;
        }
        else {
            flag=1;

        }
    }
    return flag;
}
int validaMovil (char movil[12]){
int i=0;
int j=0;
int flag=0;

    j=strlen(movil);

    while (i<j && flag==0){
        if (isdigit(movil[i])){
            i++;
        }
        else {
            flag=1;

        }
    }
    return flag;
}
int validaNombreyApelido (char nombre_Apellido[30]){
int i=0;
int j=0;
int flag=0;

    j=strlen(nombre_Apellido);


    while (i<j && flag==0){
        if (isalpha(nombre_Apellido[i])){
            i++;
        }
        else {
            flag=1;
        }
    }
    return flag;
}

          ///CREA BACKUP DEL ARCHIVO ORIGINAL////
void creaBackUp (char archivo [], char nuevoArchivo []) {
  FILE *file1 , *file2;
    int data1 =0;

    file1 = fopen ( archivo, "r" );
    file2 = fopen ( nuevoArchivo , "w" );

    while ( (data1 = fgetc ( file1 )) != EOF ) {
        fputc ( data1, file2 );
        }

    fclose ( file1 );
    fclose ( file2 );

    return 0;
}

///                                             CARGA ALEATORIA CLIENTES                    ///

char* getNombre(){
    char *nombre = (char*)malloc(sizeof(char)*31);
    char nombres[][30]={"Marcos","Victor","Matias","Franco","Maxi","Ramiro","Rodrigo","Natalia","Federico","Roberto","Pedro","Jose"};
    strcpy(nombre, nombres[rand()%(sizeof(nombres)/30)]);

    return nombre;
}

char* getApellido(){
    char *apellido = (char*)malloc(sizeof(char)*31);
    char apellidos[][30]={"Silva","Rosti","Consorti","Strick","Fernandez","Nalgandian","Federer","Roddick","Woods","Gomez","Messi","Bolanios"};
    strcpy(apellido, apellidos[rand()%(sizeof(apellidos)/30)]);

    return apellido;
}

char* getDni(){
    char *dni = (char*)malloc(sizeof(char)*15);
    char dnis[][15]={"23.655.445","13.456.789","122.5435.66","01.223.444","32.445.777","56.336.333","569.658.236","21.558.256","78.123.554","41.258.231","39.693.578","14.936.289"};
    strcpy(dni, dnis[rand()%(sizeof(dnis)/15)]);

    return dni;
}

char* getEmail(){
    char *email = (char*)malloc(sizeof(char)*31);
    char emails[][30]={"23.655.445@.com","13.456.789@.com","122.5435.66@.com","01.223.444@.com","32.445.777@.com","56.336.333@.com","569.658.236@.com","21.558.256@.com","78.123.554@.com","41.258.231@.com","39.693.578@.com","14.936.289@.com"};
    strcpy(email, emails[rand()%(sizeof(emails)/30)]);

    return email;
}

char* getMovil(){
    char *dni = (char*)malloc(sizeof(char)*31);
    char dnis[][30]={"223 23655445","223 1356789","223 122543566","223 01223444","223 32445777","223 56336333","223 569658236","223 21558256","223 78123554","223 41258231","223 39693578","223 14936289"};
    strcpy(dni, dnis[rand()%(sizeof(dnis)/30)]);

    return dni;
}

char* getDomicilio(){
    char *apellido = (char*)malloc(sizeof(char)*31);
    char apellidos[][30]={"Cordoba 2255","Formosa 1231","Agote 12312","SAn Luis 231" "Fernandez 21312","Av Paso 1234","Colon 1231","Luro 2312","Chaco 5345","Guemes 1231","garay 4213","Roca 2132"};
    strcpy(apellido, apellidos[rand()%(sizeof(apellidos)/30)]);

    return apellido;
}
int cargaId(){
    static int id = 0;
    id++;

    return id;
}
int cargaNroCliente(){
    static int id = 0;
    id++;

    return id;
}

void altaClientesRandom (char archivoClientes[], int validos){
  FILE *pArchiClientes = fopen(archivoClientes,"ab");
  int i=0;
  stClientes c;
       if (pArchiClientes){
          while (i<validos){
               strcpy(c.apellido, getApellido());
               strcpy(c.dni, getDni());
               strcpy(c.domicilio, getDomicilio());
               strcpy(c.email, getEmail());
               strcpy(c.movil, getMovil());
               strcpy(c.nombre, getNombre());
               c.id=(cuentaRegistros(archivoClientes, sizeof(stClientes)))+cargaId();
               c.nroCliente=50+cargaNroCliente();
               c.estado=1;
               fwrite(&c, sizeof(stClientes), 1, pArchiClientes);
            i++;
          }

    }
    fclose(pArchiClientes);

}

void despersistenciaOk(stClientes clientes[], int* validos){
    FILE* pArch = fopen("clientesRandom.dat","rb");
    stClientes p;

    if (pArch != NULL){
        while (fread(&p,sizeof(stClientes),1,pArch) > 0){
            clientes[*validos] = p;
            (*validos)++;
        }
        fclose(pArch);
    }
}
