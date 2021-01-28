#include<stdio.h>
#include<stdlib.h>


 typedef struct{
        long partNumber;
        char descripcion[40];               
    }repuestos_t;
typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestosdeposito_t;

struct cola_t{
	extraccionRepuestos_t d;
	struct cola_t *siguiente;
};





int main(){
	FILE *archivo,*archi,*nuevo;
	extraccionRepuestos_t dato;
	repuestosdeposito_t repuestos;
	int i;
	cola_t *aux,*primero=NULL,*recorrido;
		
	if((archi=fopen("lista.txt","rt+"))==NULL){
		printf("no se pudo abrir el archivo\n");
		return 1;
	}
	if((archivo=fopen("orden_de_extraccion.dat","rb"))==NULL){
		printf("no se pudo abrir el archivo\n");
		return 2;
	}
	
	fread(&dato,sizeof(extraccionRepuestos_t),1,archivo);
	while(!feof(archivo)){
		fseek(archi,0,0);
		fread(&repuestos,sizeof(repuestosdeposito_t),1,archi);
		while(dato.cantidad!=0){
		
			if(dato.repuesto.partNumber==repuestos.partNumber){
				dato.cantidad--;
				printf("datos del repuesto a retirar \n");
				printf("Numero de parte: %ld \n",repuestos.partNumber);
				printf("Numero de serie: %ld \n",repuestos.serialNumber);
				printf("Descripcion:	 %s \n",repuestos.descripcion);
				printf("Ubicacion:		 %s \n",repuestos.ubicacion);
				repuestos.partNumber=-1;
				repuestos.partNumber=-1;
				repuestos.descripcion[0]='\0';
				repuestos.ubicacion[0]='\0';
				fseek(archi,(-1L)*sizeof(repuestosdeposito_t),1);
				fwrite(&repuestos,sizeof(repuestosdeposito_t),1,archi);
			}
			fread(&repuestos,sizeof(repuestosdeposito_t),1,archi);
			if(!feof(archi)){
				if((aux=(struct cola_t*)malloc(sizeof(struct cola_t)))==NULL){
					printf("no se pudo reservar memoria dinamica \n");
					return 3;
				}
				aux->d=dato;
				if(primero==NULL){
					primero=recorrido=aux;
					aux->siguiente=NULL;
				}else{
				recorrido->siguiente=aux;
				aux->siguiente=NULL;
				recorrido=aux;
				}
				break;
			}
		}
		fread(&dato,sizeof(extraccionRepuestos_t),1,archivo);
	}
	if((nuevo=fopen("lista_nuevo.txt","wb"))==NULL){
		printf("no se pudo crear el achivo \n");
		return 4;
	}
	fseek(archi,0,0);
	fread(&repuestos,sizeof(repuestosdeposito_t),1,archi);
	while(!feof(archi)){
		if(repuestos.partNumber!=-1){
			fwrite(&repuestos,sizeof(repuestosdeposito_t),1,nuevo);
		}
	}
	remove("lista.txt");
	rename("lista_nuevo.txt","lista.txt");
	
	fclose(nuevo);
	fclose(archi);
	fclose(archivo);
	return 0;
}
