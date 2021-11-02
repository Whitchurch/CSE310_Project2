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

fatalityList::fatalityList(string * token)
{
	this->fatality_id = stoi(token[0]);
	this->event_id = stoi(token[1]);
	//strncpy(this->month_name, event.month_name, sizeof(this->month_name));
	//strncpy(this->event_type, event.event_type, sizeof(this->event_type));
	//strncpy(this->cz_name, event.cz_name, COUNTY_LEN - 1);
	//this->cz_name[34] = '\0';
	this->fatality_type = token[2][0];
	
	strncpy(this->fatality_date, token[3].c_str(), sizeof(this->fatality_date));
	this->fatality_date[DATE_LEN - 1] = '\0';
	if (!token[4].empty())
	{
		this->fatality_age = stoi(token[4]);
	}
	else
	{
		this->fatality_age = 0;
	}
	
	this->fatality_sex = token[5][0];

	strncpy(this->fatality_location, token[6].c_str(), sizeof(this->fatality_location));
	this->fatality_location[FAT_LOC - 1] = '\0';

	this->next = nullptr;
}
