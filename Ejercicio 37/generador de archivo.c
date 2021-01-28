#include <stdio.h>

struct d{
  int clave; //Clave o Id del registro guardado
   //Descripcion
  int tipo; //Tipo de datos como entero sin signo
   //'A':Alta 'B':Baja
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
	printf("\nIngresa la clave\n");
	fflush(stdin);
	scanf("%d", &dato.clave);
	printf("\nIngresa el tipo\n");
	fflush(stdin);
	scanf("%d", &dato.tipo);
	
	fwrite(&dato,sizeof(struct d),1,fp);
	printf("\nSi desea salir presione 0\n");
	fflush(stdin);
	scanf("%d", &salida);

	
	}while(salida!=0);
	

	
	fclose(fp);
		if((fp=fopen("dato.dat","rb"))==NULL)
	{
		printf("\nNo se pudo abrir el archivo\n");
		return 0;
	}
	
	
	fread(&dato,sizeof(struct d),1,fp);
	while(!feof(fp))
	{
		printf("\nLos datos son: \nClave: %d  \nTipo: %d \n", dato.clave,  dato.tipo);
		fread(&dato, sizeof(struct d),1,fp);
	}
	fclose(fp);
	return 0;
	
}
