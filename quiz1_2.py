# -*- coding: latin-1 -*-
import sys, string, os
import numpy as np

archivo = sys.argv[1];

m1 = [0]*20
m2 = [0]*20
i = 0


infile = open(archivo, 'r');

for line in infile:
		
		if(i < 20):
			x = str(line)
			linea= x.partition(" ");
			m1[i] = linea[0]
			linea2 = str(linea[2]).partition(" ");
			linea3 = str(linea2[0]).partition("\n")
			m2[i] = linea3[0];
			i=i+1



i=0;
for x in m1:
		m1[i] = np.log( float(m1[i]) )
		m2[i] = np.log( float(m2[i]) )
		i=i+1;


numero = np.polyfit(m1,m2,1)


final = open("VALOR_DE_K_DEL_LIBRO_"+archivo,"w")
final.write( str(numero[0]))
