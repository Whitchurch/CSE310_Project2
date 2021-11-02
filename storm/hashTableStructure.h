#include "hash_table_entry_inherited.h"
#include <string>
#include <iostream>
#pragma once

using namespace std;
class hashTableStructure
{

public:
	hash_table_entry_inherited* item = nullptr;
public:
	static hashTableStructure* insertHashTableNode(int key, hashTableStructure *hashTable, storm_event event, int itemindex);
	static hashTableStructure* clearChainsHashTableNode(int totalTableSize, hashTableStructure * hashTable);
	static hash_table_entry_inherited* findHashedValueInTable(hashTableStructure *hashTable, int valueToHash, int HashTableSize);
	static void displayHashSearchResult(hash_table_entry_inherited* eventFound, int valueToHash);

};

