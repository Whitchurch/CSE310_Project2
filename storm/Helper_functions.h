#pragma once
#include "defns.h"
#include<string>
using namespace std;

void Display_StormEvents_Head(storm_event *events);
int Normalize_Scale(string cost);
bool checkMonth(string month_name,string lowRange, string highRange);
int changeMonthToValue(string month_name);
bool checkMonthLexographical(string month_name, string lowRange, string highRange);
bool isTableSizePrime(int size);
int returnNearestBiggerPrime(int size);
void attachFatalityToTheUnderlyingDataBase(annual_storms *annualStormArray, int Index_year, int Index_event, string *token);


