#ckbird; Bird, Christopher

spantree : main.o spantree.o
	g++ -o spantree main.o spantree.o -Wall -g -O3
main.o : main.cpp
	g++ -c main.cpp -Wall -g -o -O3 main.o
spantree.o : spantree.cpp spantree.h
	g++ -c spantree.cpp -Wall -g -o -O3 spantree.o