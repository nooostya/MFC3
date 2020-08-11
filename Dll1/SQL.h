#pragma once

#include <iostream>
#include <list>
#include <string>
#include"userData.h"
#include "sqlite3.h"

class  __declspec(dllexport) SQL {
private:
	
	sqlite3* db;
	

public:

	SQL();
	~SQL();
	void Open(const char* dir);
	void createTable();
	int createIndex();
	int DeleteItem();
	void insertData(UserDataList& dataList);
	int DataIntoList(UserDataList& dataList);
	int bindName(UserDataList& dataList, std::string name);
	int selectData(UserDataList& dataList);
	
};