#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <fstream>
#include <exception>
#include "userData.h"
#include "SQLException.h"


class  __declspec(dllexport) fileOperations{
private:
	typedef std::list<userData> UserDataList;
	userData d;
	std::string name, birthdayStr;
	int16_t birthday;
	
public:
	fileOperations() {}
	void readData(UserDataList& dataList);
	void inputData(UserDataList& dataList);
	~fileOperations() {}
};
