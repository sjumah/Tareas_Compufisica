#include "Punto1.h"


void crearArchivo(gsl_matrix *respuesta)
{
	FILE *in;
	char filename[40]="parametros_movimiento.dat";
	int i;
	float respuestas[3];
	in = fopen(filename,"w"); 
  	if(!in)
  	{
   	 printf("problem opening the file %s\n", filename);
   	 exit(1);
 	}  
 	 
 	for(i=0;i<3;i++)
 	{
 		respuestas[i]=gsl_matrix_get(respuesta,i,0);
 		
 	}
 	
 	fprintf(in,"%f %f %f",respuestas[0],respuestas[1],respuestas[2]);
 	fclose(in);
}

void load_file(char *filename)
{
	FILE *in;
	  	
  	in = fopen(filename,"r"); 
  	
  	if(!in){
    	printf("problem opening the file %s\n", filename);
    	exit(1);
 	} 
 	
 	printf("el archivo obtenido es: %s \n",filename);
}


void guardar_datos(float *vector,char *filename, int filas)
{
	FILE *in;
	int i;
	
	if(!(in=fopen(filename, "r")))
	{
    printf("problem opening file %s\n", filename);
    exit(1);
 	}
 	
 	for(i=0;i<2*filas;i++)
 	{
 		fscanf(in,"%f %f", &(vector[i*2]),&(vector[i*2+1]));
 	}
}


int contar_filas(char *filename,int selector)
{
	FILE *in;
	int contador=0;
	int c;
	
	if(!(in=fopen(filename, "r")))
	{
    	printf("problem opening file %s\n", filename);
    	exit(1);
 	}
 	
	do
	{
    	c = fgetc(in);

		if(selector==0)
		{
			if(c=='\n')
			{
	    		contador++;
	    	}  
		}
	}
	
	while(c!=EOF);
	
	fclose(in);
	return contador;
}

void crear_matriz(gsl_matrix *matriz,float *vector, int filas, int columnas,int selector)
{
  
  int n_x=filas;
  int n_y=columnas;
  int pos;
  int i,j;


  if (selector==0)
  {
	  for(i=0;i<n_x;i++)
	  {
		for(j=0;j<n_y;j++)
		{
		  	pos = j + (n_y * i) ;
			gsl_matrix_set (matriz, i, 0, 1);
			gsl_matrix_set (matriz, i, 1, vector[2*i]);
			gsl_matrix_set (matriz, i, 2, (vector[2*i]*vector[2*i])/2);
		}
	  }
  }
  
  if(selector==1)
  {
	  for(i=0;i<n_x;i++)
	  {
			gsl_matrix_set (matriz, i, 0, vector[2*i+1]);
	  }
  }
  
  if(selector==2)
  {
  	for(i=0;i<n_x;i++)
  	{
		for(j=0;j<n_y;j++)
		{

			gsl_matrix_set (matriz, i, 0, vector[3*i]);
			gsl_matrix_set (matriz, i, 1, vector[3*i+1]);
			gsl_matrix_set (matriz, i, 2, vector[3*i+2]);
			
		}
	}
  }
}

int main(int argc, char **argv)
{
	
	FILE *in;
	int filas;
	int filas2;
	int columnas=3;
	int columnas2=3;
	char *filename=argv[1];
	char *filename2=argv[2];
	float *vector_datos;
	float *vector_datos2;
	float *vector_x;
	


	load_file(filename);
	
	filas=contar_filas(filename,0);
	
	gsl_matrix *transpuesta = gsl_matrix_alloc (columnas, filas);
	gsl_matrix *matriz = gsl_matrix_alloc (filas, columnas);
	gsl_matrix *multiplicacion = gsl_matrix_alloc (filas, filas);
	gsl_matrix *vector = gsl_matrix_alloc (filas, 1);
	gsl_matrix *inversa = gsl_matrix_alloc (filas, filas);
	gsl_matrix *multiplicacion2 = gsl_matrix_alloc (columnas, 1);
	gsl_matrix *multiplicacion3 = gsl_matrix_alloc (columnas, 1);



	vector_datos=malloc(2*filas*sizeof(float));
	
	guardar_datos(vector_datos,filename,filas);

	crear_matriz(matriz,vector_datos,filas,columnas,0);
	
	crear_matriz(vector,vector_datos,filas,1,1);
	
	transpuesta=transpose(matriz,columnas,filas);
	
	
	multiplicacion=multiply(transpuesta,matriz,columnas,columnas);
	
	inversa=inverse(multiplicacion,columnas);
	
	multiplicacion2=multiply(transpuesta,vector,columnas,1);
	
	multiplicacion3=multiply(inversa,multiplicacion2,columnas,1);

	crearArchivo(multiplicacion3);


}






gsl_matrix* multiply(gsl_matrix *matriz1,gsl_matrix *matriz2,int filas,int columnas)
{
		gsl_matrix *multiplicacion = gsl_matrix_alloc (filas, columnas);
		gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,1.0, matriz1,matriz2, 0.0, multiplicacion);
		return multiplicacion;
}


gsl_matrix* inverse(gsl_matrix *matriz,int filas)
{    
    int s;
    gsl_matrix *inversa = gsl_matrix_alloc (filas, filas);
    gsl_permutation * p = gsl_permutation_alloc (filas);
     
    gsl_linalg_LU_decomp (matriz, p, &s);    
    gsl_linalg_LU_invert (matriz, p, inversa);
    
    gsl_permutation_free (p);
    
	return inversa;
}



gsl_matrix* transpose(gsl_matrix *m,int columnas,int filas)
{	
	gsl_matrix *transpuesta = gsl_matrix_alloc (columnas, filas);
	gsl_matrix_transpose_memcpy(transpuesta,m);

	return transpuesta;

}


