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
	//arrayLength = 10;
} //Constructor 

void spantree::readInput()
{
	edgeList = new road[arrayLength];
	edgeCount = 0;
	
	int leftCity, rightCity, length;
	
	cin >> numCity;
	cin >> numRoad;
	
	arrayLength = numRoad;
	
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

	//THIS IS NOW UNECCESSARY SINCE ARRAYLENGTH IS = TO NUMBER OF ROADS
	
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
	//SHELL SORT OR QUICK SORT ALGORITHM
	unsigned gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1}; //Calculated 'fastest' gap length
	int temp;
	unsigned k;
	
	for(unsigned i = 0; i < 8; i++)
	{
		for(unsigned j = gaps[i]; i < arrayLength; j+= 1)
		{
			if(arrayLength < j)
			{
				break;
			}

			temp = edgeList[j].getLength();
			
			for(k = j; (k >= gaps[i]) && (edgeList[k - gaps[i]].getLength()) > temp; k -= gaps[i])
			{
				edgeList[k].setLength(edgeList[k - gaps[i]].getLength());
			}
			edgeList[k].setLength(temp);
		}
	}
	testSort();
	
} //Sorts each region's road length and creates ordered array

void spantree::testSort()
{
	cout << endl << "The ordered list of edges is: " << endl;
	for(unsigned i = 0; i < arrayLength; i++)
	{
		cout << edgeList[i].getLength() << endl;
	}
}

void spantree::buildTree()
{
	unsigned i = 0;
	//While edge list is not empty && minimum cost forest is not yet found
	//Remove edge from Edge List
		//If it joins two separate trees, add, and combine trees
		//Otherwise discard

		/*Increment through list of edges
		add edges one at a time to final product
			make sure cities they are connecting are not already connected
			check to see if cities are already in region
				if not, make new region and insert edge
				otherwise, add to existing region
			Continue until all cities are connected in each region
				make sure to add non-determinism alg here*/
			
	while(i < arrayLength)
	{
		if(findSet(edgeList[i].getLCity()) != findSet(edgeList[i].getRCity()))
		{
			//findSet will check which region each node of the edge 
			//is in, if they are in the same one, it will not add
			//otherwise, it will add edge to tree, and combine each nodes region
		}
	}

	
} //Builds each region using the lowest cost edges from each region

XXX spantree::findSet(XXX)
{
	
}

void spantree::printOut()
{

} //Prints each region in the output desired by chen

road::road()
{

} //Constructor for road class