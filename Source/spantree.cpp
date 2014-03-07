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

//IT WAS HERE
	
	cin >> numCity;
	cin >> numRoad;
	regionList = new region[numCity];
	
	arrayLength = numRoad;
	finalEdgeList = new road[arrayLength];
	
		edgeList = new road[arrayLength];
	edgeCount = 0; 
	
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
} //Reads input and stores

//Test Input went Here

void spantree::testInput() 
{
	cout << "Cities : " << numCity;
	cout << "    Roads : " << numRoad << endl;
		for(unsigned i = 0; i < edgeCount; i++) 
		{
			road Road = edgeList[i];
			cout << Road.getLCity() << " " << Road.getRCity() << " " << Road.getLength() << endl;
		}
		
}

void spantree::resize()
{

	//THIS IS NOW UNECCESSARY SINCE ARRAYLENGTH IS = TO NUMBER OF ROADS
	
	/*road* newEdgeList = new road[arrayLength * 2];
	for(unsigned i = 0; i < arrayLength; i++)
	{
		newEdgeList[i] = edgeList[i];
	}
	
	delete edgeList;
	edgeList = newEdgeList;
	arrayLength *= 2;
*/}

void spantree::sortInfo()
{
	//SHELL SORT
	unsigned gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1}; //Calculated 'fastest' gap length
	road temp;
	unsigned k;
	
	/*cout << endl << "The UNordered list of edges is: " << endl;
	for(unsigned i = 0; i < arrayLength; i++)
	{
		cout << edgeList[i].getLength() << endl;
	}
	cout << endl;*/
	
	for(unsigned i = 0; i < 8; i++)
	{
		for(unsigned j = gaps[i]; j < arrayLength; j+= 1)
		{
			if(arrayLength < j)
			{
				break;
			}

			temp = edgeList[j];
			//cout << "This is the temp value: " << edgeList[j].getLength() << endl;;
			
			for(k = j; (k >= gaps[i]) && (edgeList[k - gaps[i]].getLength()) > temp.getLength(); k -= gaps[i])
			{
				//cout << "This is the value being stored: " << edgeList[k-gaps[i]].getLength() << endl;
				edgeList[k] = edgeList[k - gaps[i]];
			}
			edgeList[k] = temp;
		}
	}
	//testSort();
	//This is where test sort was called
	
} //Sorts each region's road length and creates ordered array

void spantree::testSort()
{
	cout << endl << "The ordered list of edges is: " << endl;
	for(unsigned i = 0; i < arrayLength; i++)
	{
		cout << edgeList[i].getLength() << endl;
	}
	cout << endl;
}
//This was where the declaration for test sort was

