#include "Helper_functions.h"
#include<iostream>
#include<string>

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

double Normalize_Scale(string cost)
{
	int units = 0;

	//We can extract the last character to find out what we are multiplying against.
	//K implies we multiply with 1000.
	if (cost.back() == 'K')
	{
		units = 1000;
	}

	int length = cost.length();
	cost = cost.substr(0, length);
	cout << cost.substr(0, cost.length())<<endl;
	return 0;
}
