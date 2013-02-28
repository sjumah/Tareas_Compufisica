# -*- coding: latin-1 -*-
import sys, string, os
import numpy as np

archivo = sys.argv[1];

frecuencia= [0]*1000
caracter = [""]*1000

k=0;


def nuevo_caracter(nuevo):
		i=0
		termino = 0
		for x in caracter:
				if(caracter[i] == "" and termino == 0 and  nuevo != " " and  nuevo != "\n" and  nuevo != "." and  nuevo != "," and  nuevo != ":" and  nuevo != ";" and  nuevo != "!" and  nuevo != "?" and  nuevo != "¿" and  nuevo != "¡" and  nuevo != "(" and  nuevo != ")" and nuevo != chr(13)) and  nuevo != "'":
						caracter[i] = nuevo
						frecuencia[i] = 1
						termino = 1
				i=i+1



def agregar_caracteres(linea):
		encontro = 0;
		for x in linea:
				j=0
				for y in caracter:
						if(x == y):
								frecuencia[j] = frecuencia[j]+1
								encontro = 1
						j=j+1
				if(encontro == 0):
						nuevo_caracter(x)
				encontro=0
						

	

#for i in range(n_args):
#   print sys.argv[i]

# read the file
infile = open(archivo, 'r')

for line in infile:
        agregar_caracteres(line)

        

matriz = [frecuencia,caracter]


from operator import itemgetter
inv = zip(*matriz)
inv.sort(reverse = 1,key=itemgetter(0))
matriz = zip(*inv)


total = 0.0;

for a in frecuencia:			
	total += a



final = open("Frecuencias_"+archivo,"w")

for x in frecuencia:
		parte1=matriz[0][k]
		parte2=matriz[1][k]
		
		parte1int = parte1*100/total
		
		parte1= str(parte1int)

		valork = str(k+1)

		
		value = valork+ " "+parte1 + "\n"
		
		if(parte2 != ""):
				final.write(value)
		k = k+1
		
		
