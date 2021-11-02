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
