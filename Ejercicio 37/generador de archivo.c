#include <stdio.h>

struct d{
	long clave;
	char d[30];
	unsigned char tipo;
	char b;
};


int main()
{
	FILE* fp;
	struct d dato;
	int salida;
	if((fp=fopen("datos.dat","wb"))==NULL)
	{
		printf("\nNo se pudo abrir el archivo\n");
		return 0;
	}
	do
	{
	printf("Ingresa la clave\n");
	fflush(stdin);
	scanf("%d", &dato.clave);
	printf("\nIngresa el tipo\n");
	fflush(stdin);
	scanf("%d", &dato.tipo);
	printf("\ningrese descripcion\n");
	fflush(stdin);
	scanf("%s",&dato.d);
	printf("\ningrese etiqueta\n");
	fflush(stdin);
	scanf("%c",&dato.b);
	
	
	
	fwrite(&dato,sizeof(struct d),1,fp);
	printf("\nSi desea salir presione 0\n");
	fflush(stdin);
	scanf("%d", &salida);

	
	}while(salida!=0);
	

	
	fclose(fp);
		if((fp=fopen("datos.dat","rb"))==NULL)
	{
		printf("\nNo se pudo abrir el archivo\n");
		return 0;
	}
	
	fseek(fp,0L,0);
	fread(&dato,sizeof(struct d),1,fp);
	while(!feof(fp))
	{
		printf("\nLos datos son: \nClave: %ld  \nTipo: %d \n", dato.clave,  dato.tipo);
		fread(&dato, sizeof(struct d),1,fp);
		
	}
	getchar();
	fclose(fp);
	return 0;
	
}
