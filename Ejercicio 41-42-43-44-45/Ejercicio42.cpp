#include<stdio.h>
#include<stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;

struct cola_t{
	repuestos_t d;
	struct cola_t *siguiente;
};
int main(){
	struct cola_t *aux,*recorrido,*primero=NULL;
	FILE *archivo,*archi,*nuevo;
	int c=0,i;
	
	if((archivo=fopen("lista.txt","rt"))==NULL){
		printf("no se pudo abrir el archivo");
		return 1;
	}
	if((nuevo=fopen("lista_nuevo.txt","wt"))==NULL){
		printf("no se pudo abrir el archivo");
		return 2;
	}
	if((aux=(struct cola_t*)malloc(sizeof(struct cola_t)))==NULL){
		printf("no se pudo reservar memoria dinamica");
		return 3;
	}
	fread(&aux->d,sizeof(repuestos_t),1,archivo);
	while(!feof(archivo)){
		if(aux->d.partNumber==1234){
			if(aux->d.serialNumber&(1<<3)==(1<<3)){
				if(aux->d.serialNumber&(1<<5)==(1<<5)){
				c=1;			
				if(primero==NULL){
					primero=recorrido=aux;
					primero->siguiente=NULL;
				}else{
				recorrido->siguiente=aux;
				recorrido=aux;
				}
				}else c=0;
			}else c=0;
		}else c=0;
		if(c==0){
		fwrite(&aux->d,sizeof(repuestos_t),1,nuevo);
		}else{
		if((aux=(struct cola_t*)malloc(sizeof(struct cola_t)))==NULL){
		printf("no se pudo reservar memoria dinamica");
		return 4;
		}
	}
		fread(&aux->d,sizeof(repuestos_t),1,archivo);
	}

	if((archi=fopen("fallas.txt","wt"))==NULL){
		printf("no se pudo crear el archivo \n");
		return 5;
	}
	c=0;
	aux=primero;
	while(aux!=NULL){
		aux=aux->siguiente;
		c++;
	}
	do{
		aux=primero;
		for(i=0;i<c-1;i++){
			aux=aux->siguiente;
		}
		fwrite(&aux->d,sizeof(repuestos_t),1,archi);
		free(aux);
		c--;
	}while(c!=0);

	
	fclose(archi);
	fclose(nuevo);
	fclose(archivo);
		
	remove("lista.txt");
	rename("lista_nuevo.txt","lista.txt");

	return 0;
}
