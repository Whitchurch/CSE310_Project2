#include "treeNode_BST_StormEvents.h"
#include "Constants.h"
#include "defns.h"
#include<iostream>

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
			cout << root->event_index << endl;
			cout << root->event_id << endl;
			cout << root->State << endl;
			cout << root->Year << endl;
			
			free(root);
		}
		else
		{
			cout << root->event_index << endl;
			cout << root->event_id << endl;
			cout << root->State << endl;
			cout << root->Year << endl;
		}

	}
}
