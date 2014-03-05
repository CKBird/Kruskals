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

road::road()
{
	
} //Constructor for road class

region::region()
{
	regionNum = -1;
	regionName = -1;
	numCities = 1;
} //Constructor for region class

spantree::spantree()
{

} //Constructor 

void spantree::readInput()
{
	int leftCity, rightCity, length;

	edgeList = new road[arrayLength]; //Ditto
	edgeCount = 0; //This used to be up on line 35
	
	cin >> numCity;
	cin >> numRoad;
	regionList = new region[numCity];
	
	arrayLength = numRoad;
	finalEdgeList = new road[arrayLength];
	
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
	
	for(int i = 0; i < numCity; i++)
	{
		region Region;
		Region.setRegion(i);
		Region.setNum(i);
		//GETS TO HERE JUST FINE
		regionList[i] = Region;
	} //Once this is done, there will be numCity Regions, each with their own name
	testInput();
} //Reads input and stores

//Test Input went Here

void spantree::testInput() 
{
	//cout << "Cities : " << numCity;
	//cout << "    Roads : " << numRoad << endl;
		for(unsigned i = 0; i < edgeCount; i++) 
		{
			//road Road = edgeList[i];
			//cout << Road.getLCity() << " " << Road.getRCity() << " " << Road.getLength() << endl;
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
	
	//This is where test sort was called
	
} //Sorts each region's road length and creates ordered array

void spantree::testSort()
{
	//cout << endl << "The ordered list of edges is: " << endl;
	for(unsigned i = 0; i < arrayLength; i++)
	{
		//cout << edgeList[i].getLength() << endl;
	}
	//cout << endl;
}
//This was where the declaration for test sort was

void spantree::buildTree()
{
	int position = 0;
	for(unsigned i = 0; i < edgeCount; i++) //Take edges one at a time from sorted list
	{
		if(findSet(edgeList[i].getLCity()) != findSet(edgeList[i].getRCity()))
		{
			finalEdgeList[position] = edgeList[i]; //Add edge to final list
			connect(edgeList[i].getLCity(), edgeList[i].getRCity()); //Put cities in same set
			position++;
		}
		else
		{
			arrayLength--;
		}
	}
	
} //Builds each region using the lowest cost edges from each region

int spantree::findSet(int city)
{
	int regionNum;
	for(int i = 0; i < getNumCity(); i++) //Increment through list of regions
	{
		if(regionList[i].getName() == city) //If regions original name is same as the city
		{
			regionNum = regionList[i].getNum(); //Get the current name of the region it's in
			break;
		}		
	}
	return regionNum;
} //Returns int number of region it is in

void spantree::connect(int LCity, int RCity)
{
	int regionNum;
	int changedRegion = -1;
	for(int i = 0; i < getNumCity(); i++)
	{
		if(regionList[i].getName() == LCity)
		{
			regionNum = regionList[i].getNum();
		}
		else if(regionList[i].getName() == RCity)
		{
			changedRegion = i;
		}
	}
	regionList[changedRegion].setNum(regionNum);
} //Connects the two input cities

void spantree::printOut()
{
	for(int i = 0; i < getNumCity(); i++) //Will increment through region list
	{
		for(unsigned j = 0; j < arrayLength; j++) //Increments through finalEdgeList
		{
			if(regionList[i].getName() == finalEdgeList[j].getRCity()) //If RCity matches region NAME
			{
				finalEdgeList[j].setRegion(regionList[i].getNum()); //Sets region of edge
			}
		}
	} //Once finished, each road in finalEdgeList will have a region value
	
	int regionOrder[arrayLength];
	int numRegions = 0;
	int tempRegion = -1;
	for(unsigned i = 0; i < arrayLength; i++)
	{
		if(finalEdgeList[i].getRegion() != tempRegion)
		{
			numRegions++;
			regionOrder[i] = finalEdgeList[i].getRegion();
			tempRegion = finalEdgeList[i].getRegion();
		}
	} //THIS LOOP SHOULD GET THE TOTAL NUMBER OF REGIONS
	
	for(unsigned i = 0; i < arrayLength; i++) //Increment through edge list
	{
		int temp = regionList[(finalEdgeList[i].getRCity())].getNum();
		regionList[temp].setNumCities(1);
	} //THIS SHOULD SET THE NUMBER OF CITIES IN EACH REGION CORRECTLY
	
	//SHELL SORT TO SORT REGION LIST
	unsigned gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1}; //Calculated 'fastest' gap length
	int temp;
	unsigned k;
	//SORT ALG HERE
	for(int i = 0; i < 8; i++) //For each gap in gaps
	{
		for(int j = gaps[i]; j < numRegions; j++)
		{
			temp = regionList[regionOrder[j]].getNumCities();
			for(k = j; ((k >= gaps[i]) && (regionList[regionOrder[k-gaps[i]]].getNumCities()) > temp); k -= gaps[i])
			{
				regionList[regionOrder[k]].setNumCities(regionList[regionOrder[k-gaps[i]]].getNumCities());
			}
			regionList[regionOrder[k]].setNumCities(temp);
		}
	}
	
	cout << "<?xml version=\"1.5\"?>" << endl;
	cout << "<country>" << endl;
	for(int i = 0; i < numRegions; i++)
	{
		cout << "<region>" << endl;
		for(unsigned j = 0; j < arrayLength; j++)
		{
			if(finalEdgeList[j].getRegion() == regionOrder[i])
			{
				if(finalEdgeList[j].getRCity() < finalEdgeList[j].getLCity())
				{
					cout << "<road>" << finalEdgeList[j].getRCity() << " " << finalEdgeList[j].getLCity() << " " << finalEdgeList[j].getLength() << "</road>" << endl;
				}
				else
				{
					cout << "<road>" << finalEdgeList[j].getLCity() << " " << finalEdgeList[j].getRCity() << " " << finalEdgeList[j].getLength() << "</road>" << endl;
				}
			}
		}
		cout << "</region>" << endl;
	}
	cout << "</country>" << endl;

} //Prints each region in the output desired by chen