void spantree::buildTree()
{	
	int position = 0; //Position in finalEdgeList being edited
	for(unsigned i = 0; i < edgeCount; i++) //Take edges one at a time from sorted list
	{

		//cout << findSet(edgeList[i].getLCity()) << " --- " << findSet(edgeList[i].getRCity()) << endl;
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
	for(int i = 0; i < getNumCity(); i++) //Increment through regions
	{
		if(regionList[i].getName() == city) //Find city in region list
		{
			return regionList[i].getNum(); //return region it's in
		}
	}
	return 0;
} //Returns int number of region it is in

void spantree::connect(int LCity, int RCity)
{
	int regionNum;
	int tempRegion;
	for(int i = 0; i < getNumCity(); i++) //Increment through regions
	{
		if(regionList[i].getName() == LCity)
		{
			regionNum = regionList[i].getNum();
			break;
		}
	}
	//regionNum now has region of left city
	
	for(int j = 0; j < getNumCity(); j++)
	{
		if(regionList[j].getName() == RCity)
		{
			tempRegion = regionList[j].getNum();
			regionList[j].setNum(regionNum);
			break;
		}
	}
	//Both RCity and LCity now have same regionNum
	
	for(int k = 0; k < getNumCity(); k++)
	{
		if(regionList[k].getNum() == tempRegion)
		{
			regionList[k].setNum(regionNum);
		}
	}
	
} //Connects the two input cities

int spantree::min(int num1, int num2)
{
	if(num1 < num2)
	{
		return num1;
	}
	else if(num2 < num1)
	{
		return num2;
	}
	else if(num1 == num2)
	{
		return -1;
	}
	else
	{
		cout << "I should NEVER get here" << endl;
	}
	return -2;
}

int spantree::max(int num1, int num2)
{
	if(num1 < num2)
	{
		return num2;
	}
	else if(num2 < num1)
	{
		return num1;
	}
	else if(num1 == num2)
	{
		cout << "Found redundant edges." << endl;
		return -1;
	}
	return -2;
}

void spantree::printOut()
{
	for(int i = 0; i < getNumCity(); i++) //Will increment through region list
	{
		for(unsigned j = 0; j < arrayLength; j++) //Increments through finalEdgeList
		{
			if(regionList[i].getName() == finalEdgeList[j].getLCity()) //If RCity matches region NAME
			{
				finalEdgeList[j].setRegion(regionList[i].getNum()); //Sets region of edge
			}
		}
	} //Once finished, each road in finalEdgeList will have a region value THIS WORKS
	
	road temp1;
	for(unsigned i = 0; i < arrayLength; i++)
	{
		for(unsigned j = 0; j < arrayLength; j++)
		{
			if(i != j && (finalEdgeList[i].getLength() == finalEdgeList[j].getLength()) && (finalEdgeList[i].getRegion() == finalEdgeList[j].getRegion())) //If not checking same road, and length is the same
			{
				if(min(finalEdgeList[i].getRCity(), finalEdgeList[i].getLCity()) < min(finalEdgeList[j].getRCity(), finalEdgeList[j].getLCity()))
				{ //If smallest city in iRoad is smaller than smallest in jRoad
					if(i > j) //NOT sorted correctly
					{
						temp1 = finalEdgeList[i];
						finalEdgeList[i] = finalEdgeList[j];
						finalEdgeList[j] = temp1;
					}
				}
				else if(min(finalEdgeList[i].getRCity(), finalEdgeList[i].getLCity()) > min(finalEdgeList[j].getRCity(), finalEdgeList[j].getLCity()))
				{
					if(j > i)
					{
						temp1 = finalEdgeList[i];
						finalEdgeList[i] = finalEdgeList[j];
						finalEdgeList[j] = temp1;
					}
				}
				else if(min(finalEdgeList[i].getRCity(), finalEdgeList[i].getLCity()) == min(finalEdgeList[j].getRCity(), finalEdgeList[j].getLCity()))
				{
					if(max(finalEdgeList[i].getRCity(), finalEdgeList[i].getLCity()) < max(finalEdgeList[j].getRCity(), finalEdgeList[j].getLCity()))
					{
						if(i > j)
						{
							temp1 = finalEdgeList[i];
							finalEdgeList[i] = finalEdgeList[j];
							finalEdgeList[j] = temp1;
						}
					}
					else if(max(finalEdgeList[i].getRCity(), finalEdgeList[i].getLCity()) > max(finalEdgeList[j].getRCity(), finalEdgeList[j].getLCity()))
					{
						if(i < j)
						{
							temp1 = finalEdgeList[i];
							finalEdgeList[i] = finalEdgeList[j];
							finalEdgeList[j] = temp1;
						}
					}
				}
			}
		}
	} //SAME REGION SAME LENGTH, SORT BY SMALLEST CITY
	
	int regionOrder[arrayLength];
	for(unsigned i = 0; i < arrayLength; i++)
	{
		regionOrder[i] = -1;
	}
	int numRegions = 0;
	int check = 0;
	for(unsigned i = 0; i < arrayLength; i++) //Going through finalEdgeList again
	{
		for(unsigned j = 0; j < arrayLength; j++) //Increment through regionList
		{
			if(finalEdgeList[i].getRegion() == regionOrder[j])
			{
				check = 1;
			}
		}
		if(check == 0)
		{
			regionOrder[numRegions] = finalEdgeList[i].getRegion();
			numRegions++;
			//cout << "NumRegions: " << numRegions << endl;
		}
		else
		{
			check = 0;
		}
	} //Sets total number of regions WORKS CORRECTLY
	
	regionFinal = new region[numRegions];
	for(int i = 0; i < numRegions; i++) //Increment through numRegions
	{
		for(int j = 0; j < getNumCity(); j++) //For each city, set regionFinal
		{
			if(regionOrder[i] == regionList[j].getNum())
			{
				regionFinal[i] = regionList[j];
			}
		}
	}	//REGIONFINAL HAS POINTERS TO FINAL REGIONS
	
	for(unsigned i = 0; i < arrayLength; i++) //Increment through edge list
	{
		for(int j = 0; j < numRegions; j++)
		{
			if(finalEdgeList[i].getRegion() == regionFinal[j].getNum())
			{
				regionFinal[j].setNumCities(1);
				regionList[finalEdgeList[i].getRegion()].setNumCities(1);
			}
		}
	} //THIS SHOULD SET THE NUMBER OF CITIES IN EACH REGION CORRECTLY
	//IS WORKING CORRECTLY
	
	for(int i = 0; i < numCity; i++)
	{
		for(unsigned j = 0; j < arrayLength; j++)
		{
			if((regionList[i].getName() == finalEdgeList[j].getRCity()) || (regionList[i].getName() == finalEdgeList[j].getLCity()))
			{
				for(int k = 0; k < numRegions; k++)
				{
					if(regionOrder[k] == regionList[i].getName())
					{
						break;
					}
					regionList[i].setNumCities(-1);
				}
			}
			break;
		}
	}
	
	
	//SHELL SORT TO SORT REGION LIST
	unsigned gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1}; //Calculated 'fastest' gap length
	region temp;
	unsigned k;
	
	//SORT ALG HERE
	for(int i = 0; i < 8; i++) //For each gap in gaps
	{
		for(int j = gaps[i]; j < numRegions; j++) //getNumCity() was numRegions
		{
			temp = regionFinal[j]; //ENTIRE REGION POINTER TO BE CHECKED AGAINST
			for(k = j; k >= gaps[i] && regionFinal[k - gaps[i]].getNumCities() > temp.getNumCities(); k -= gaps[i])
			{ 
				regionFinal[k] = regionFinal[k - gaps[i]]; //PUTTING SMALLEST NUMBER OF CITIES INTO REGIONFINAL
			}
			regionFinal[k] = temp;
		}
	}
	
	int check1 = 0;
	int check2 = 0;
	int temp10, temp20;
	for(int i = 0; (i < numRegions); i++) //Incrementing through regionFinal
	{
		for(int j = 0; (j < (numRegions - i)); j++) //For each region, increment through the other regions
		{
			if(i != j && (regionFinal[i].getNumCities() == regionFinal[j].getNumCities())) //if two regions have same number of cities
			{
				for(unsigned k = 0; k < arrayLength; k++) //Increment through edge list and find first edge in that region
				{
					if((finalEdgeList[k].getRegion() == regionFinal[i].getNum()) && check1 != 1) //If edge matches region, store edge num
					{
						temp10 = k;
						check1 = 1;
					}
					else if((finalEdgeList[k].getRegion() == regionFinal[j].getNum()) && check2 != 1) //If edge matches region, store edge num
					{
						temp20 = k;
						check2 = 1;
					}
					else if((check1 == 1) && (check2 == 1))
					{
						if(min(finalEdgeList[temp10].getRCity(), finalEdgeList[temp10].getLCity()) < min(finalEdgeList[temp20].getRCity(), finalEdgeList[temp20].getLCity()))
						{
							if(i > j)
							{
								region Bread;
								Bread = regionFinal[i];
								regionFinal[i] = regionFinal[j];
								regionFinal[j] = Bread;
							}
						}
						else if(min(finalEdgeList[temp10].getRCity(), finalEdgeList[temp10].getLCity()) > min(finalEdgeList[temp20].getRCity(), finalEdgeList[temp20].getLCity()))
						{
							if(i < j)
							{
								region Bread;
								Bread = regionFinal[i];
								regionFinal[i] = regionFinal[j];
								regionFinal[j] = Bread;
							}
						}
						check1 = 0;
						check2 = 0;
						break;
					}
				}
			}
		}
	} //THIS FUCKING WORKS NOW BITCHES #SWAGGOMLYOLOMONEYSEEYANERDSXXX420FROAKWEED
	
	int skipCount = 0;
	int meepo = 0;
	for(int i = 0; i < numCity; i++)
	{
		for(int j = 0; j < numRegions; j++) //For each city, increment through final list of regions
		{
			if(regionOrder[j] == regionList[i].getNum())
			{
				meepo = 1; //If region num matches final region, release
			}
		}
		if(meepo != 1)
		{
			skipCount++;
		}
		meepo = 0;
	} //Accounting for empty regions
	
	cout << "<?xml version=\"1.5\"?>" << endl;
	cout << "<country>" << endl;
	
	for(int i = 0; i < skipCount; i++)
	{
		cout << "<region>" << endl << "</region>" << endl;
	}
	for(int i = 0; i < numRegions; i++) //Incrementing through regionFinal
	{
		cout << "<region>" << endl;
		for(unsigned j = 0; j < arrayLength; j++) //incrementing through finalEdgeList
		{
			if(finalEdgeList[j].getRegion() == regionFinal[i].getNum()) //If region of edge is same as regionFinal
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

