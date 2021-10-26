#pragma once
//	2. Max-Heap functions:
int returnLeft(int currentIndex);
int returnRight(int currentIndex);

int* maxHeapify(int inputArray[], int violatingNodeIndex, int heapSize);
int* buildMaxHeap(int inputArray[], int heapSize);

