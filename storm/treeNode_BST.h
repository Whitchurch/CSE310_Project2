#pragma once

class treeNode_BST
{
	//Keeping the members public for ease of access.
	//I may move these to private and implement a getter/setter in the future to make the code cleaner.
public:
	int nodeKey;
	treeNode_BST *leftNode;
	treeNode_BST *rightNode;

public: treeNode_BST(int a);

	static treeNode_BST* buildBinarySearchTree(treeNode_BST *t1, treeNode_BST *root);
	static void postOrderTraversalDelete(treeNode_BST *root, bool deleteTree);
};




