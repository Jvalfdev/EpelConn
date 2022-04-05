#include "Queries.h"



//Constructors
SQL::SQL(){
}

//Getters
std::string SQL::getDatabase() {
	return database;
}
std::string SQL::getField() {
	return field;
}
std::string SQL::getTable() {
	return table;
}

//Setters
void SQL::setDatabase(std::string database) {
	this->database = database;
}
void SQL::setField(std::string field) {
	this->field = field;
}
void SQL::setTable(std::string table) {
	this->table = table;
}

//Methods
void SQL::createDatabase(std::string database) {
	
	std::string query = "CREATE DATABASE " + database + ";";
	std::cout << query << std::endl;
	conn->setSchema(database);
	stmt = conn->createStatement();
	res = stmt->executeQuery(query);
}
void SQL::query(std::string database, std::string table) {
	try
	{
		driver->threadInit();
		std::string query = "SELECT * FROM " + table + ";";
		std::cout << query << std::endl;
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		while (res->next()) {
			std::cout << res->getString("Format") << std::endl;
		}
	}
	catch (sql::SQLException &e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
}

//Destructors
SQL::~SQL() {
	delete stmt;
	delete conn;
}
