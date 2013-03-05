#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>

#define USAGE "./a.out archivo.dat"

void load_file(char*);
void guardar_datos2(float*,char*, int);
void crear_matriz(gsl_matrix*,float*, int , int,int );
/*void print_matrix(gsl_matrix*,int,int);
void print_vector (gsl_vector*,int);*/
void crearArchivo2(gsl_matrix*);
void find_eigens2(gsl_matrix*, gsl_vector*,gsl_matrix*);


gsl_matrix* cov_calculate2(gsl_matrix*);

float mean(gsl_matrix*, int);
float sumatoria(gsl_matrix*, int, int, int);

//////////////////////////////////////////////////MAIN///////////////////////////////////////////////7

int main(int argc, char **argv){
	
	FILE *in;
	int filas;
	int filas2;

	int columnas2=3;
	char *filename2=argv[1];
	float *vector_datos;
	float *vector_datos2;
	float *vector_x;
	
	
	if(argc!=2){
   	 	printf("USAGE: %s\n", USAGE);
   	 	exit(1);
  	}



	load_file(filename2);

	filas2=contar_filas(filename2,0);
	
	vector_datos2=malloc(3*filas2*sizeof(float));
	
	guardar_datos2(vector_datos2,filename2,filas2);


	gsl_matrix *matriz2 = gsl_matrix_alloc (filas2, columnas2);
	gsl_matrix *covarianza = gsl_matrix_alloc (columnas2, columnas2);
	gsl_vector *eigenvals= gsl_vector_alloc(columnas2);
	gsl_matrix *eigenvecs= gsl_matrix_alloc(columnas2, columnas2);
	gsl_matrix *transpuesta2 = gsl_matrix_alloc (columnas2, filas2);
	

	crear_matriz(matriz2,vector_datos2,filas2,columnas2,2);
	
	covarianza = cov_calculate2(matriz2);

	find_eigens2(covarianza, eigenvals, eigenvecs);    
	
	crearArchivo2(eigenvecs);
	
}




//////////////////////////////////////////METODOS//////////////////////////////////////////////////

/////////////////////LOAD_FILE/////////////////////////
void load_file(char *filename){
	FILE *in;
	
  	
  	in = fopen(filename,"r"); 
  	
  	if(!in){
    	printf("problem opening the file %s\n", filename);
    	exit(1);
 	} 
 	
 	printf("el archivo obtenido es: %s \n",filename);
}

/////////////////////CONTAR_FILAS/////////////////////////

int contar_filas(char *filename,int selector)
{
	FILE *in;
	int contador=0;
	int c;
	
	if(!(in=fopen(filename, "r"))){
    printf("problem opening file %s\n", filename);
    exit(1);
 	}
 	
 	
 	
	do{
    c = fgetc(in);

	if(selector==0){
		if(c=='\n'){
	    	contador++;
	    }  
	}
	
	
	 }while(c!=EOF);
	
	fclose(in);
	return contador;
}

/////////////////////GUARDAR_DATOS2/////////////////////////

void guardar_datos2(float *vector,char *filename, int filas)
{
	FILE *in;
	int i;
	
	if(!(in=fopen(filename, "r"))){
    printf("problem opening file %s\n", filename);
    exit(1);
 	}
 	
 	for(i=0;i<3*filas;i++)
 	{
 		fscanf(in,"%f %f %f", &(vector[i*3]),&(vector[i*3+1]),&(vector[i*3+2]));
 	}
}



/////////////////////CREAR_MATRIZ/////////////////////////

void crear_matriz(gsl_matrix *matriz,float *vector, int filas, int columnas,int selector)
{
  
  int n_x=filas;
  int n_y=columnas;
  int pos;
  int i,j;


  if (selector==0)
  {
	  for(i=0;i<n_x;i++){
		for(j=0;j<n_y;j++){
		  	pos = j + (n_y * i) ;
			gsl_matrix_set (matriz, i, 0, 1);
			gsl_matrix_set (matriz, i, 1, vector[2*i]);
			gsl_matrix_set (matriz, i, 2, (vector[2*i]*vector[2*i])/2);
			
		  
		}
	  }
  }
  if(selector==1)
  {
	  for(i=0;i<n_x;i++){
		
			gsl_matrix_set (matriz, i, 0, vector[2*i+1]);

	  }
  }
  if(selector==2)
  {
  	for(i=0;i<n_x;i++){
		for(j=0;j<n_y;j++){

			gsl_matrix_set (matriz, i, 0, vector[3*i]);
			gsl_matrix_set (matriz, i, 1, vector[3*i+1]);
			gsl_matrix_set (matriz, i, 2, vector[3*i+2]);
			
		}
	  }
  }


  

}


