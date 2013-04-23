#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define Pi 3.14159


	double G =  6.67*0.0000000001;
	double Mr = pow(10,34);
	double m = pow(10,29);
	double constante = 7.95*pow(10,66);
	
double func_R1p(double t,double R)
{
  return R;
}
double func_R2p(double t,double R, double P)
{
  return (G*Mr/(R*R))+((4*Pi*R*R*P)/m);
}

double llenarP(double R)
{
	return constante/(R*R*R*R*R);
}



void escribir_archivo(char* nombre_archivo, double* t, double* R,double* v,  double* P,double n_points)
{
	FILE* in;
	int i;
	in=fopen(nombre_archivo, "w");
	
	for(i=0;i<n_points;i++)
	{
		fprintf(in,"%f %f %f %f\n",t[i],R[i],v[i],P[i]);
	}
	
	
}

void RK(double* t, double* R,  double* v,  double* P ,double h,int n_points, char* nombre_archivo)
{
int i = 0;
for(i=0; i<n_points;i++)
  {
    double v2 = func_R1p(t[i],R[i]);
    double R_2 = func_R2p(t[i],R[i],P[i]);
    

    double t_middle = t[i] + (h/2.0);
    double R_middle = R[i] + (h/2.0) * v2;
    double v_middle = v[i] + (h/2.0) * R_2;
    
    
    double R_middle_prime = func_R1p(t_middle, v_middle);
    double v_middle_prime = func_R2p(t_middle, R_middle,P[i]);


    t[i+1] = t[i] + h;
    R[i+1] = R[i] + h * R_middle_prime ;
    v[i+1] = v[i] + h * v_middle_prime ;
    P[i+1] = llenarP(R[i+1]);


   //printf("%f %f %f %f\n",t[i],R[i],v[i], P[i]);
  }
	escribir_archivo(nombre_archivo,t,R,v,P,n_points);
}


/*void RK4(double* t, double* R,double* r,  double* P ,double h,int n_points, char* nombre_archivo)
{
int i;
for(i=0; i<n_points;i++)
  {
	double v = func_R1p(t[i],P[i]);
    double R_2 = func_R2p(t[i],R[i],P[i]);


// primera iter
    double t_middle = t[i] + (h/2.0);
    double R_middle = R[i] + (h/2.0) * v;
    double v_middle = P[i] + (h/2.0) * R_2;
    
    
    double R_12 = func_R1p(t_middle, v_middle);
    double R_22 = func_R2p(t_middle, R_middle,v_middle);
    
    
    // segunda iter
    
    double t_middle2 = t[i] + (h/2.0);
    double R_middle2 = R[i] + (h/2.0) * R_12;
    double v_middle2 = P[i] + (h/2.0) * R_22;
    
    
    double R_13 = func_R1p(t_middle2, v_middle2);
    double R_23 = func_R2p(t_middle2, R_middle2,v_middle2);
    
    
    // terc eriter
    
    double t_middle3 = t[i] + (h/2.0);
    double R_middle3 = R[i] + (h/2.0) * R_13;
    double v_middle3 = P[i] + (h/2.0) * R_23;
    
    
    double R_14 = func_R1p(t_middle3, v_middle3);
    double R_24 = func_R2p(t_middle3, R_middle3,v_middle3);
    
 //cuarto

	
	double averageY1=(1.0/6.0)*(v+2.0*R_12+2.0*R_13+R_14);
	
	double averageY2=(1.0/6.0)*(R_2+2.0*R_22+2.0*R_23+R_24);

    t[i+1] = t[i] + h;
    R[i+1] = R[i] + h * averageY1 ;
    P[i+1] = P[i] + h * averageY2 ;

  // printf("%f %f %f %f\n",t[i],t[i], y[i], z[i]);
  }
	escribir_archivo(nombre_archivo,t,R,P,n_points);
}*/
