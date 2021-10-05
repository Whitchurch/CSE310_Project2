// storm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<math.h>
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
			return;
		}
		else
		{
			postOrderTraversalDelete(root->leftNode,deleteTree);
			postOrderTraversalDelete(root->rightNode,deleteTree);
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
};

//	2. Max-Heap functions:
 int returnLeft(int currentIndex)
{
	return((2 * currentIndex)+1); // return (2i) location, we add + 1 since we start at 0 index.
}

 int returnRight(int currentIndex)
{
	return((2 * currentIndex) + 2); //return (2i+1) location, we add + 1 since we start at 0 index.
}

int* maxHeapify(int inputArray[], int violatingNodeIndex, int heapSize)
{
	int *result;
	//Get the left and right index values, below the violating node.
	int leftIndex = returnLeft(violatingNodeIndex);
	int rightIndex = returnRight(violatingNodeIndex);
	int largest = 0; // setting the largest to 0, this needs to be run to make sure, setting to 0 does not break the code.
	int tempStorage = 0;

	//Decide if the leftIndex has the larger element.
	if (leftIndex <= heapSize && inputArray[leftIndex] > inputArray[violatingNodeIndex])
	{
		largest = leftIndex;
	}
	else
	{
		largest = violatingNodeIndex;
	}

	//Decide if the rightIndex has the larger element.
	if (rightIndex <= heapSize && inputArray[rightIndex] > inputArray[largest])
	{
		largest = rightIndex;
	}

	//Only make the swap, it either the left or right indexes are bigger than the violating node index.
	//This information has already been tracked in the larges variable:
	if (largest != violatingNodeIndex)
	{
		tempStorage = inputArray[violatingNodeIndex];
		inputArray[violatingNodeIndex] = inputArray[largest];
		inputArray[largest] = tempStorage;
	}
	else
	{
		return inputArray;
	}

	//Once the swap is done, we need to recurse down the heap, to ensure, lower sub-trees are still heaps.
	result = maxHeapify(inputArray, largest, heapSize);

	return result;
}

int* buildMaxHeap(int inputArray[], int heapSize)
{
	//Start at the first node, which is not a max-heap, to begin the max-heapify.
	//Work your way from this point all the way to the root node, all the while
	//running max-heapify on every node visited.
	for (int violatingNodeIndex = floor((heapSize / 2)-1); violatingNodeIndex >= 0; violatingNodeIndex--)
	{
		maxHeapify(inputArray, violatingNodeIndex, heapSize-1);
	}

	return inputArray;
}


//class heapNode
//{
//public:
//	int nodeKey;
//	heapNode *leftNode;
//	heapNode *rightNode;
//private:
//	static int returnLeft(int currentIndex)
//	{
//		return((2 * currentIndex) + 1); // return (2i) location, we add + 1 since we start at 0 index.
//	}
//
//	static int returnRight(int currentIndex)
//	{
//		return((2 * currentIndex) + 2); //return (2i+1) location, we add + 1 since we start at 0 index.
//	}
//
//public:
//	static heapNode* maxHeapify(int inputArray[], int violatingNodeIndex, int heapSize)
//	{
//		heapNode *result;
//		//Get the left and right index values, below the violating node.
//		int leftIndex = returnLeft(violatingNodeIndex);
//		int rightIndex = returnRight(violatingNodeIndex);
//		int largest = 0; // setting the largest to 0, this needs to be run to make sure, setting to 0 does not break the code.
//		int tempStorage = 0;
//
//		//Decide if the leftIndex has the larger element.
//		if (leftIndex <= heapSize && inputArray[leftIndex] > inputArray[violatingNodeIndex])
//		{
//			largest = leftIndex;
//		}
//		else
//		{
//			largest = violatingNodeIndex;
//		}
//
//		//Decide if the rightIndex has the larger element.
//		if (rightIndex <= heapSize && inputArray[rightIndex] > inputArray[largest])
//		{
//			largest = rightIndex;
//		}
//		
//		//Only make the swap, it either the left or right indexes are bigger than the violating node index.
//		//This information has already been tracked in the larges variable:
//		if (largest != violatingNodeIndex)
//		{
//			tempStorage = inputArray[violatingNodeIndex];
//			inputArray[violatingNodeIndex] = inputArray[largest];
//			inputArray[largest] = tempStorage;
//		}
//
//		//Once the swap is done, we need to recurse down the heap, to ensure, lower sub-trees are still heaps.
//		result = maxHeapify(inputArray, largest, heapSize);
//
//		return result;
//	}
//
//	static heapNode* buildMaxHeap(int inputArray[], int heapSize)
//	{
//		//Start at the first node, which is not a max-heap, to begin the max-heapify.
//		//Work your way from this point all the way to the root node, all the while
//		//running max-heapify on every node visited.
//		for (int violatingNodeIndex = heapSize / 2; violatingNodeIndex > 0; violatingNodeIndex--)
//		{
//			maxHeapify(inputArray, violatingNodeIndex, heapSize);
//		}
//
//		return inputArray;
//	}
//	
//};

int main()
{
	//int a[] = { 1,5,11,4,6,9,8};
	int a[] = { 1,2,3,4,5 };
	//int a[] = { 8,3,10,1,6,14,4,7,13 };
	//int a[] = { 4,12,10,18,24,22,15,31,44,35,66,90,70,50,25 };
	//int a[] = { 25,15,50,10,22,35,70,4,12,18,24,31,44,66,90 };
	treeNode *root = nullvalue; //set root of BST to null.
	
	//Building a BST
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		treeNode *newNode = new treeNode(a[i]);
		root = root->buildBinarySearchTree(newNode,root);
	}

	//Post-order Traversal of the tree,
	root->postOrderTraversalDelete(root,true);


	//MaxHeapify trial
	int a_1[] = { 1,2,3,4,5 };
	int arrayLength = sizeof(a_1) / sizeof(a_1[0]);
	int *result;
	result = buildMaxHeap(a_1, arrayLength );

	//View the max-heap:
	for (int i = 0; i < arrayLength; i++)
	{
		cout << a_1[i] << endl;
	}
	

}


