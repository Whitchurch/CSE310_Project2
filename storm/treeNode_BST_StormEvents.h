#pragma once
#include "defns.h"
#include<string>

using namespace std;
//Constant definition:
//const int nullvalue = 0;
class treeNode_BST_StormEvents
{
	//Keeping the members public for ease of access.
	//I may move these to private and implement a getter/setter in the future to make the code cleaner.
public:
	int event_id;
	string State;
	treeNode_BST_StormEvents *leftNode;
	treeNode_BST_StormEvents *rightNode;

public: treeNode_BST_StormEvents(storm_event event);

		static treeNode_BST_StormEvents* buildBinarySearchTree(treeNode_BST_StormEvents *t1, treeNode_BST_StormEvents *root);
		static void postOrderTraversalDelete(treeNode_BST_StormEvents *root, bool deleteTree);
};
