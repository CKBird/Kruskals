//ECS 60 Homework #2
//Christopher Bird
//ID: 997337048
//Professor: Hao Chen

//Kruskal's Implementation along with Sorting Algorithm
//Main.cpp

#include <string>
#include <iostream>
#include "spantree.h"

using namespace std;

int main()
{
	spantree Spantree;
	Spantree.readInput();
	//Reads input and stores
	
	Spantree.sortInfo();
	//Sorts each regions roads by length and creates ordered arrays with least -> most length pointers
	
	Spantree.buildTree();
	//Builds each region using the lowest cost edges from each region
	
	Spantree.printOut();
	//Prints each region in the output desired by Chen
	
	return 0;
}