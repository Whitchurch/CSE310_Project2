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

	hash_table_entry_inherited *nextnode = hashTable[key].item;
	while (nextnode != nullptr)
	{
		if (valueToHash == nextnode->event_id) //If the item is found, return the event.
		{
			return nextnode;
		}
		nextnode = nextnode->next;
	}
	
	return nullptr;
}



void hashTableStructure::displayHashSearchResult(hash_table_entry_inherited * eventFound, int valueToHash, annual_storms *annualStormArray, string yearParam)
{
	if (eventFound != nullptr)
	{

		//Output Template:
		//Event ID : 10096229
		//State : OKLAHOMA
		//Year : 1950
		//Month Name : May
		//Event Type : Tornado
		//County / Zone Type : C
		//County / Zone Name : PAYNE
		//Injuries Direct : 0
		//Injuries Indirect : 0
		//Deaths Direct : 0
		//Deaths Indirect : 0
		//Damage Property : $2500
		//Damage Crops : $0

		//	No fatalities

		int base_year = stoi(yearParam);
		int yearindex = eventFound->year%base_year;
		
		cout << "Event ID: "<<eventFound->event_id << endl;
		cout << "State: " << annualStormArray[yearindex].events[eventFound->event_index].state <<endl;
		cout << "Year: " << eventFound->year<< endl;
		cout << "Month Name: " << annualStormArray[yearindex].events[eventFound->event_index].month_name << endl;
		cout << "Event Type: " << annualStormArray[yearindex].events[eventFound->event_index].event_type << endl;
		cout << "County/Zone Type: " << annualStormArray[yearindex].events[eventFound->event_index].cz_type<< endl;
		cout << "County/Zone Name: " << annualStormArray[yearindex].events[eventFound->event_index].cz_name << endl;
		cout << "Injuries Direct: " << annualStormArray[yearindex].events[eventFound->event_index].injuries_direct<< endl;
		cout << "Injuries Indirect: " << annualStormArray[yearindex].events[eventFound->event_index].injuries_indirect << endl;
		cout << "Deaths Direct: " << annualStormArray[yearindex].events[eventFound->event_index].deaths_direct << endl;
		cout << "Deaths Indirect: " << annualStormArray[yearindex].events[eventFound->event_index].deaths_indirect << endl;
		cout << "Damage Property: " << "$"<<annualStormArray[yearindex].events[eventFound->event_index].damage_property << endl;
		cout << "Damage Crops: " << "$"<<annualStormArray[yearindex].events[eventFound->event_index].damage_crops <<"\n"<< endl;
		if (annualStormArray[yearindex].events[eventFound->event_index].f == nullptr)
		{
			cout << "\tNo fatalities" << endl;
		}
		else
		{
			fatality_event *nextnode = annualStormArray[yearindex].events[eventFound->event_index].f;
			while (nextnode!= nullptr)
			{
				cout << "\tFatality ID: " << nextnode->fatality_id<<endl;
				cout << "\tFatality Type: "<<nextnode->fatality_type << endl;
				cout << "\tFatality Date: " <<nextnode->fatality_date <<endl;
				cout << "\tFatality Age: " << nextnode->fatality_age<<endl;
				cout << "\tFatality Sex: " << nextnode->fatality_sex<<endl;
				cout << "\tFatality Location: " << nextnode->fatality_location<<endl;

				nextnode = nextnode->next;
			}
		}
		

	}
	else
	{
		cout << "Storm event "<< valueToHash <<" not found" << endl;
	}
}
