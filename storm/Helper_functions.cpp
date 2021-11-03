#include "Helper_functions.h"
#include<math.h>
#include"Constants.h"
#include<iostream>
#include<string>
#include "fatalityList.h"


using namespace std;
//Function to display first few entries of storm_event

//A better approach is to use enum's with ordinality, or struct for months with ordinal meta-data.
//Decided to not overdesign for the time being, and stick with constants.
string January = "January";
string February = "February";
string March = "March";
string April = "April";
string May = "May";
string June = "June";
string July = "July";
string August = "August";
string September = "September";
string October = "October";
string November = "November";
string December = "December";

//Abbreviation of months
string Jan = "Jan";
string Feb = "Feb";
string Mar = "Mar";
string Apr = "Apr";
string Jun = "Jun";
string Jul = "Jul";
string Aug = "Aug";
string Sep = "Sep";
string Sept = "Sept";
string Oct = "Oct";
string Nov = "Nov";
string Dec = "Dec";



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
		else if (cost.back() == 'M')
		{
			units = 1000000;
		}
		else if (cost.back() == 'B')
		{
			units = 1000000000;
		}
		else
		{
			cout << cost.back() << endl;
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

bool checkMonthLexographical(string month_name, string lowRange, string highRange)
{

	bool result = false;

	//Spreading it out month-wise for ease of reading.
	if (month_name == January || month_name == Jan || month_name == February || month_name == Feb || month_name == March || month_name == Mar || month_name == April || month_name == Apr || month_name == May || month_name == June || month_name == Jun)
	{


		if (lowRange <= month_name && month_name <= highRange)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	else if (month_name == July || month_name == Jul || month_name == August || month_name == Aug || month_name == September || month_name == Sept || month_name == Sep)
	{
		if (lowRange <= month_name && month_name <= highRange)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	else if (month_name == October || month_name == November || month_name == December || month_name == Oct || month_name == Nov || month_name == Dec)
	{
		if (lowRange <= month_name && month_name <= highRange)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (month_name == Oct || month_name == Nov || month_name == Dec)
	{
		if (lowRange <= month_name && month_name <= highRange)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return result;

}
bool isTableSizePrime(int size)
{
	bool isPrime = true;
	for (int i = 2; i <= sqrt(size); i++)
	{
		if (size%i == 0)
		{
			isPrime = false;
			return isPrime;
		}

	}
	return isPrime;
}
int returnNearestBiggerPrime(int size)
{
	//Test for prime, find the next biggest prime.
	while (!isTableSizePrime(size))
	{
		size++;
	}

	return size;
}
void attachFatalityToTheUnderlyingDataBase(annual_storms * annualStormArray, int Index_year, int Index_event, string * token)
{
	fatalityList *item = new fatalityList(token);

	fatality_event *head = annualStormArray[Index_year].events[Index_event].f;
	fatality_event *nextitem = annualStormArray[Index_year].events[Index_event].f;
		while (nextitem != nullptr)
		{

			if (item->fatality_id > nextitem->fatality_id) //Check if something inbetween needs to be where we insert
			{
				item->next = nextitem->next;
				nextitem->next = item;


			}

			nextitem = nextitem->next;
		}
	
		if (nextitem == nullptr) //If the list is empty add the  item directly
		{
			nextitem = item;
		}
}

bool checkMonth(string month_name,string lowRange,string highRange)
{
	int lowerBound = changeMonthToValue(lowRange);
	int higherBound = changeMonthToValue(highRange);
	int monthValue = changeMonthToValue(month_name);
	bool result = false;

	if (lowerBound == 0 || higherBound == 0 || monthValue == 0)
	{
		return result;
	}

	//Spreading it out month-wise for ease of reading.
	if (month_name == January || month_name == Jan || month_name == February || month_name == Feb || month_name == March || month_name == Mar || month_name == April || month_name == Apr|| month_name == May|| month_name == June || month_name == Jun)
	{


		if (lowerBound <= monthValue && monthValue <= higherBound)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

	else if (month_name == July || month_name == Jul||month_name == August||month_name == Aug||month_name == September||month_name ==Sept||month_name == Sep)
	{
		if (lowerBound <= monthValue && monthValue <= higherBound)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	else if (month_name == October || month_name == November || month_name == December|| month_name == Oct || month_name == Nov || month_name == Dec)
	{
		if (lowerBound <= monthValue && monthValue <= higherBound)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (month_name == Oct || month_name == Nov || month_name == Dec)
	{
		if (lowerBound <= monthValue && monthValue <= higherBound)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return result;

}

int changeMonthToValue(string month_name)
{
	
	if (month_name == January||month_name == Jan)
	{
		return 1;
	}

	else if (month_name == February || month_name == Feb)
	{
		return 2;
	}

	else if (month_name == March || month_name == Mar)
	{
		return 3;
	}

	else if (month_name == April || month_name == Apr)
	{
		return 4;
	}

	else if (month_name == May)
	{
		return 5;
	}

	else if (month_name == June||month_name==Jun)
	{
		return 6;
	}

	else if (month_name == July || month_name == Jul)
	{
		return 7;
	}

	else if (month_name == August||month_name == Aug)
	{
		return 8;
	}

	else if (month_name == September||month_name == Sept||month_name == Sep)
	{
		return 9;
	}
	else if (month_name == October || month_name == Oct)
	{
		return 10;
	}

	else if (month_name == November || month_name == Nov)
	{
		return 11;
	}

	else if (month_name == December || month_name == Dec)
	{
		return 12;
	}
	else
	{
		return 0;
	}


}
