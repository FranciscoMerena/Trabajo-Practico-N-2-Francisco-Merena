#include<stdlib.h>
#include<stdio.h>

struct datos_t{
	char desc[60];
	unsigned char potencia;
	unsigned int estado;
};
struct pila_t{
	unsigned char potencia;
	struct pila_t *siguiente;
};

struct pila_t* funcionmagica(int,struct pila_t*);

int main(){
	int id,opc;
	struct pila_t *primero=NULL;
	do{
	printf("ingrese id del registro al que desea modificar automaticamente \n");
	scanf("%d",&id);
	fflush(stdin);
	primero=funcionmagica(id,primero);
	printf("\n desea modificar mas registros	1.si	2.no \n");
	scanf("%d",&opc);
	fflush(stdin);
	}while(opc==1);
	
	
	
	return 0;
}
struct pila_t* funcionmagica(int id,struct pila_t *primero){
	struct pila_t *aux;
	struct datos_t data;
	char *p;
	int c=0,i;
	FILE *archivo,*archi;
	
	if((archivo=fopen("potencia.dat","rb"))==NULL){
		printf("error al abrir el archivo \n");
		return primero;
	}
	if((archi=fopen("salida.dat","ab"))==NULL){
		printf("error al abrir el archivo \n");
		return primero;
	}
	fseek(archivo,(1L)*sizeof(struct datos_t)*(id-1),0);
	fread(&data,sizeof(struct datos_t),1,archivo);
	p=data.desc;
	while(p[c]!=' '){
	c++;
	}
	for(i=0;i<=c;i++)
	printf("%c",p[c-i]);
	printf("\n");
	data.estado=data.estado^(1<<3);
	fwrite(&data,sizeof(struct datos_t),1,archivo);
	c=3;
	if((data.estado&(1<<2))==(1<<2)){
		if((data.estado&(1<<0))==(1<<0)){
			if((aux=(struct pila_t*)malloc(sizeof(struct pila_t)))==NULL){
				printf("no se pudo reservar memoria dinamica \n");
				return primero;
			}
			printf("se agrego el registro a la pila \n");
			aux->potencia=data.potencia;
			if(primero==NULL){
				primero=aux;
				primero->siguiente=NULL;
			}else{
				aux->siguiente=primero;
				primero=aux;
				}
		}else c=1;
	}else c=0;
	if(c==0||c==1){
		printf("%i \n",c);
		fwrite(&data,sizeof(struct datos_t),1,archi);
		printf("se agrego el registro al archivo salida.dat \n");
	}


fclose(archivo);
fclose(archi);
return(primero);	
}
