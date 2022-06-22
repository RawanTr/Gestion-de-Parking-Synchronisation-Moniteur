simulation: utils.o main.o parking.o
	gcc -o simulation utils.o parking.o main.o -pthread

utils.o: utils.c
	gcc -o utils.o -c utils.c 

parking.o: parking.c
	gcc -o parking.o -c parking.c

main.o: main.c utils.h parking.h
	gcc -o main.o -c main.c 
	
