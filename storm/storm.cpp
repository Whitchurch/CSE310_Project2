#include <iostream>
#include<fstream>
#include<math.h>
#include<string>
#include<cstring>
#include "Constants.h"
#include "defns.h"
#include "treeNode_BST.h"
#include "treeNode_BST_StormEvents.h"
#include "Helper_functions.h"

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



	//Step 3: Read the details-YYYY.csv files based on the year passed in:
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
		annualStormArray[i].eventCount = readLineCount - 1;
		annualStormArray[i].events = events = new storm_event[readLineCount - 1]; // we subtract 1, since we don't need space for the column headings
		
		
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
				events[LineCount - 1].event_index = LineCount - 1;

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
			LineCount++;


		}

		fileInputStream.close();


	}
	//Step 4: Get the user input queries.

	
	//Step 5: Create the BST for storing the map, to the underlying events array.
	treeNode_BST_StormEvents *root = nullvalue; //Set root of BST to null


	for (int year = 0; year < noOfYears; year++) //Go one year at a time
	{
		
		for (int eventIndex = 0; eventIndex < annualStormArray[year].eventCount; eventIndex++) //Go through all the events, in the current year and insert them into the BST. 
		{
			treeNode_BST_StormEvents *newNode = new treeNode_BST_StormEvents(annualStormArray[year].events[eventIndex]); //We Pass by value the events.
			root = root->buildBinarySearchTree(newNode, root);
		}
	}



	//Post-order Traversal of the tree,
	//cout << "------------------------POST ORDER TRAVERSAL---------------------------------------------------" << endl;
	//root->postOrderTraversalDelete(root,true);
	//cout << "-------------------------END OF TRAVERSAL------------------------------------------------------" << endl;

	cout << "------------------------IN ORDER TRAVERSAL---------------------------------------------------" << endl;
	if (!root->inorderRangeQueryDisplay(root, "state", "A", "O"))
	{
			cout << "No storm events found for the given range" << endl;
	}
	cout << "-------------------------END OF TRAVERSAL------------------------------------------------------" << endl;

	//Remove the underlying events array, to free up the memory.:
	delete[] events;


	
}