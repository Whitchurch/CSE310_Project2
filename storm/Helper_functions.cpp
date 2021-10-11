#include "Helper_functions.h"
#include<iostream>

using namespace std;
//Function to display first few entries of storm_event
void Display_StormEvents_Head(storm_event *events)
{
	for (int i = 0; i < 3; i++)
	{
		cout << events[i].event_id << endl;
		cout << events[i].event_type << endl;
	}
}
