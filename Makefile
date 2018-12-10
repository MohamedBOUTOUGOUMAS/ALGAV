
exe :  cle.o arbre_binaire.o Main.o 
	gcc -o exe Main.o
Main.o : Main.c arbre_binaire.o cle.o
	gcc -c Main.c 
arbre_binaire.o : arbre_binaire.c cle.o
	gcc -c arbre_binaire.c
cle.o : cle.c
	gcc -c cle.c


