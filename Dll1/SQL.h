#pragma once

#include <iostream>
#include <list>
#include <string>
#include "sqlite3.h"
#include"userData.h"

class  __declspec(dllexport) SQL {
private:
	
	sqlite3* db;
	

public:

	SQL();
	~SQL();
	void Open(const char* dir);
	void createTable();
	int createIndex();
	void insertData(UserDataList& dataList);
	int DataIntoList(UserDataList& dataList);
	int DeleteItem(UserDataList & dataList, int number);
	int bindName(UserDataList& dataList, std::string name);
	//int selectData(UserDataList& dataList);
	void beginTransaction();
	void commitTransaction();
	int UpdateData(UserDataList& dataList);
	void rollback();

	int isexist(int number);

	int insertData2(UserDataList & dataList);
};