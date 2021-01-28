/*El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria. Cada técnico toma una tarea de la pila
 y genera un orden de extracción de repuestos al depósito.
 Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita utilizando la siguiente estructura:
typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;
Se pide cargar la lista de repuestos solicitados por los técnicos.
 Tener en cuenta que varios técnicos pueden necesitar la misma parte,
  y en esos casos se debe incrementar la cantidad pedida en la lista.
*/
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
}ordenesdetrabajo_t;
struct pila_t{
	ordenesdetrabajo_t d;
	struct pila_t *siguiente;
};
 typedef struct{
        long partNumber;
        char descripcion[40];               
    }repuestos_t;
typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;
struct lista_t{
	extraccionRepuestos_t d;
	struct lista_t *siguiente;
};


struct pila_t* generapila (void);



int main(){
	struct pila_t *primero_pila;
	struct lista_t *primero=NULL,*aux,*recorrido;
	int opc=1,salida=1;
	FILE* archivo;
		
		
	primero_pila=generapila();


	while(opc==1){
		printf("1.Retirar tarea de la pila \n2.generar lista de extraxion de repuestos \n");
		scanf("%d",&opc);
		fflush(stdin);
		if(opc==1){
			do{
			if((aux=(struct lista_t *)malloc(sizeof(struct lista_t)))==NULL){
				printf("no se puedo reservar memoria dinamia \n");
				return 1;
			}
			printf("Numero de orden: %ld \nDescripcion de falla: %s \nModelo: %s\n",primero_pila->d.numeroDeOrden,primero_pila->d.descripciondeFalla,primero_pila->d.modelo);
			printf("ingrese el numero de parte del repuesto a solitar \n");
			scanf("%ld",&aux->d.repuesto.partNumber);
			fflush(stdin);
			printf("ingrese una descripcion del repuesto \n");
			gets(aux->d.repuesto.descripcion);
			printf("ingrese la cantidad del repuesto a solicitar\n");
			scanf("%d",&aux->d.cantidad);
			fflush(stdin);
			
				if(primero==NULL){
					primero=aux;
					primero->siguiente=NULL;
				}else{
				recorrido=primero;
					while(1){
						if(recorrido->d.repuesto.partNumber<=aux->d.repuesto.partNumber){
							if(recorrido->d.repuesto.partNumber==aux->d.repuesto.partNumber){
								recorrido->d.cantidad+=aux->d.cantidad;
								break;
							}else{
								aux->siguiente=primero;
								primero=aux;
								break;
							}
						}
						while(recorrido->siguiente!=NULL){
							if(recorrido->siguiente->d.repuesto.partNumber<=aux->d.repuesto.partNumber){
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
			printf("necesita algun otro repuesto?\n1.si\n2.no\n");
			scanf("%d",&salida);
			fflush(stdin);
			}while(salida==1);
		}		
	}
	if((archivo=fopen("orden_de_extraccion.dat","wb"))==NULL){
		printf("no se pudo crear el archivo\n");
		return 2;
	}	


	while(primero!=NULL){
		aux=primero;
		fwrite(&primero->d,sizeof(extraccionRepuestos_t),1,archivo);
		primero=primero->siguiente;
		free(aux);
	}

fclose(archivo);	
return 0;
}


struct pila_t* generapila (void){
	struct pila_t *aux,*primero=NULL;
	FILE *archivo;
	ordenesdetrabajo_t muestreo,muestreo2;
	char maximo[10];
	int c=1,i;
	
	if((archivo=fopen("ordenes.dat","rb"))==NULL){
		printf("no se pudo abrir el archivo \n");
		return NULL;
	}
	
	if((aux=(struct pila_t*)malloc(sizeof(struct pila_t)))==NULL){
		printf("no se pudo reservar memoria dinamica \n");
		return NULL;
	}
	maximo[0]='\0';
	fread(&muestreo,sizeof(ordenesdetrabajo_t),1,archivo);
	do{
		c++; 
		if(strcmp(maximo,muestreo.hora)<0){
			strcpy(maximo,muestreo.hora);
		}
		fread(&muestreo,sizeof(ordenesdetrabajo_t),1,archivo);
	}while(!feof(archivo));
	for(i=0;i<c;i++){
		fseek(archivo,0L,0);
		fread(&muestreo,sizeof(ordenesdetrabajo_t),1,archivo);
		muestreo2.hora[0]='\0';
			do{	
				if(strcmp(muestreo.hora,maximo)<0){
					if(strcmp(muestreo2.hora,muestreo.hora)<0){
						muestreo2=muestreo;
					}
				}
				
				
				fread(&muestreo,sizeof(ordenesdetrabajo_t),1,archivo);
			}while(!feof(archivo));
		aux->d=muestreo2;
		aux->siguiente=primero;
		primero=aux;
		strcpy(maximo,muestreo2.hora);
		if((aux=(struct pila_t*)malloc(sizeof(struct pila_t)))==NULL){
			printf("no se pudo reservar memoria dinamica \n");
			return NULL;
		}
	
		
		
	}
	
fclose(archivo);

return primero;	
}

