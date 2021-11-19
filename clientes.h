#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct{
    int id;
    int nroCliente;
    char nombre[30];
    char apellido [30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char movil[12];
    int estado; ///"0" cliente dado de baja, "1" cliente activo
}stClientes;

void altaCliente (char archivoClientes[]);
void modNumCliente (stClientes c);
void despersistencia(stClientes clientes[], int* validos);
int validaNumCliente (int numCliente);
void modificaEstado();
int cuentaRegistros(char archivo[],int tamanio);
void cambiaEstado( int pos, int estado);
void creaBackUp (char archivo [], char nuevoArchivo []);
int validaMovil (char movil[12]);
int validaDni (char Dni[10]);
int validaMovil (char movil[12]);
char menu();

/// CARGA ALEATORIA CLIENTES ///

char* getNombre();
char* getApellido();
char* getDni();
char* getEmail();
char* getMovil();
char* getDomicilio();
int cargaId();
int cargaNroCliente();

void altaClientesRandom (char archivoClientes[], int validos);
void despersistenciaOk(stClientes clientes[], int* validos);
#endif // CLIENTES_H_INCLUDED
