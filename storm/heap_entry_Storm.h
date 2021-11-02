#pragma once
#include "defns.h"
using namespace std;

class heap_entry_Storm:heap_entry
{
public:
	int event_id;
	int damage_amount; // Amount of damage to property or crops
	int year; // Year of storm event
	int event_index; // For the given year, the index into array of storm events

public: heap_entry_Storm();
public: heap_entry_Storm(storm_event event, int damage_amount, int event_index);

	static int returnLeft_Storm(int currentIndex);
	static int returnRight_Storm(int currentIndex);

	static heap_entry_Storm* maxHeapify_Storm(heap_entry_Storm inputArray[], int violatingNodeIndex, int heapSize);
	static heap_entry_Storm* buildMaxHeap_Storm(heap_entry_Storm inputArray[], int heapSize);
	static heap_entry_Storm * ExtractDeleteMaxHeap_Storm(heap_entry_Storm maxHeap[], int count, int itemstodisplay);
};
