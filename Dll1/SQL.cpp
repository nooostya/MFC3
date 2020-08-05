#include "pch.h"
#include "SQL.h"
#include"SQLException.h"
#include"userData.h"
#include<string>

SQL::SQL() : db(nullptr) {

}

void SQL::Open(const char * dir)
{
	int rc = sqlite3_open(dir, &db);
	if (rc)
	{
		throw SQLException("Database opening error", rc);
	}
	else {
		fprintf(stdout, "Opened database successfully\n");
	}
	this->createTable();
	this->createIndex();
}

void SQL::createTable()
{
	char* messageError;
	std::string sql = "CREATE TABLE IF NOT EXISTS BIRTHDAYS("
		"NUMBER INTEGER PRIMARY KEY,"
		"NAME TEXT NOT NULL,"
		"birthday INT NOT NULL)";

	int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
	if (rc != SQLITE_OK) {
		throw SQLException("error creating table", rc);

	}
	else
		std::cout << "Table created successfully" << std::endl;

}

int SQL::createIndex()
{
	char* messageError;
	std::string sql("CREATE INDEX IF NOT EXISTS main ON BIRTHDAYS(name)");
	int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
	if (rc != SQLITE_OK) {
		throw SQLException("error creating index", rc);
	}
	else {
		std::cout << "Index created successfully" << std::endl;
	}
	return 0;
}

void SQL::insertData(UserDataList & dataList)
{
	sqlite3_stmt *stmt;
	const char *sql = "INSERT INTO Birthdays (name,birthday) VALUES (?,?)";
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		throw SQLException("insert error", rc);
	}

	for (UserDataList::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		sqlite3_bind_text(stmt, 1, it->name.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, it->birthday);
		rc = sqlite3_step(stmt);

		sqlite3_reset(stmt);
	}
	dataList.clear();
	sqlite3_finalize(stmt);
}


int SQL::bindName(UserDataList & dataList, std::string name)
{
	sqlite3_stmt *stmt;

	int rc = sqlite3_prepare_v2(db, "SELECT * FROM birthdays WHERE name = ?", -1, &stmt, 0);
	if (rc != SQLITE_OK)
	{
		throw SQLException("select error", rc);
	}
	
	sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
	userData a;

	int er = sqlite3_step(stmt);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		a.number = sqlite3_column_int(stmt, 0);
		a.name = (const char*)(sqlite3_column_text(stmt, 1));
		a.birthday = sqlite3_column_int(stmt, 2);
		dataList.push_back(a);
	}
	if (er != SQLITE_ROW) {
		throw SQLException("no such name", er);
	}

	sqlite3_finalize(stmt);
	return 0;
}

int SQL::selectData(UserDataList & dataList)
{
	for (UserDataList::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		std::cout << it->number << "|" << it->name << "|" << it->birthday << std::endl;
	}
	return 0;
}

SQL::~SQL()
{
	if (db != nullptr)
		sqlite3_close(db);
}