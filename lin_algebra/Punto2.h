#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>


void load_file(char*);
void guardar_datos2(float*,char*, int);
void crear_matriz(gsl_matrix*,float*, int , int,int );
void crearArchivo2(gsl_matrix*,float,float,float);
void find_eigens2(gsl_matrix*, gsl_vector*,gsl_matrix*);


gsl_matrix* cov_calculate2(gsl_matrix*);

float mean(gsl_matrix*, int);
float sumatoria(gsl_matrix*, int, int, int);
float calcular_norma(gsl_matrix *, int );
