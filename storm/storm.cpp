#include <iostream>
#include<fstream>
#include<math.h>
#include<string>
//#include<cstring>
#include "Constants.h"
#include "defns.h"
//#include "treeNode_BST.h"
#include "treeNode_BST_StormEvents.h"
#include"heap_entry_Storm.h"
#include "hash_table_entry_inherited.h"
//#include"heap_entry.h"
#include "linkedlist.h"
#include "Helper_functions.h"
#include "hashTableStructure.h"

using namespace std;

//Global variables
storm_event *events;
int LineCount = 0;



int main(int argc, char *argv[])
{

	int totalCommandLineArguments = argc;

	//Step 1: Read in the command line parameters
	string yearParam = argv[1]; // We assume the inputs are not going to have errors: AS per P2-ilestone definition
	int noOfYears = atoi(argv[2]); // We assume the inputs are not going to have errors: AS per P2-ilestone definition

	//Step 2: Create an array  of structure_annual storms:
	annual_storms *annualStormArray = new annual_storms[noOfYears];
	int *eventCount = new int[noOfYears];

//Step 3: Read the details-YYYY.csv files based on the year passed in: ////////////////////////////////////////////////////////////////////
	//Create a file  input stream object:

	
	for (int i = 0; i < noOfYears; i++)
	{
		int year = stoi(yearParam);
		year = year + i;
		string yearInput = to_string(year);

		ifstream fileInputStream;
		fileInputStream.open("details-" + yearInput + ".csv");
		bool ignoreFirstLine = true;
		int readLineCount = 0;

		//Get the total lines per file:
		while (fileInputStream.good())
		{
			string currentLineRead;
			getline(fileInputStream, currentLineRead);
			//Get the total lines in the file
			readLineCount++;
		}
		fileInputStream.close();

		annualStormArray[i].year = year;
		eventCount[i] = readLineCount - 1;
		annualStormArray[i].events = events = new storm_event[readLineCount - 1]; // we subtract 1, since we don't need space for the column headings

	}

	//--------------------------------Setup for the Hash Table ---------------------------------------//
	//Total eventCounts:
	int HashTableSize = 0;
	for (int i = 0; i < noOfYears; i++)
	{
		HashTableSize += eventCount[i];
	}

	//Allocate 3 times size to the nearest PRIME
	HashTableSize = 3 * HashTableSize;

	//Check and return the next biggest prime.
	HashTableSize = returnNearestBiggerPrime(HashTableSize);


	//Create a Hash Table of size equal to : Ceiling(3X(total years size))nearest prime!!
	hashTableStructure *hashTable = new hashTableStructure[HashTableSize];


	//-----------------------------Start reading the files and populating the Event Arrays, Hash Tables, Fatality linkedlist------//

	for (int i = 0; i < noOfYears; i++)
	{
		int year = stoi(yearParam);
		year = year + i;
		string yearInput = to_string(year);
		ifstream fileInputStream;
		fileInputStream.open("details-" + yearInput + ".csv");
		
		string token[13];
		LineCount = 0;

		//Now read the file again:
		while (fileInputStream.good())
		{
			string currentLineRead;
			getline(fileInputStream, currentLineRead);



			if (LineCount > 0) //This condition skips the first line, with the headings and stars recording from the second line
			{
				int i_token = 0;
				string delimiter = ",";

				while (i_token < 13)
				{

					token[i_token] = currentLineRead.substr(0, currentLineRead.find(delimiter));
					currentLineRead = currentLineRead.erase(0, currentLineRead.find(delimiter) + delimiter.length());
					i_token++;
				}

				//Enter the event_index:
				//events[LineCount - 1].event_index = LineCount - 1;

				//Enter the extracted tokens into their respective fields:
				events[LineCount - 1].event_id = stoi(token[0]);
				strcpy_s(events[LineCount - 1].state, token[1].c_str());
				//events[LineCount - 1].state = token[1];

				events[LineCount - 1].year = stoi(token[2]);
				strcpy_s(events[LineCount - 1].month_name, token[3].c_str());
				//events[LineCount - 1].month_name = token[3];

				strcpy_s(events[LineCount - 1].event_type, token[4].c_str());
				//events[LineCount - 1].event_type = token[4];

				events[LineCount - 1].cz_type = token[5][0];
				//events[LineCount - 1].cz_type = token[5];

				strcpy_s(events[LineCount - 1].cz_name, token[6].c_str());
				//events[LineCount - 1].cz_name = token[6];

				events[LineCount - 1].injuries_direct = stoi(token[7]);
				events[LineCount - 1].injuries_indirect = stoi(token[8]);
				events[LineCount - 1].deaths_direct = stoi(token[9]);
				events[LineCount - 1].deaths_indirect = stoi(token[10]);
				events[LineCount - 1].damage_property = Normalize_Scale(token[11]);
				events[LineCount - 1].damage_crops = Normalize_Scale(token[12]);

			}

			if (LineCount > 0)
			{
				//Applying Hashing to create a record inside the HashTable:
				int key = events[LineCount - 1].event_id%HashTableSize;

				//Use Key to hash into the table:
				hashTable = hashTable->insertHashTableNode(key,hashTable,events[LineCount-1], (LineCount - 1));
			}
			
			
			LineCount++;


		}

		fileInputStream.close();


	}
	string inputQueries;
	bool stringFirstLine = false;
	int noOfQueries = 0; //Read total query number

//Step 4: Read the Fatalities file, and enter the fatalities into their respective events:



//Step 4: Get the user input queries: ////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (getline(cin, inputQueries))
	{
		
		if (stringFirstLine == false)
		{
			noOfQueries = stoi(inputQueries);
			stringFirstLine = true; // Set to true to begin processing incoming queries
			
			//OUTPUT LINE 1:
			std::cout << noOfQueries<<endl;
		}
		else if (stringFirstLine == true)  //Check gating bool, before allowing query processing
		{
	
				int query_token_index = 0;
				string query_delimiter = " ";
				string query_token[5];

				//Read in ant tokenize.
				while (query_token_index < 5)
				{

					query_token[query_token_index] = inputQueries.substr(0, inputQueries.find(query_delimiter));

					if (query_token_index == 3 || query_token_index == 4)
					{
						if (query_token[0] == "range")
						{
						//Remove the slashes in the 4th and 5th tokens,from the beginning and the end.
						//Hard coding not interested in generalizing at the moment.
					
						query_token[query_token_index] = query_token[query_token_index].erase(0, 1);
						query_token[query_token_index] = query_token[query_token_index].erase(query_token[query_token_index].length() - 1, 1);
						}

					}

					inputQueries = inputQueries.erase(0, inputQueries.find(query_delimiter) + query_delimiter.length());
					query_token_index++;
				}

				//OUTPUT LINE 2:
				cout << "\n"<<"Query:" + query_token[0] + " " + query_token[1] + " " + query_token[2] +" "+"\"" + query_token[3] + "\""+" "+"\"" +query_token[4]+"\""+"\n"<<endl;



//Step 5: Construct the Data Structure based on the query passed in: //////////////////////////////////////////////////////////////////////
				//Data Structures are: Range == BST

				if (query_token[0] == "range")
				{
					//Step 5: Create the BST for storing the map, to the underlying events array.
					treeNode_BST_StormEvents *root = nullvalue; //Set root of BST to null


					//Step 6: Construct BST either for all years or just for given year.
					if (query_token[1] == "all")
					{
						for (int year = 0; year < noOfYears; year++) //Go one year at a time
						{

							for (int eventIndex = 0; eventIndex < eventCount[year]; eventIndex++) //Go through all the events, in the current year and insert them into the BST. 
							{
								treeNode_BST_StormEvents *newNode = new treeNode_BST_StormEvents(annualStormArray[year].events[eventIndex]); //We Pass by value the events.
								//Step 7: Decide the BST tree construction, based on the field_name passed in: either month_name or state
								if (query_token[2] == "month_name")
								{
									root = root->buildBinarySearchTree(newNode, root,query_token[2]);
								}
								else
								{
									root = root->buildBinarySearchTree(newNode, root,query_token[2]);
								}
								
							}
						}
					}
					else if (query_token[1] != "all")
					{
						int year = stoi(query_token[1]); //Get the year.
						int baseYear = stoi(yearParam);
						year = year % baseYear;

							for (int eventIndex = 0; eventIndex < eventCount[year]; eventIndex++) //Go through all the events, in the current year and insert them into the BST. 
							{
								treeNode_BST_StormEvents *newNode = new treeNode_BST_StormEvents(annualStormArray[year].events[eventIndex]); //We Pass by value the events.
								//Step 7: Decide the BST tree construction, based on the field_name passed in: either month_name or state
								if (query_token[2] == "month_name")
								{
									root = root->buildBinarySearchTree(newNode, root,query_token[2]);
								}
								else
								{
									root = root->buildBinarySearchTree(newNode, root,query_token[2]);
								}
							}
						
					}


					//Step 6: Do a in-order traversal to print out the contents of the BST for the current query: ////////////////////////////////////////////
					if (!root->inorderRangeQueryDisplay(root, query_token[2], query_token[3], query_token[4]))
					{
						cout << "No storm events found for the given range" << endl;
					}

					cout << endl;

					//Step 7: Do a post-order traversal to destroy/obliterate the BST for the current query: ////////////////////////////////////////////////
					root->postOrderTraversalDelete(root, true);
				}
				else if (query_token[0] == "find")
				{
					//Step 5: Create the heap for storing the map, to the underlying events array.
					heap_entry_Storm *maxHeap = nullvalue;

					//Step 7: Check if we are creating a max/min heap.
					if (query_token[1] == "max")
					{
						if (query_token[2] == "fatality")
						{
							if (query_token[3] == "all")
							{
							}
							else if (query_token[3] != "all")
							{
								cout << "Linked List implemention" << endl;
								linkedlist *root = nullptr;
								linkedlist *node = new linkedlist(2);
								root = linkedlist::InsertNode(node, root);
								linkedlist *node1 = new linkedlist(4);
								root = linkedlist::InsertNode(node1, root);

								linkedlist *next = root;
								while (next != nullptr)
								{
									
									cout << next->value << endl;
									next = next->next;
								}

								//Delete the linkedlist items
							    root = linkedlist::clearList(root);

							}
						}

						//Step 8a: Check if the heap is for all years
						else if (query_token[2] == "all")
						{
							int count = 0;

							for (int year = 0; year < noOfYears; year++) //Go one year at a time
							{
									count += eventCount[year];
							}

							maxHeap = new heap_entry_Storm[count];

							for (int year = 0; year < noOfYears; year++) //Go one year at a time
							{
								for (int eventIndex = 0; eventIndex < eventCount[year]; eventIndex++) //Go through all the events, in the current year and insert them into the BST. 
								{
									//Step 9: just create a huge array of type struct, either of damage_property or damage_crop.
									if (query_token[3] == "damage_property")
									{
										maxHeap[eventIndex].event_id = annualStormArray[year].events[eventIndex].event_id;
										maxHeap[eventIndex].damage_amount = annualStormArray[year].events[eventIndex].damage_property;
										maxHeap[eventIndex].year = annualStormArray[year].events[eventIndex].year;
										maxHeap[eventIndex].event_index = eventIndex;
										//heap_entry_Storm *newNode = new heap_entry_Storm(annualStormArray[year].events[eventIndex], annualStormArray[year].events[eventIndex].damage_property,eventIndex); //We Pass by value the events.
										//root = root->buildBinarySearchTree(newNode, root, query_token[2]);
									}
									else
									{
										maxHeap[eventIndex].event_id = annualStormArray[year].events[eventIndex].event_id;
										maxHeap[eventIndex].damage_amount = annualStormArray[year].events[eventIndex].damage_crops;
										maxHeap[eventIndex].year = annualStormArray[year].events[eventIndex].year;
										maxHeap[eventIndex].event_index = eventIndex;
										//heap_entry_Storm *newNode = new heap_entry_Storm(annualStormArray[year].events[eventIndex], annualStormArray[year].events[eventIndex].damage_crops, eventIndex); //We Pass by value the events.
										//root = root->buildBinarySearchTree(newNode, root, query_token[2]);
									}
								}
							}

							//Step 10: Build a Max- heap from the generic array:
							maxHeap = heap_entry_Storm::buildMaxHeap_Storm(maxHeap, count);

							//Step 11: Perform Extract- Delete Operation
							maxHeap = heap_entry_Storm::ExtractDeleteMaxHeap_Storm(maxHeap, count, stoi(query_token[4]));

							//Step 12: Delete and free the entire max-heap structure:
							//delete Last element:
							delete[] maxHeap;

							
						}
						else if (query_token[2] != "all")
						{
							int year = stoi(query_token[2]); //Get the year.
							year = year % year;

							int count = eventCount[year];
							maxHeap = new heap_entry_Storm[count];

							for (int eventIndex = 0; eventIndex < eventCount[year]; eventIndex++) //Go through all the events, in the current year and insert them into the BST. 
							{
								
								//Step 9: just create a huge array of type struct, either of damage_property or damage_crop.
								if (query_token[3] == "damage_property")
								{
									maxHeap[eventIndex].event_id = annualStormArray[year].events[eventIndex].event_id;
									maxHeap[eventIndex].damage_amount = annualStormArray[year].events[eventIndex].damage_property;
									maxHeap[eventIndex].year = annualStormArray[year].events[eventIndex].year;
									maxHeap[eventIndex].event_index = eventIndex;
									//heap_entry_Storm *newNode = new heap_entry_Storm(annualStormArray[year].events[eventIndex], annualStormArray[year].events[eventIndex].damage_property,eventIndex); //We Pass by value the events.
									//root = root->buildBinarySearchTree(newNode, root, query_token[2]);
								}
								else
								{
									maxHeap[eventIndex].event_id = annualStormArray[year].events[eventIndex].event_id;
									maxHeap[eventIndex].damage_amount = annualStormArray[year].events[eventIndex].damage_crops;
									maxHeap[eventIndex].year = annualStormArray[year].events[eventIndex].year;
									maxHeap[eventIndex].event_index = eventIndex;
									//heap_entry_Storm *newNode = new heap_entry_Storm(annualStormArray[year].events[eventIndex], annualStormArray[year].events[eventIndex].damage_crops, eventIndex); //We Pass by value the events.
									//root = root->buildBinarySearchTree(newNode, root, query_token[2]);
								}
							}

							//Step 10: Build a Max- heap from the generic array:
							maxHeap = heap_entry_Storm::buildMaxHeap_Storm(maxHeap, count);
							
							//Step 11: Perform Extract- Delete Operation
							maxHeap = heap_entry_Storm::ExtractDeleteMaxHeap_Storm(maxHeap, count, stoi(query_token[4]));

							//Step 12: Delete and free the entire max-heap structure:
							//delete Last element:
							delete[] maxHeap;


						}


					}

	
				}

			
		}
	


	}

//Step 8: Remove the chains from the Hash Table:
	hashTable = hashTable->clearChainsHashTableNode(HashTableSize, hashTable);
	delete[] hashTable;

//Step 8: Remove the underlying events array, to free up the memory :  ///////////////////////////////////////////////////////////////////
	delete[] events;

//Step 9: Add that extra blank line to match the expected output.
	cout << "\n\n";


	
}