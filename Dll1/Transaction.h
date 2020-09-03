#pragma once
#include "SQL.h"
#include "sqlite3.h"
class  __declspec(dllexport) Transaction
{
private:
	SQL& m_db;
	bool commited;

public:
	Transaction(SQL& db): m_db(db)
	{
		commited = false;
		m_db.beginTransaction();
	}

	~Transaction()
	{
		if (!commited)
		m_db.rollback();
	}

	void commit()
	{
		m_db.commitTransaction();
		commited = true;
	}
};
