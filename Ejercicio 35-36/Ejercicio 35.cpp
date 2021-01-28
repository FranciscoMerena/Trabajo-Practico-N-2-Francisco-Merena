#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct datos_t{
char nombre[30],apellido[30];
int edad;
long telefono;
char email[30];
};

struct pila_t {
	struct datos_t d;
	struct pila_t *anterior;
};
 int main(){
 	int opc=2,i=0;
 	FILE *archivo;
 	struct pila_t *pila=NULL, *aux=NULL;
 		if((archivo=fopen("contactos.dat","ab"))==NULL){
	 	printf("error al abrir el archivo");
	 	return 1;
		}	
	 do{
 		aux=(struct pila_t*)malloc(sizeof(struct pila_t));
 		if (aux==NULL){
 			printf ("no hay memoria disponible");
 			return 2;
		}
		printf("ingrese el nombre \n");
		scanf("%s",&aux->d.nombre);
		fflush(stdin);
		printf("ingrese apellido \n");
		scanf("%s",&aux->d.apellido);
		fflush(stdin);
		printf("ingrese edad \n");
		scanf("%d",&aux->d.edad);
		fflush(stdin);
		printf("ingrese telefono \n");
		scanf("%ld",&aux->d.telefono);
		fflush(stdin);
		printf("ingrese email  \n");
		scanf("%s",&aux->d.email);
		fflush(stdin);
		
		aux->anterior=pila;
		pila=aux;
		printf("presione 1 para salir o cualquier otro numero para seguir cargando \n");
		scanf("%d",&opc);
		}while (opc!=1);	
	
do{ 
 	if(pila->d.edad>21){
 		printf("%s \n",pila->d.nombre);
 		printf("%s \n",pila->d.apellido);
 		printf("%d\n",pila->d.edad);
 		printf("%ld \n",pila->d.telefono);	
 		printf("%s \n \n",pila->d.email);
 		fwrite(&pila->d,sizeof(struct datos_t),1,archivo);
 	 	}
 		aux=pila;
 		pila=pila->anterior;
 		free(aux);
	 }	while(pila->anterior!=NULL);
		printf("%s \n",pila->d.nombre);
 		printf("%s \n",pila->d.apellido);
 		printf("%d\n",pila->d.edad);
 		printf("%ld \n",pila->d.telefono);	
 		printf("%s \n \n",pila->d.email);
 		fwrite(&pila->d,sizeof(struct datos_t),1,archivo);
 	
 	fclose(archivo);
 	return 0;
 }

