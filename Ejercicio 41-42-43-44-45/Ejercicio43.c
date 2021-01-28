#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;
struct pila_t{
	repuestos_t d;
	struct pila_t *siguiente;
};
/* hago la suposicion de que la hora esta en el formato HHMMSS*/
int main(){
	struct pila_t *aux,*primero=NULL;
	FILE *archivo;
	repuestos_t muestreo,muestreo2;
	char maximo[10];
	int c=1,i;
	
	if((archivo=fopen("ordenes.dat","rb"))==NULL){
		printf("no se pudo abrir el archivo \n");
		return 1;
	}
	
	if((aux=(struct pila_t*)malloc(sizeof(struct pila_t)))==NULL){
		printf("no se pudo reservar memoria dinamica \n");
		return 2;
	}
	maximo[0]='\0';
	fread(&muestreo,sizeof(repuestos_t),1,archivo);
	do{
		c++; 
		if(strcmp(maximo,muestreo.hora)<0){
			strcpy(maximo,muestreo.hora);
		}
		fread(&muestreo,sizeof(repuestos_t),1,archivo);
	}while(!feof(archivo));
	for(i=0;i<c;i++){
		fseek(archivo,0L,0);
		fread(&muestreo,sizeof(repuestos_t),1,archivo);
					muestreo2.hora[0]='\0';
			do{	
				if(strcmp(muestreo.hora,maximo)<0){
					if(strcmp(muestreo2.hora,muestreo.hora)<0){
						muestreo2=muestreo;
					}
				}
				
				
				fread(&muestreo,sizeof(repuestos_t),1,archivo);
			}while(!feof(archivo));
		aux->d=muestreo2;
		aux->siguiente=primero;
		primero=aux;
		printf("%s \n",aux->d.hora);
		strcpy(maximo,muestreo2.hora);
		if((aux=(struct pila_t*)malloc(sizeof(struct pila_t)))==NULL){
			printf("no se pudo reservar memoria dinamica \n");
			return 2;
		}
	
		
		
	}
	
fclose(archivo);

return 0;	
}
