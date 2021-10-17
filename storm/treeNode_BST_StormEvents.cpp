#include "treeNode_BST_StormEvents.h"
#include "Constants.h"
#include "defns.h"
#include<iostream>
#include "Helper_functions.h"

using namespace std;

treeNode_BST_StormEvents::treeNode_BST_StormEvents(storm_event event)
{
	//this->event_index = event.event_index;
	this->event_id = event.event_id;
	this->State = event.state;
	this->Year = event.year;
	strcpy_s(this->month_name, event.month_name);
	strcpy_s(this->event_type, event.event_type);
	strcpy_s(this->cz_name, event.cz_name);
	this->cz_type = event.cz_type;
	this->leftNode = nullvalue;
	this->rightNode = nullvalue;
}

treeNode_BST_StormEvents * treeNode_BST_StormEvents::buildBinarySearchTree(treeNode_BST_StormEvents * t1, treeNode_BST_StormEvents * root, string treeType)
{
	// I could have built the BST into 2 separate functions, one for State, one fot Month.  
	//But for this small scale project,  I decided to put them both in the same Build function.
	//Having 2 different functions is the better design approach, as it offers encapuslation, each function does it's own thing.
	//I am aware of that, bit for this small project I decided to put both types of tree construction in the same function.
	//If more types of queries come in the future, I will encapsulate each part of the if else logic in it's own function and call it 
	//form here.

	if (treeType == "state") //Build BST Using State as the first Key to check, before breaking equalizer with even_id
	{
		if (root == nullvalue)
		{
			root = t1;
		}
		else
		{
			if (t1->State != root->State)
			{
				if (t1->State > root->State)
				{
					root->rightNode = buildBinarySearchTree(t1, root->rightNode, treeType);
				}
				else if (t1->State < root->State)
				{
					root->leftNode = buildBinarySearchTree(t1, root->leftNode, treeType);
				}

			}

			else if (t1->State == root->State)
			{
				if (t1->event_id > root->event_id)
				{
					root->rightNode = buildBinarySearchTree(t1, root->rightNode, treeType);
				}
				else if (t1->event_id < root->event_id)
				{
					root->leftNode = buildBinarySearchTree(t1, root->leftNode, treeType);
				}
			}
		}
	}
	else if (treeType == "month_name")
	{
		if (root == nullvalue)
		{
			root = t1;
		}
		else
		{
			//Downgraded to make the months lexographical.
			int newEntry = changeMonthToValue(t1->month_name);
			int oldEntry = changeMonthToValue(root->month_name);

			if (newEntry != oldEntry)
			{
				if (newEntry > oldEntry)
				{
					root->rightNode = buildBinarySearchTree(t1, root->rightNode, treeType);
				}
				else if (newEntry < oldEntry)
				{
					root->leftNode = buildBinarySearchTree(t1, root->leftNode, treeType);
				}

			}

			else if (newEntry == oldEntry)
			{
				if (t1->event_id > root->event_id)
				{
					root->rightNode = buildBinarySearchTree(t1, root->rightNode, treeType);
				}
				else if (t1->event_id < root->event_id)
				{
					root->leftNode = buildBinarySearchTree(t1, root->leftNode, treeType);
				}
			}
		}
	}


	return root;
}

void treeNode_BST_StormEvents::postOrderTraversalDelete(treeNode_BST_StormEvents * root, bool deleteTree)
{

	if (root == nullvalue)
	{
		return;
	}
	else
	{
		postOrderTraversalDelete(root->leftNode, deleteTree);
		postOrderTraversalDelete(root->rightNode, deleteTree);
		if (deleteTree == true)
		{
			//DisplayCurrentNode(root);
			free(root);
		}
		else
		{
			//DisplayCurrentNode(root);
		}

	}
}

bool treeNode_BST_StormEvents::inorderRangeQueryDisplay(treeNode_BST_StormEvents * root, string field_type,string lowRange, string highRange)
{
	static bool eventFound = false; // Initially starts out being set to false;
	
	if (root == nullvalue)
	{
		return false;
	}
	else
	{
		inorderRangeQueryDisplay(root->leftNode,field_type,lowRange,highRange);
		//Show only items that fall between the low and high.
		if (field_type == "month_name")
		{
			if (checkMonth(root->month_name,lowRange,highRange)!=0)
			{
				eventFound = true;
				DisplayCurrentNode(root,field_type);
			}

		}
		else if(field_type == "state")
		{
			if (lowRange == highRange) //We check if the Range covers only one State
			{
				int stringLengthtoCompare = lowRange.length();
				string subString = root->State.substr(0, stringLengthtoCompare);

				if (subString == lowRange)
				{
					eventFound = true;
					DisplayCurrentNode(root,field_type);
				}

			}
			else if (lowRange < highRange)
			{
				int stringLengthtoCompare = lowRange.length();
				string subString = root->State.substr(0, stringLengthtoCompare);
				if (lowRange <= subString && subString <= highRange)
				{
					eventFound = true;
					DisplayCurrentNode(root,field_type);
				}
			}

		}
		
		inorderRangeQueryDisplay(root->rightNode,field_type,lowRange,highRange);

	}

	return eventFound;
}


void treeNode_BST_StormEvents::DisplayCurrentNode(treeNode_BST_StormEvents * root, string field_type)
{
	if (field_type == "month_name")
	{
		//Sample Output:
		//month_name: July
		//event_id : 9983034
		//year : 1952
		//event_type : Tornado
		//cz_type : C
		//cz_name : MILLER
		
		cout << "\n";
		cout << "        Month Name: "<<root->month_name << endl;
		cout << "        Event ID: "<<root->event_id << endl;
		cout << "        Year: "<<root->Year << endl;
		cout << "        Event Type: "<<root->event_type << endl;
		cout << "        County/Zone Type: "<<root->cz_type << endl;
		cout << "        County/Zone Name: "<<root->cz_name << endl;
		
	}

	if (field_type == "state")
	{
		//Sample Output:
		//state: ALABAMA
		//event_id : 9979429
		//year : 1952
		//event_type : Tornado
		//cz_type : C
		//cz_name : TALLAPOOSA

		cout << "\n";
		cout << "        State: "<<root->State << endl;
		cout << "        Event ID: " << root->event_id << endl;
		cout << "        Year: " << root->Year << endl;
		cout << "        Event Type: " << root->event_type << endl;
		cout << "        County/Zone Type: " << root->cz_type << endl;
		cout << "        County/Zone Name: " << root->cz_name << endl;
	}

}
