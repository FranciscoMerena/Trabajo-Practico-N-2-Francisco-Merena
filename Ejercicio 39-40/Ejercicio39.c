#include<stdio.h>
#include<stdlib.h>


struct datos_t{
	char desc[60];
	unsigned char potencia;
	unsigned int estado;
};
struct lista_t{
	struct datos_t d;
	struct lista_t *siguiente;
};

int main(){
	struct datos_t datos;
	struct lista_t *aux,*recorrido,*primero=NULL;
	FILE *archivo;
	int opc;

	if((archivo=fopen("potencia.dat","ab"))==NULL){
		printf("no se pudo crear el archivo");
		return 1;
	}
	do{
	printf("ingrese la descripcion de la medicion \n");
	gets(datos.desc);
	fflush(stdin);
	printf("ingrese la medicion de potencia \n");
	scanf("%i",&datos.potencia);
	fflush(stdin);
	datos.estado=datos.desc[0]*datos.potencia;
	printf("desea cargar mas datos? 1.si	2.no \n");
	scanf("%d",&opc);
	fflush(stdin);
	if((aux=(lista_t*)malloc(sizeof(struct lista_t)))==NULL){
		printf("no se pudo reservar memoria dinamica \n");
		return 2;
	}
	aux->d=datos;
	if(primero==NULL){
		primero=recorrido=aux;
		aux->siguiente=NULL;		
	}else{
		recorrido=primero;
		while(1){
			if(recorrido->d.potencia<aux->d.potencia){
				aux->siguiente=recorrido;
				primero=aux;
				break;
			}
			while(recorrido->siguiente!=NULL){
				if(recorrido->siguiente->d.potencia>aux->d.potencia){
				recorrido=recorrido->siguiente;
				}else break;
			}
				aux->siguiente=recorrido->siguiente;
				recorrido->siguiente=aux;
				break;
		}
	}
	}while(opc==1);
	
	while(primero!=NULL){
	aux=primero;
	fwrite(&primero->d,sizeof(struct datos_t),1,archivo);
	printf("\n descripcion: %s",primero->d.desc);
	printf("\n potencia medida: %d",primero->d.potencia);
	printf("\n estado: %d",primero->d.estado);
	primero=primero->siguiente;
	free(aux);
	}
	
	
	
	fclose(archivo);
	return 0;
}