/*
/////////////////////PRINT_MATRIX/////////////////////////

void print_matrix(gsl_matrix *matriz,int filas,int columnas){

	int i=0;
	int j=0;
	for (i = 0; i < filas; ++i)
         for (j = 0; j < columnas; ++j)
             printf(j==columnas-1?" %6.3f\n":" %6.3f", gsl_matrix_get(matriz,i,j));
}



/////////////////////PRINT_VECTOR/////////////////////////


void print_vector (gsl_vector * v, int filas)
{
	int i;
 	for (i = 0; i < filas; i++) 
         {
           printf ("v_%d = %g\n", i, gsl_vector_get (v, i));
         }
     
       gsl_vector_free (v);
}*/



/////////////////////CREAR ARCHIVO 2/////////////////////////
void crearArchivo2(gsl_matrix *respuesta){
	FILE *in;
	char filename[50]="autovectores_3D_data.dat";
	int i,j,pos;
	float respuestas[8];
	in = fopen(filename,"w"); 
  	
  	if(!in){
   	 printf("problem opening the file %s\n", filename);
   	 exit(1);
 	 }  
 	 
 	for(i=0;i<3;i++){
 		for(j=0;j<3;j++){
	 		pos = j + (3 * i);
	 		respuestas[pos]=gsl_matrix_get(respuesta,i,j);
 		
 		}
 		
 	}
 	fprintf(in,"%f %f %f\n%f %f %f\n%f %f %f",respuestas[0],respuestas[1],respuestas[2],respuestas[3],respuestas[4],respuestas[5],respuestas[6],respuestas[7],respuestas[8]);
 	fclose(in);
}




/////////////////////MEAN/////////////////////////

float mean(gsl_matrix *m, int fila)
{
	gsl_vector_view a;
	int i;
	float constante = 0;
	for (i=0;i<3;i++)
	{
	constante = constante+gsl_matrix_get(m,fila,i);	
	}

	constante = constante/3;
	return constante;

}

/////////////////////SUM/////////////////////////

float sumatoria(gsl_matrix *m, int i, int j, int M)
{
	int k;
	float di,dim,dj,djm,sum=0,resta1=0,resta2=0,multi=0;
	dim=mean(m, i);
	djm=mean(m, j);
	
	for (k=0; k<M;k++)
	{
	di = gsl_matrix_get(m,i,k);
	
	dj = gsl_matrix_get(m,j,k);
	
	
	resta1 = (di-dim);
	resta2 = (dj-djm);
	sum=(resta1*resta2)+sum;	

	}
	
	sum = sum/(M-1);
	return sum;

}

/////////////////////COVARIANCE MATRIX/////////////////////////

gsl_matrix* cov_calculate2(gsl_matrix *m)
{
	int i,j;
	float sum;
	gsl_matrix *covariance = gsl_matrix_alloc (m->size2,m->size2);
	
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
		sum = sumatoria(m, i, j, 3);
		gsl_matrix_set(covariance, i, j, sum);
		}
	
	}
	return covariance;
	
}




/////////////////////EIGEN/////////////////////////

void find_eigens2(gsl_matrix *m, gsl_vector *eval,gsl_matrix *evec)
{

  gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (3);
  
  gsl_eigen_symmv (m, eval, evec, w);
  
  gsl_eigen_symmv_free (w);
  
  gsl_eigen_symmv_sort (eval, evec,GSL_EIGEN_SORT_ABS_ASC);
  
  {
	int i;
    
    for (i = 0; i < 3; i++)
      {
		double eval_i= gsl_vector_get (eval, i);
		gsl_vector_view evec_i= gsl_matrix_column (evec, i);

		
		gsl_vector_fprintf (stdout,&evec_i.vector, "%g");
      }
  }
  
  gsl_vector_free (eval);
  gsl_matrix_free (evec);

}
	
