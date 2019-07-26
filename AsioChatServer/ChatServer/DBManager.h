#pragma once
#include "pch.h"

class DBManager
{
private:
	sql::SQLString host_name = "10.25.20.245";
	sql::SQLString schema_name = "ztest";
	sql::SQLString user_name = "doz2";
	sql::SQLString password = "test1324";

	std::unique_ptr<sql::Connection> con;
	std::unique_ptr<sql::Statement> statement;

public:
	DBManager();
	~DBManager();

	void Init();

	void ExecuteSql(const sql::SQLString sql);

	static DBManager& Instance();
};

