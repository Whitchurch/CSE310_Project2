#include "Helper_functions.h"
#include<math.h>
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

int Normalize_Scale(string cost)
{
	int units = 0;
	int numberOnly = 0;

	if (cost.empty()||cost == "0")
	{
		return 0;
	}
	else
	{
		//We can extract the last character to find out what we are multiplying against.
		//K implies we multiply with 1000.
		if (cost.back() == 'K')
		{
			units = 1000;
		}

		if (cost.length() == 1) //If only a single digit is passed without a unit of K
		{
			numberOnly = stod(cost);
			return numberOnly;
		}
		else
		{
			int length = cost.length();
			cost = cost.substr(0, length - 1);
			numberOnly = stod(cost)*units;
			return numberOnly;
		}

	}


}
