#include "heap_entry_Storm.h"
#include"defns.h"
#include<math.h>


heap_entry_Storm::heap_entry_Storm()
{
}

//Constructor, it follows the same struct pattern no changes.
heap_entry_Storm::heap_entry_Storm(storm_event event, int damage_amount,int event_index)
{
	this->event_id = event.event_id;
	this->event_index = event_index;
	this->damage_amount = damage_amount;
	this->year = event.year;
}

//	2. Max-Heap functions:
int heap_entry_Storm::returnLeft_Storm(int currentIndex)
{
	return((2 * currentIndex) + 1); // return (2i) location, we add + 1 since we start at 0 index.
}

int heap_entry_Storm::returnRight_Storm(int currentIndex)
{
	return((2 * currentIndex) + 2); //return (2i+1) location, we add + 1 since we start at 0 index.
}



int * heap_entry_Storm::maxHeapify_Storm(int inputArray[], int violatingNodeIndex, int heapSize)
{
	int *result;
	//Get the left and right index values, below the violating node.
	int leftIndex = heap_entry_Storm::returnLeft_Storm(violatingNodeIndex);
	int rightIndex = heap_entry_Storm::returnRight_Storm(violatingNodeIndex);
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
	result = maxHeapify_Storm(inputArray, largest, heapSize);

	return result;
}

int * heap_entry_Storm::buildMaxHeap_Storm(int inputArray[], int heapSize)
{
	//Start at the first node, which is not a max-heap, to begin the max-heapify.
	//Work your way from this point all the way to the root node, all the while
	//running max-heapify on every node visited.
	for (int violatingNodeIndex = floor((heapSize / 2) - 1); violatingNodeIndex >= 0; violatingNodeIndex--)
	{
		maxHeapify_Storm(inputArray, violatingNodeIndex, heapSize - 1);
	}

	return inputArray;
}



