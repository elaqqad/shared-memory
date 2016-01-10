import os

pid1 = os.fork() 
pid=pid1

if pid != 0: 
	pid2 = os.fork()
	pid=pid2+1 


if pid!=0 and pid!=1:
	print "je suis le pere   :",os.getpid(),"j'ai deux fils",pid1,"  ",pid2
elif pid== 0:
        print "je suis le fils 1 :",pid," ",os.getpid() 
else :
        print "je suis le fils 2 :",pid," ",os.getpid() 
