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
	this->createTable();
	this->createIndex();
}

void SQL::createTable()
{
	char* messageError;
	std::string sql = "CREATE TABLE IF NOT EXISTS BIRTHDAYS("
		"NUMBER INTEGER PRIMARY KEY,"
		"NAME TEXT NOT NULL,"
		"BIRTHDAY INT NOT NULL)";

	int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
	if (rc != SQLITE_OK) {
		throw SQLException("error creating table", rc);

	}
}

int SQL::createIndex()
{
	char* messageError;
	std::string sql("CREATE INDEX IF NOT EXISTS main ON BIRTHDAYS(name)");
	int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
	if (rc != SQLITE_OK) {
		throw SQLException("error creating index", rc);
	}
	return 0;
}

void SQL::insertData(UserDataList & dataList)
{
	sqlite3_stmt *stmt;
	const char *sql = "INSERT INTO Birthdays (number,name,birthday) VALUES (?,?,?)";
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		throw SQLException("insert error", rc);
	}

	for (UserDataList::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		sqlite3_bind_int(stmt, 1, it->number);
		sqlite3_bind_text(stmt, 2, it->name.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 3, it->birthday);
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) 
		{
			throw SQLException("bind error", rc);
		}
		sqlite3_reset(stmt);
	}
	sqlite3_finalize(stmt);
}
int SQL::DataIntoList(UserDataList & dataList)
{
	dataList.clear();
	sqlite3_stmt *stmt;

	int rc = sqlite3_prepare_v2(db, "SELECT * FROM birthdays", -1, &stmt, 0);
	if (rc != SQLITE_OK)
	{
		throw SQLException("select all error", rc);
	}
	userData a;

	int er = SQLITE_DONE;
	do
	{
		er = sqlite3_step(stmt);
		if (er == SQLITE_ROW) {
			userData a;
			a.number = sqlite3_column_int(stmt, 0);
			a.name = (const char*)(sqlite3_column_text(stmt, 1));
			a.birthday = sqlite3_column_int(stmt, 2);
			dataList.push_back(a);
		}

	} while (er == SQLITE_ROW);

	sqlite3_finalize(stmt);
	return 0;
}
int SQL::DeleteItem(UserDataList & dataList, int number) {
	sqlite3_stmt *stmt;
	int rc = sqlite3_prepare_v2(db, "DELETE FROM birthdays WHERE number=?", -1, &stmt, 0);
	if (rc != SQLITE_OK)
	{
		throw SQLException("delete item error", rc);
		
	}
	sqlite3_bind_int(stmt, 1, number);
	rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return 0;

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
	
	int er=SQLITE_DONE;
	//int er = sqlite3_step(stmt);
	do 
	{
		er = sqlite3_step(stmt);
		if (er == SQLITE_ROW) {
			userData a;
			a.number = sqlite3_column_int(stmt, 0);
			a.name = (const char*)(sqlite3_column_text(stmt, 1));
			a.birthday = sqlite3_column_int(stmt, 2);
			dataList.push_back(a);
		}
		
	}while (er == SQLITE_ROW);

	sqlite3_finalize(stmt);
	if (er != SQLITE_DONE) {
		throw SQLException("select error", rc);
	}
	return 0;
}

void SQL::beginTransaction() {
	sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
}
void SQL::commitTransaction() {
	sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, NULL);
}
int SQL::UpdateData( int number, std::string name)
{

	sqlite3_stmt *stmt;
	const char *sql = "UPDATE Birthdays SET name = ? WHERE number = ? ";
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		throw SQLException("update error", rc);
	}

		sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
		//sqlite3_bind_int(stmt, 2, it->birthday);
		sqlite3_bind_int(stmt, 2, number);
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE)
		{
			throw SQLException("bind error", rc);
		}
		sqlite3_reset(stmt);
	sqlite3_finalize(stmt);
}
int SQL::UpdateData2(int number, int birthday)
{
	sqlite3_stmt *stmt;
	const char *sql = "UPDATE Birthdays SET birthday = ? WHERE number = ? ";
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		throw SQLException("update error", rc);
	}

	sqlite3_bind_text(stmt, 1, birthday.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, number);
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		throw SQLException("bind error", rc);
	}
	sqlite3_reset(stmt);
	sqlite3_finalize(stmt);
}
void SQL::rollback() {
	sqlite3_exec(db, "ROLLBACK TRANSACTION;", NULL, NULL, NULL);
}
int SQL::isexist(int number)
{
	sqlite3_stmt *stmt;

	int rc = sqlite3_prepare_v2(db, "SELECT count() FROM birthdays WHERE number=?", -1, &stmt, 0);
	if (rc != SQLITE_OK)
	{
		throw SQLException("select error", rc);
	}
	std::string s = std::to_string(number);
	sqlite3_bind_text(stmt, 1, s.c_str(), -1, SQLITE_TRANSIENT);

	rc = sqlite3_step(stmt);
	int count = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return count;
}
int SQL::insertData2(UserDataList & dataList)
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
		if (rc != SQLITE_DONE)
		{
			throw SQLException("bind error", rc);
		}
		sqlite3_reset(stmt);
	}
	sqlite3_finalize(stmt);
}

SQL::~SQL()
{
	if (db != nullptr)
		sqlite3_close(db);
}