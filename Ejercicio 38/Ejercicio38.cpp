#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct cola_t{
	char m;
	cola_t *siguiente;
};
int main(){
	struct cola_t *aux=NULL,*primero=NULL,*ultimo;
	int i=0,k=0,r=0,x;
	float P=3.14159265;
	printf("ingrese el tamaño de la puestra para el cuarto de la señal senoidal \n");
	scanf("%d",&k);
	fflush(stdin);


	for(i=0;i<k;i++){
		if((aux=(struct cola_t*)malloc(sizeof(struct cola_t)))==NULL){
			printf("error al reservar memoria dinamica \n");
			return 0;
		}
		aux->m=128*(sin((P*i)/(2*k)));
		if(primero==NULL){
			primero=ultimo=aux;
			aux->siguiente=NULL;
		}else
		{
			ultimo->siguiente=aux;
			aux->siguiente=NULL;
			ultimo=aux;
		}
	}
for(x=0;x<6;x++){
	aux=primero;
	while(aux!=NULL){
		printf("%i \n",aux->m);
		aux=aux->siguiente;	
	
	}	
	aux=primero;
		for(r=k-1;r>0;r--){
			for(i=0;i<r;i++){
			aux=aux->siguiente;
			}
			if(aux->siguiente!=NULL)
			printf("%d \n",aux->m);
			aux->m=aux->m^(1<<7); 
			aux=primero;
		}
}
		
		
	
	
	
	return 0;
}
