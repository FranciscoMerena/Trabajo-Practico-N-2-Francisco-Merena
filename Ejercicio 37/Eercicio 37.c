#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct d{
	long clave;
	char d[30];
	unsigned char tipo;
	char b;
};
struct pila_t{
	long clave,posicion;
	struct pila_t *siguiente;
};
 struct pila_t* apilador(long,struct pila_t*);
int main()
{
	FILE *archivo;
	struct pila_t *aux=NULL;
	int opc;
	long clave;
	struct d datos;
	
	if((archivo=fopen("datos.dat","rb"))==NULL){
		printf("no se pudo leer archivo o no existe \n");
		return 1;
	}
	do{
	printf("ingrese la clave del registro que desea apilar \n");
	scanf("%ld",&clave);
	fflush(stdin);
	aux=apilador(clave,aux);
	printf("desea apilar otro regustro? 	1.si	 2.no \n");
	scanf("%d",&opc);
	fflush(stdin);
	}while(opc==1);
	while(aux!=NULL){
		fseek(archivo,(1L)*(aux->posicion)*sizeof(struct d),0);
		fread(&datos,sizeof(struct d),1,archivo);
		printf("%s \n",datos.d);
		aux=aux->siguiente;
	}
	
	
	
	return 0;
}
struct pila_t* apilador(long clave,struct pila_t* primero)
{
	FILE *archivo;
	struct d auxiliar;
	int esta=0;
	long i=0;
	struct pila_t *aux;
if((archivo=fopen("datos.dat","rb"))==NULL){
		printf("no se pudo leer archivo o no existe \n");
		return primero;
	}
	fread(&auxiliar,sizeof(struct d),1,archivo);
	while(!feof(archivo))
	{
	
	if(auxiliar.clave==clave){
		esta=1;
		if(((auxiliar.tipo)&(1<<4))==(1<<4)){
			
			if((aux=(pila_t*)malloc(sizeof(pila_t)))==NULL){
				printf("no se pudo reservar memoria dinamica \n");
				return primero;
			}
			aux->clave=clave;
			aux->posicion=i;
			if(primero==NULL){
				primero=aux;
				primero->siguiente=NULL;
			}else{
				aux->siguiente=primero;
				primero=aux;
			}
		}else{
			printf("el bit 4 no cumple con la condicion \n");
		}
		break;
	}

	fread(&auxiliar,sizeof(struct d),1,archivo);
	i++;
	}
	if(esta!=1){
	printf("el registro no pudo ser encontrado en el archivo \n");
}
	fclose(archivo);
	return (primero);
}





