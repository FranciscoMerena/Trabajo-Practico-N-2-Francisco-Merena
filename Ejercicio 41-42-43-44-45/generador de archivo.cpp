#include <stdio.h>
#include <time.h>
typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;


int main () {
/*	time_t t = time(NULL);
	struct tm tiempoLocal = *localtime(&t);
	char *formatohora = "%H%M%S"; */ //codigo para carga automatica de la hora
	int opc=0;
	repuestos_t d;
  	FILE *archivo;
   	
   if((archivo=fopen("ordenes.dat","wb"))==NULL){
   	printf("no se pudo crear el archivo \n");
   	return 1;
   }
   
   
    printf("ingrese el dia en el formato YYYYMMDD \n");
    gets(d.fecha);
    fflush(stdin);
    do{
    	printf("ingrese numero de orden \n");
    	scanf("%ld",&d.numeroDeOrden);
    	fflush(stdin);
    	printf("ingrese cliente \n");
    	gets(d.cliente);
    	   fflush(stdin);
		printf("ingrese descripcion de la falla \n");
    	gets(d.descripciondeFalla);
   		fflush(stdin);
    	printf("ingrese modelo \n");
    	gets(d.modelo);
    	printf("ingrese la hora en formato HHMMSS\n");
    	gets(d.hora);
  //  	strftime(d.hora,sizeof(d.hora),formatohora,&tiempoLocal);  //asignacion automatica de hora
    	fwrite(&d,sizeof(repuestos_t),1,archivo);
    	
    	printf("desea ingresar mas ordenes de trabajo? \n 1.si 2.no \n");
    	scanf("%d",&opc);
   	    fflush(stdin);
    	
	}while(opc==1);
    
   fclose(archivo);
   return 0;
}
