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



hash_table_entry_inherited * hashTableStructure::findHashedValueInTable(hashTableStructure * hashTable, int valueToHash, int HashTableSize)
{
	int key = valueToHash%HashTableSize;
	while (hashTable[key].item != nullptr)
	{
		if (valueToHash == hashTable[key].item->event_id) //If the item is found, return the event.
		{
			return hashTable[key].item;
		}
		hashTable[key].item = hashTable[key].item->next;
	}
	
	return nullptr;
}



void hashTableStructure::displayHashSearchResult(hash_table_entry_inherited * eventFound, int valueToHash)
{
	if (eventFound != nullptr)
	{
		cout << eventFound->event_id << endl;
		cout << eventFound->year << endl;
		cout << eventFound->event_index << endl;

	}
	else
	{
		cout << "Storm event"<< valueToHash <<"not found" << endl;
	}
}
