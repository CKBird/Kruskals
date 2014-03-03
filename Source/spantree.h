//ECS 60 Homework #2
//Christopher Bird
//ID: 997337048
//Professor: Hao Chen

//Kruskal's Implementation along with Sorting Algorithm
//spantree.h

#ifndef SPANTREE_H
#define SPANTREE_H

#include<fstream>
#include<string>

using namespace std;

class road
{
public:
	road();
	void setLCity(int LCity)	{ leftCity = LCity; }
	void setRCity(int RCity)	{ rightCity = RCity; }
	void setLength(int length)	{ roadLength = length; }
	int getLCity() 				{ return leftCity; }
	int getRCity()				{ return rightCity; }
	int getLength()				{ return roadLength; }
	
private:
	int roadLength;
	int leftCity;
	int rightCity;
};

class spantree
{
public:
	spantree();
	void readInput();	//Reads input and stores
	void resize();		//Resizes array to double length
	void sortInfo();	//Sorts each regions roads by length and creates ordered arrays with least -> most length pointers
	void buildTree();	//Builds each region using the lowest cost edges from each region, THIS IS WHERE REGION CREATION WILL HAPPEN
	void printOut();	//Prints each region in the output desired by Chen
	void testInput(); // delete this
	
private:
	int numCity;
	int numRoad;
	road* edgeList;
	unsigned arrayLength;
	unsigned edgeCount;
};
#endif