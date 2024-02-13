#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "corteControl.h"

typedef char tString [20];

 typedef struct {
    int idCategoria;
    tString  descripcion;
    float precio;
    tString mes;
    int dia;
}tr_articulos;

typedef struct nodo{
	tr_articulos articulos;
	struct nodo*siguiente;
}tLista;

void iniciarArchivo();
void inicializarLista();
bool listaVacia(tLista*);
void procesarDatos();
void pregunta(char);
void menu();
void insertarVenta ();
void insertarPrimero();
void insertarAdelante();
void grabarDatos(tLista*);
void eliminarAdelante();
void visualizar(tLista*);
void finalizarRegistro();


tLista *listaVentas;
int respuestaInt;
char respuestaChar;
tr_articulos vr_articulos;
FILE*vf_registroArticulos;

int main(){
	inicializarLista();
   iniciarArchivo();
   printf("Desea realizar alguna accion? (S/N) \n");
	fflush(stdin);
	scanf("%c", &respuestaChar);
   	pregunta(respuestaChar);
    finalizarRegistro();

	
}
void inicializarLista(){
	listaVentas=NULL;
	printf("lista inicializada!\n");
}
bool listaVacia(tLista * pLista){
	return pLista==NULL;
}
void iniciarArchivo(){
    vf_registroArticulos=fopen("ventas.dat", "wb");
    if(vf_registroArticulos!=NULL){
        printf("El regisro ha sido encontrado!\n");
    }else{
        printf("OCURRIO UN ERROR!\n");
        finalizarRegistro();
    }
}


void pregunta(char pRespuesta){
  
	if(pRespuesta== 'S' || pRespuesta=='s'){
		
	printf("Que desea realizar? 1-Ingresar elemento//2-Visualizar elementos//3-Eliminar un elemento");
	fflush(stdin);
	scanf("%d", &respuestaInt);
	
	 menu();
	 
	 printf("Desea realizar alguna accion? (S/N) \n");
	fflush(stdin);
	scanf("%c", &pRespuesta);
	
 	pregunta(pRespuesta);																											//se aplica recurvididad al volver a llamar la funcion "pregunta();"

	}else{
			printf("GRACIAS POR USAR NUESTRO SERVICIO!\n");

	}

}

void menu(){
	
	
	switch (respuestaInt){
		
		case 1: insertarVenta( );
		break;
		
		case 2:visualizar(listaVentas);
		break;
			
		case 3: eliminarAdelante();
		break;
			

	}

}


void insertarVenta ( ){
	if (listaVacia(listaVentas)){
		insertarPrimero();
	}else{
		insertarAdelante();
	}
}
void insertarPrimero (){
	
	tLista * nuevoNodo;
		
	nuevoNodo=(tLista*)malloc(sizeof(tLista));
	
    printf("\nIngrese ID del producto (1-SANITARIOS// 2- BULONERIA//3-HERRAMIENTAS EN GRAL): \n");
	fflush(stdin);
	scanf("%d", &nuevoNodo->articulos.idCategoria);
	
     printf("Ingrese descripcion del mismo: \n");
	fflush(stdin);
	scanf("%s", &nuevoNodo->articulos.descripcion);
	
     printf("Ingrese precio de venta: \n");
	fflush(stdin);
	scanf("%f", &nuevoNodo->articulos.precio);
	
		
	printf("Ingrese mes de venta: \n");
	fflush(stdin);
	scanf("%s", &nuevoNodo->articulos.mes);


    printf("Ingrese dia de venta: \n");
	fflush(stdin);
	scanf("%f", &nuevoNodo->articulos.dia);

		
	
	
	nuevoNodo->siguiente=NULL;
	
	listaVentas=nuevoNodo;
	
		grabarDatos(listaVentas);

	printf("ARTICULO INGRESADO!");
	
}
void insertarAdelante(){
	
	tLista * nuevoNodo;
	
	nuevoNodo=(tLista*)malloc(sizeof(tLista));
	
	
	printf("\nIngrese ID del producto (1-SANITARIOS// 2- BULONERIA//3-HERRAMIENTAS EN GRAL): \n");
	fflush(stdin);
	scanf("%d", &nuevoNodo->articulos.idCategoria);
	
     printf("Ingrese descripcion del mismo: \n");
	fflush(stdin);
	scanf("%s", &nuevoNodo->articulos.descripcion);
	
     printf("Ingrese precio de venta: \n");
	fflush(stdin);
	scanf("%f", &nuevoNodo->articulos.precio);
	
		
	printf("Ingrese mes de venta: \n");
	fflush(stdin);
	scanf("%s", &nuevoNodo->articulos.mes);


    printf("Ingrese dia de venta: \n");
	fflush(stdin);
	scanf("%f", &nuevoNodo->articulos.dia);	
		
		
	
	nuevoNodo->siguiente=nuevoNodo;
	
	listaVentas=nuevoNodo;
	grabarDatos(listaVentas);
		printf("ARTICULO INGRESADO!");

	
}

void grabarDatos(tLista *  pLista){
    fwrite(&vr_articulos, sizeof(tr_articulos), 1, vf_registroArticulos);
    printf("Registro ingresado con exito!\n");
}

void eliminarAdelante(){
	tLista * nodoSuprimir=listaVentas;
	
	listaVentas=listaVentas->siguiente;
	printf("El nodo ha sido eliminado!\n");
	free(nodoSuprimir);
	nodoSuprimir=NULL;
}
void visualizar(tLista * pLista){
	tLista* aux;
	aux=pLista;
	printf("CATEGORIA			DESCRIPCION			PRECIO\n");
	printf("----------------------------------------------------------------------------------------------\n");

	if (!listaVacia(aux)){
		
		while (aux!=NULL){
	printf("%d		%s		%.2f\n", aux->articulos.idCategoria , aux->articulos.descripcion,aux->articulos.precio );
	
	aux=aux->siguiente;}
	}else{
		printf("NO HAY ELEMENTOS PARA MOSTRAR!\n");
	}
	
}
void finalizarRegistro(){
    fclose(vf_registroArticulos);
}
