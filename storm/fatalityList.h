#pragma once
#include "defns.h"
#include<string>
using namespace std;

class fatalityList:public fatality_event
{
public:
	fatalityList();
	fatalityList(string *token);

};

