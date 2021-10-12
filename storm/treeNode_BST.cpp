#include "treeNode_BST.h"
#include "Constants.h"
#include<iostream>

using namespace std;

treeNode_BST::treeNode_BST(int a)
{
	this->nodeKey = a;
	this->leftNode = nullvalue;
	this->rightNode = nullvalue;
}

treeNode_BST * treeNode_BST::buildBinarySearchTree(treeNode_BST * t1, treeNode_BST * root)
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

void treeNode_BST::postOrderTraversalDelete(treeNode_BST * root, bool deleteTree)
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
			cout << root->nodeKey << endl;
			free(root);
		}
		else
		{
			cout << root->nodeKey << endl;
		}

	}
}

void treeNode_BST::inOrderTraversal(treeNode_BST * root)
{
	if (root == nullvalue)
	{
		return;
	}
	else
	{
		inOrderTraversal(root->leftNode);
		cout << root->nodeKey << endl;
		inOrderTraversal(root->rightNode);

	}
}



