#include "hash_table_entry_inherited.h"
#pragma once
class hashTableStructure
{

public:
	hash_table_entry_inherited* item = nullptr;
public:
	static hashTableStructure* insertHashTableNode(int key, hashTableStructure *hashTable, storm_event event, int itemindex);
	static hashTableStructure * clearChainsHashTableNode(int totalTableSize, hashTableStructure * hashTable);

};

