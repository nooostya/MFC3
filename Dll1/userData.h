#pragma once
#include <list>
#include<string>
struct userData
{
	std::string name;
	int birthday;
	int number;
};

typedef std::list<userData> UserDataList;