#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct datos_t{
char nombre[30],apellido[30];
int edad;
long telefono;
char email[30];
};

struct lista_t {
	datos_t d;
	struct lista_t *siguiente;
};
 int main()
{
 	struct lista_t *aux=NULL,*primero=NULL,*recorrido;
 	FILE *archivo,*archi;
  	if((archivo=fopen("contactos.dat","rb"))==NULL)
		{
	 	printf("error al abrir el archivo");
	 	return 1;
		}
	if((archi=fopen("contactos_ordenados.dat","wb"))==NULL)
		{
	 	printf("error al abrir el archivo");
	 	return 2;
		}
	if((aux=(struct lista_t*)malloc(sizeof(struct lista_t)))==NULL)
		{
 		printf ("no hay memoria disponible");
 		return 3;
		}
	fread(&aux->d,sizeof(struct datos_t),1,archivo);
	while(!feof(archivo))
	{		
		if(primero==NULL)
		{
		primero=aux;
		primero->siguiente=NULL;
		}else
			{
			recorrido=primero;
			while(1)
			{
			if(strcmp(recorrido->d.nombre,aux->d.nombre)>=0)
				{
					if(strcmp(recorrido->d.nombre,aux->d.nombre)==0)
					{
					if(strcmp(recorrido->d.apellido,aux->d.apellido)>0)
						{
						aux->siguiente=primero;
						primero=aux;
						break;
						}
					}else
						{
						aux->siguiente=primero;
						primero=aux;
						break;
						}
				}
				while(recorrido->siguiente)
				{
					if(strcmp(recorrido->siguiente->d.nombre,aux->d.nombre)<=0)
					{
						if(strcmp(recorrido->siguiente->d.nombre,aux->d.nombre)==0)
						{
							if(strcmp(recorrido->siguiente->d.apellido,aux->d.apellido)<0)
							{
							recorrido=recorrido->siguiente;
							}else break;													
						}else
						recorrido=recorrido->siguiente;
					}else break;
				}
				if(recorrido->siguiente==NULL)
				{
					recorrido->siguiente=aux;
					aux->siguiente=NULL;
					break;
				}
				aux->siguiente=recorrido->siguiente;
				recorrido->siguiente=aux;
				break;
				}
			}
		if((aux=(struct lista_t*)malloc(sizeof(struct lista_t)))==NULL)
		{
		printf ("no hay memoria disponible");
		return 4;
		}
		fread(&aux->d,sizeof(struct datos_t),1,archivo);
	}
recorrido=primero;
while(recorrido!=NULL)
{
	printf("%s \n",recorrido->d.nombre);
	printf("%s \n",recorrido->d.apellido);
	printf("%d \n",recorrido->d.edad);
	printf("%s \n",recorrido->d.email);
	printf("%ld \n \n",recorrido->d.telefono);	
	fwrite(&recorrido->d,sizeof(struct datos_t),1,archi);
	recorrido=recorrido->siguiente;
}
fclose(archi);
fclose(archivo);
return 0;
}
