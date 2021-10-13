#include "treeNode_BST_StormEvents.h"
#include "Constants.h"
#include "defns.h"
#include<iostream>
#include "Helper_functions.h"

using namespace std;

treeNode_BST_StormEvents::treeNode_BST_StormEvents(storm_event event)
{
	this->event_index = event.event_index;
	this->event_id = event.event_id;
	this->State = event.state;
	this->Year = event.year;
	strcpy_s(this->month_name, event.month_name);
	strcpy_s(this->event_type, event.event_type);
	strcpy_s(this->cz_name, event.cz_name);
	this->cz_type, event.cz_type;
	this->leftNode = nullvalue;
	this->rightNode = nullvalue;
}

treeNode_BST_StormEvents * treeNode_BST_StormEvents::buildBinarySearchTree(treeNode_BST_StormEvents * t1, treeNode_BST_StormEvents * root)
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
				root->rightNode = buildBinarySearchTree(t1, root->rightNode);
			}
			else if (t1->State < root->State)
			{
				root->leftNode = buildBinarySearchTree(t1, root->leftNode);
			}
			
		}

		else if (t1->State == root->State)
		{
			if (t1->event_id > root->event_id)
			{
				root->rightNode = buildBinarySearchTree(t1, root->rightNode);
			}
			else if (t1->event_id < root->event_id)
			{
				root->leftNode = buildBinarySearchTree(t1, root->leftNode);
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
			DisplayCurrentNode(root);
			free(root);
		}
		else
		{
			DisplayCurrentNode(root);
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
				DisplayCurrentNode(root);
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
					DisplayCurrentNode(root);
				}

			}
			else if (lowRange < highRange)
			{
				int stringLengthtoCompare = lowRange.length();
				string subString = root->State.substr(0, stringLengthtoCompare);
				if (lowRange <= subString && subString <= highRange)
				{
					eventFound = true;
					DisplayCurrentNode(root);
				}
			}

		}
		
		inorderRangeQueryDisplay(root->rightNode,field_type,lowRange,highRange);

	}

	return eventFound;
}


void treeNode_BST_StormEvents::DisplayCurrentNode(treeNode_BST_StormEvents * root)
{
	cout << root->event_index << endl;
	cout << root->event_id << endl;
	cout << root->State << endl;
	cout << root->Year << endl;
	cout << root->month_name << endl;
	cout << root->event_type << endl;
	cout << root->cz_name << endl;
	cout << root->cz_type << endl;
}
