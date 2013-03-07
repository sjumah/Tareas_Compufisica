#%pylab inline
import pylab as pyl
import os
import sys
import numpy as np

#obtener datos
#filename = "./ResultadosGXY/"
#dir = os.path.dirname(filename)
#os.path.mkdir(dir)
ruta ="./hw4_data/"
ruta2="./ResultadosGXY/resultados.dat"
ruta3="./ResultadosGXY/vectores_propios.dat"
ruta4="./ResultadosGXY/datos_sinfit.dat"
carpeta=os.listdir(ruta);
i=0;

resultadosGXY = open(ruta2,"w")	

resultadosGXY.write("#" + "" + "v_y" + "          "+ "v_x" + "           " + "g" +"             " +"f" + "                "+ "sin(angulo)" +  "    "+ "angulo"+"\n") # imprime vx, vy, g, angulo

for archivo in carpeta:
	#carga los datos
	datos=np.loadtxt(ruta+archivo,comments="#",unpack=False); #unpack transpone
	#guarda los datos
	tiempo=datos[:,0];
	pos_x=datos[:,1];
	pos_y=datos[:,2];
	#Polifit
	r_x=np.polyfit(tiempo,pos_x,1); # el primero es vx
	r_y=np.polyfit(tiempo,pos_y,2); #el primero es g/2 y el segundo es vy
	
	v_x = r_x[0]
	v_y = r_y[1]
	g   = r_y[0] * -2 
	
	f = 1.0 - (g/9.81)
	
	
	
	nombre = str(archivo).rsplit("_")
	angulo = str(nombre[3]).rpartition(".")	
	
	sinalg = np.sin( np.pi * float(angulo[0])/180.0 )
	
	imprimir = str(v_y) + " "+ str(v_x)+  " "+ str(g) +" " + str(f)+  " " + str(sinalg) +" " + angulo[0] +"\n"

	
		
	resultadosGXY.write(imprimir) # imprime vx, vy, g, angulo
	
resultadosGXY.close()


#carga los valores de v_x, v_y, g, el angulo


datos2=np.loadtxt(ruta2); #unpack transpone
#guarda los datos
v_yt=datos2[:,0];
v_xt=datos2[:,1];
gt=datos2[:,2];
angt=datos2[:,5]
sinang=datos2[:,4]
ft=datos2[:,3]

sinfit=np.polyfit(sinang,ft,1);

print sinfit
#ii=0;
#y=datos2[:,4];
#datos22=datos2[:,4];
#sinfitt=open(ruta4,"w");
#for aa in y:
#	print "datos2="+str(sinang[ii]) 
#	y[ii]=(datos22[ii]*sinfit[0])+sinfit[1];
#	print "datos2="+str(sinang[ii]) 
#	ii=ii+1;
	
#jj=0;
#for bb in sinang:
	#print "datos2="+str(sinang[jj]) 
	#print "y[ii]"+str(y[jj])
#	printt=str(y[jj]) + " " + str(sinang[jj]) + " " +str(angt[jj]) + "\n"
#	sinfitt.write(printt);
#	jj=jj+1;



#sinfitt.close()









arreglo = pyl.concatenate( ( [v_xt], [v_yt], [gt] ) )

cov = np.cov(arreglo)

eigenval = np.linalg.eigvals(cov)
eigenvec = np.linalg.eig(cov)[1]

vectores = open(ruta3,"w")	

vectores.write( str(eigenvec[0][0]) + " " + str(eigenvec[0][1]) + " " + str(eigenvec[0][2]) + "\n"  );
vectores.write( str(eigenvec[1][0]) + " " + str(eigenvec[1][1]) + " " + str(eigenvec[1][2]) + "\n"  );
vectores.write( str(eigenvec[2][0]) + " " + str(eigenvec[2][1]) + " " + str(eigenvec[2][2]) + "\n"  );


vectores.close()




