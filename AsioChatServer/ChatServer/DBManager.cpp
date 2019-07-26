#include "pch.h"

DBManager::DBManager()
{

}


DBManager::~DBManager()
{
}

void DBManager::Init()
{
	try {
		auto driver = get_driver_instance(); //�� �����ϸ� �ȵ�
		con = std::unique_ptr<sql::Connection>(driver->connect(host_name, user_name, password)); //����
		con->setSchema(schema_name); //Ư�� DB ����

		statement = std::unique_ptr<sql::Statement>(con->createStatement());

		auto result_set = std::unique_ptr<sql::ResultSet>(statement->executeQuery("SELECT 1"));
	}
	catch (sql::SQLException& e) {
		std::cout << e.what() << std::endl
			<< "error code: " << e.getErrorCode() << std::endl
			<< "sqlstate:" << e.getSQLState() << std::endl;
	}
}

void DBManager::ExecuteSql(const sql::SQLString sql)
{
	try {
		//auto statement = std::unique_ptr<sql::Statement>(con->createStatement());
		auto result = std::unique_ptr<sql::ResultSet>(statement->executeQuery(sql));
	}
	catch (sql::SQLException& e) {
		//std::cout << e.what() << std::endl
		//	<< "error code: " << e.getErrorCode() << std::endl
		//	<< "sqlstate:" << e.getSQLState() << std::endl;
	}
}

DBManager& DBManager::Instance()
{
	static DBManager dbManager;

	return dbManager;
}
