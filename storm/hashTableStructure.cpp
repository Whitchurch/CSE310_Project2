#include "hashTableStructure.h"

hashTableStructure * hashTableStructure::insertHashTableNode(int key, hashTableStructure * hashTable, storm_event event, int itemindex)
{
	if (hashTable[key].item == nullptr)
	{
		//Create a new hash table entry:
		hashTable[key].item = new hash_table_entry_inherited(event, itemindex);


	}
	else
	{
		hash_table_entry_inherited* oldItemAddress;
		oldItemAddress = hashTable[key].item;

		//Insert new item at the beginning of the chain:
		hashTable[key].item = new hash_table_entry_inherited(event, itemindex);
		hashTable[key].item->next = oldItemAddress;

	}

	return hashTable;
}

hashTableStructure * hashTableStructure::clearChainsHashTableNode(int totalTableSize, hashTableStructure * hashTable)
{
	for (int i = 0; i < totalTableSize; i++)
	{
		hash_table_entry_inherited *nextnode;
		while (hashTable[i].item != nullptr)
		{
			nextnode = hashTable[i].item->next;
			delete hashTable[i].item;
			hashTable[i].item = nextnode;
		}
	}

	return hashTable;
}
