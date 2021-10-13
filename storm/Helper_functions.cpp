#include "Helper_functions.h"
#include<math.h>
#include<iostream>
#include<string>
#include "Constants.h"

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

bool checkMonth(string month_name)
{
	//Spreading it out month-wise for ease of reading.
	if (month_name == January || month_name == Jan)
	{
		return true;
	}
	else if (month_name == February || month_name == Feb)
	{
		return true;
	}
	else if (month_name == March || month_name == Mar)
	{
		return true;
	}
	else if (month_name == April || month_name == Apr)
	{
		return true;
	}
	else if (month_name == May)
	{
		return true;
	}
	else if (month_name == June || month_name == Jun)
	{
		return true;
	}
	else if (month_name == July || month_name == Jul)
	{
		return true;
	}
	else if (month_name == August || month_name == Aug)
	{
		return true;
	}
	else if (month_name == September || month_name == Sept || month_name == Sep)
	{
		return true;
	}
	else if (month_name == October || month_name == November || month_name == December)
	{
		return true;
	}
	else if (month_name == Oct || month_name == Nov || month_name == Dec)
	{
		return true;
	}
	else
	{
		return false;
	}
}
