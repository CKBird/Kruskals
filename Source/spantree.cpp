//ECS 60 Homework #2
//Christopher Bird
//ID: 997337048
//Professor: Hao Chen

//Kruskal's Implementation along with Sorting Algorithm
//spantree.cpp

#include <iostream>
#include <string>
#include <iomanip>
#include "spantree.h"

using namespace std;

spantree::spantree()
{
	arrayLength = 10;
	//Nothing for now
} //Constructor 

void spantree::readInput()
{
	edgeList = new road[arrayLength];
	edgeCount = 0;
	
	int leftCity, rightCity, length;
	
	cin >> numCity;
	cin >> numRoad;
	
	while(!cin.eof())
	{
		cin >> leftCity >> rightCity >> length;
		
		road Road;
		Road.setLCity(leftCity);
		Road.setRCity(rightCity);
		Road.setLength(length);
		
		if(edgeCount == arrayLength)
		{
			resize();
		}
		
		edgeList[edgeCount] = Road;
		edgeCount++;			
	} //Once this loop ends, all roads are stored into edgeList array
} //Reads input and stores

void spantree::testInput() {

	cout << "Cities : " << numCity;
	cout << "    Roads : " << numRoad << endl;

	for(unsigned i = 0; i < edgeCount; i++) {
		road Road = edgeList[i];
		cout << Road.getLCity() << " " << Road.getRCity() << " " << Road.getLength() << endl;
	}
		
}

void spantree::resize()
{
	road* newEdgeList = new road[arrayLength * 2];
	for(unsigned i = 0; i < arrayLength; i++)
	{
		newEdgeList[i] = edgeList[i];
	}
	
	delete edgeList;
	edgeList = newEdgeList;
	arrayLength *= 2;
}

void spantree::sortInfo()
{

} //Sorts each region's road length and creates ordered array

void spantree::buildTree()
{

} //Builds each region using the lowest cost edges from each region

void spantree::printOut()
{

} //Prints each region in the output desired by chen

road::road()
{

} //Constructor for road class