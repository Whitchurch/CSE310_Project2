#include "fatalityList.h"

//Constructor to initialize the object with default values
fatalityList::fatalityList()
{
	this->fatality_id = 0;
	this->event_id = 0;
	this->fatality_type = '\0';
	this->fatality_date[DATE_LEN] = '\0';
	this->fatality_age = 0;
	this->fatality_sex = '\0';
	this->fatality_location[FAT_LOC] = '\0';
	this->next = nullptr;
	
}
