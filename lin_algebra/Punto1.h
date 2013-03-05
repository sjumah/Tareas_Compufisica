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

void load_file(char*);
void guardar_datos(float*,char*, int);
void guardar_datos2(float*,char*, int);
void crear_matriz(gsl_matrix*,float*, int , int,int );
void crearArchivo(gsl_matrix*);


gsl_matrix* transpose(gsl_matrix*,int ,int);
gsl_matrix* multiply(gsl_matrix *,gsl_matrix *,int,int );
gsl_matrix* inverse(gsl_matrix*,int);
