// storm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

//Constant definition:
const int nullvalue = 0;

//Class definitions:
//	1. Binary Search Tree
class treeNode
{
//Keeping the members public for ease of access.
//I may move these to private and implement a getter/setter in the future to make the code cleaner.
public: 
	int nodeKey;
	treeNode *leftNode;
	treeNode *rightNode;

public: treeNode(int a)
	{
		this->nodeKey = a;
		this->leftNode = nullvalue;
		this->rightNode = nullvalue;
	}

	//Common shared by all the treeNode objects
	static treeNode* buildBinarySearchTree(treeNode *t1, treeNode *root)
	{
		if (root == nullvalue)
		{
			root = t1;
		}
		else
		{
			if (t1->nodeKey > root->nodeKey)
			{
				root->rightNode = buildBinarySearchTree(t1, root->rightNode);
			}
			else if (t1->nodeKey < root->nodeKey)
			{
				root->leftNode = buildBinarySearchTree(t1, root->leftNode);
			}
			else if (t1->nodeKey == root->nodeKey)
			{
				root->leftNode = buildBinarySearchTree(t1, root->leftNode);
			}
		}

		return root;
	}

	static void postOrderTraversalDelete(treeNode *root,bool deleteTree) //Can also be used to delete the contents of the tree and free up the memory
	{
		if (root == nullvalue)
		{
			//cout << root->nodeKey << endl;
			return;
		}
		else
		{
			postOrderTraversalDelete(root->leftNode,deleteTree);
			postOrderTraversalDelete(root->rightNode,deleteTree);
			if (deleteTree == true)
			{
				//cout << root->nodeKey << endl;
				free(root);
			}
			else
			{
				cout << root->nodeKey << endl;
			}
			
		}
	}
};

//	2. Max-Heap:

int main()
{
	//int a[] = { 1,5,11,4,6,9,8};
	//int a[] = { 1,2,3,4,5 };
	//int a[] = { 8,3,10,1,6,14,4,7,13 };
	//int a[] = { 4,12,10,18,24,22,15,31,44,35,66,90,70,50,25 };
	int a[] = { 25,15,50,10,22,35,70,4,12,18,24,31,44,66,90 };
	treeNode *root = nullvalue; //set root of BST to null.
	
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		treeNode *newNode = new treeNode(a[i]);
		root = root->buildBinarySearchTree(newNode,root);
	}

	root->postOrderTraversal(root,true);


}


