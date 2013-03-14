/*
  First writes the months of the year and its 
  corresponding number  of days to a file. 

  Afterwards it reads the same file and prints out 
  its contents to the screen.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(int argc, char **argv)
{

  
  double limite1 = atof(argv[1]);
  double limite2 = atof(argv[2]);
  double delta = atof(argv[3]);

  int pasos = (int) floor((limite2-limite1)/delta);
  double cuenta = limite1;

  double suma = 0.0;

  
  int i = 0;

  for(i=0; i<pasos;i++)
  {
	double valorf = 1/( sqrt(1+cos(cuenta)*sin(cuenta) ) );
	cuenta = cuenta+delta;
	
	suma = suma+valorf*delta;
  }
  
  printf("El valor de la integral es: %f\n", suma);
  
  return 0;
}



