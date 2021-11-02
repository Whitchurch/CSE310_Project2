#pragma once
#include "defns.h"
#include<string>

using namespace std;
//Constant definition:
//const int nullvalue = 0;
class treeNode_BST_StormEvents:bst
{
	//Keeping the members public for ease of access.
	//I may move these to private and implement a getter/setter in the future to make the code cleaner.
public:
	int event_index;
	int event_id;
	string State;
	int Year;
	char month_name[MONTH_LEN]; // Month of event
	char event_type[EVENT_LEN];
	char cz_type; // Where event happened, C, Z, or M
	char cz_name[COUNTY_LEN]; // Name of county/zone

	
	treeNode_BST_StormEvents *leftNode;
	treeNode_BST_StormEvents *rightNode;

public: treeNode_BST_StormEvents(storm_event event);

		static treeNode_BST_StormEvents* buildBinarySearchTree(treeNode_BST_StormEvents *t1, treeNode_BST_StormEvents *root, string treeType);
		static void postOrderTraversalDelete(treeNode_BST_StormEvents *root, bool deleteTree);
		static bool inorderRangeQueryDisplay(treeNode_BST_StormEvents *root, string field_type,string lowRange, string highRange);
		static void DisplayCurrentNode(treeNode_BST_StormEvents *root,string field_type);
};
