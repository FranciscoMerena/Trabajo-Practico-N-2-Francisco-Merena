#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;
struct lista_t{
	repuestos_t d;
	lista_t *siguiente;
};
int main(){
	FILE* archivo;
	int opc;
	struct lista_t *aux,*recorrido,*primero=NULL;
	
do{
		if((aux=(struct lista_t*)malloc(sizeof(struct lista_t)))==NULL){
		printf("No se pudo reservar memoria dinamica \n");
		return 1;
	}
	printf("ingrese numero de parte \n");
	scanf("%ld",&aux->d.partNumber);
	fflush(stdin);
	printf("ingrese numero de serie \n");
	scanf("%ld",&aux->d.serialNumber);
	fflush(stdin);
	printf("ingrse una descripcion para el producto \n");
	gets(aux->d.descripcion);
	fflush(stdin);
	printf("ingrese la ubicacion del producto \n");
	gets(aux->d.ubicacion);	
	fflush(stdin);		

	if(primero==NULL){
		primero=aux;
		primero->siguiente=NULL;
	}else{
		recorrido=primero;
		while(1){
			if(strcmp(recorrido->d.descripcion,aux->d.descripcion)>0){
				aux->siguiente=primero;
				primero=aux;
				break;
			}
			while(recorrido->siguiente!=NULL){
				if(strcmp(recorrido->siguiente->d.descripcion,aux->d.descripcion)<0){
					recorrido=recorrido->siguiente;
				}else break;
			}
			if(recorrido->siguiente==NULL){
				recorrido->siguiente=aux;
				aux->siguiente=NULL;
				break;
			}
			aux->siguiente=recorrido->siguiente;
			recorrido->siguiente=aux;
			break;
		}
	}
	aux=primero;
	while(aux!=NULL){
		printf("Numero de parte: %ld \n",aux->d.partNumber);
		printf("Numero de serie: %ld \n",aux->d.serialNumber);
		printf("Descripcion:	 %s \n",aux->d.descripcion);
		printf("Ubicacion:		 %s \n",aux->d.ubicacion);
		aux=aux->siguiente;
	}
	
	
	
	printf("desea cargar mas productos a la lista \n 1.Si	2.No  \n");
	scanf("%d",&opc);
	fflush(stdin);
}while(opc==1);	
	if((archivo=fopen("lista.txt","wt"))==NULL){
		printf("no se pudo crear el archivo \n");
	return 2;
	}
	aux=primero;
	while(aux!=NULL){
		fwrite(&aux->d,sizeof(repuestos_t),1,archivo);
		recorrido=aux;
		aux=aux->siguiente;
		free(recorrido);		
	}
	
	
	return 0;
}
