#include "defns.h"

#pragma once
class hash_table_entry_inherited
{
public:

	int event_id; // Event id -- key used to hash on
	int year; // Year of storm event
	int event_index; // For the given year, the index into array of storm events
	hash_table_entry_inherited *next; // Pointer to next entry in case of collisions

	hash_table_entry_inherited()
	{

	}

	hash_table_entry_inherited(storm_event event, int itemindex)
	{
		this->event_id = event.event_id;
		this->event_index = itemindex;
		this->next = nullptr;
		this->year = event.year;
	}

};

