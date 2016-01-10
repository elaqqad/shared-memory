#!/usr/bin/python
import os,sys,random

r1,w1= os.pipe() 
r2,w2= os.pipe()

##########################################################################################################
# Lancement des trois processus on utilise le variable pid pour distnguer les trois processus en effet   #
# pid =0 pour le fils 1                                                                                  #
# pid =1 pour le fils 2                                                                                  #
# pid =pid2+1 (!=0 et !=1) pour le processus pere                                                        #
##########################################################################################################
pid1 = os.fork() 
pid=pid1
if pid != 0: 
	pid2 = os.fork()
	pid=pid2+1 


###########################################################################################################
w1 = os.fdopen(w1, 'w')
r1 = os.fdopen(r1,'r')
w2 = os.fdopen(w2, 'w')
r2 = os.fdopen(r2,'r')


for i in range(10):
        t=random.choice(["+","-"])

	if pid!=0 and pid!=1:
        	w1.write(t)
	elif pid == 0:
        	lu = r1.read()
        	print "text lu par fils 1=", lu

	if pid!=0 and pid!=1:
        	w2.write(t)
	elif pid == 1:
        	lu = r2.read()
        	print "text lu par fils 2=" , lu  


if pid!=0 and pid!=1:
	w1.close()
	w2.close()
        r1.close()
	r2.close()
sys.exit(0)
        










