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

class region //Each vertex has it's own region class instance, information is stored here
{
public:
	region();
	void setRegion(unsigned region)	{ regionName = region; }
	void setNum(int newValue)		{ regionNum = newValue; }
	int getName()					{ return regionName; }
	int getNum()					{ return regionNum; }
	void setNumCities(int value)	{ numCities = numCities + value; }
	int getNumCities()				{ return numCities; }
	
private:
	int regionNum; //The final region it ends up in
	int regionName; //The name of the region that started the set
	int numCities;
};

class road
{
public:
	road();
	void setLCity(int LCity)		{ leftCity = LCity; }
	void setRCity(int RCity)		{ rightCity = RCity; }
	void setLength(int length)		{ roadLength = length; }
	int getLCity() 					{ return leftCity; }
	int getRCity()					{ return rightCity; }
	int getLength()					{ return roadLength; }
	void setRegion(int region)		{ currRegion = region; }
	int getRegion()					{ return currRegion; }

private:
	int roadLength;
	int leftCity;
	int rightCity;
	int currRegion;
};

class spantree
{
public:
	spantree();
	void readInput();		//Reads input and stores
	void resize();			//Resizes array to double length
	void sortInfo();		//Sorts each regions roads by length and creates ordered arrays with least -> most length pointers
	void buildTree();		//Builds each region using the lowest cost edges from each region
	int findSet(int city);	//Will return the region the road is in for comparison
	void connect(int LCity, int RCity); //Puts two cities together, fixing regions aswell
	int getNumCity()		{ return numCity; }
	void printOut();		//Prints each region in the output desired by Chen
	void testInput();		// delete this
	void testSort();		// delete this too
	int min(int num1, int num2);
	int max(int num1, int num2);
	
private: 
	int numCity;
	int numRoad;
	road* edgeList;
	unsigned arrayLength;
	unsigned edgeCount;
	road* finalEdgeList;
	region* regionList;
	region* regionFinal;
	int position;
};
#endif