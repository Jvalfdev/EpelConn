#include "Queries.h"

#define LOG(x) std::cout << x << std::endl

//Constructors definition
SQL::SQL() {
}

//Setters definition
void SQL::setDatabase(std::string database) {
	this->database = database;
}

void SQL::setField(std::string field) {
	this->field = field;
}
void SQL::setTable(std::string table) {
	this->table = table;
}
void SQL::setIp(std::string ip) {
	this->ip = ip;
}
void SQL::setUser(std::string user) {
	this->user = user;
}
void SQL::setPass(std::string password) {
	this->password = password;
}
void SQL::setPort(std::string port) {
	this->port = port;
}
void SQL::setValue(std::string value) {
	this->value = value;
}
//void SQL::setQueryValues(std::vector<std::string>queryValues) {
//	this->queryValues = queryValues;
//}


//Getters definition
std::string SQL::getDatabase() {
	return database;
}
std::string SQL::getField() {
	return field;
}
std::string SQL::getTable() {
	return table;
}
std::string SQL::getIp() {
	return ip;
}
std::string SQL::getUser() {
	return user;
}
std::string SQL::getPass() {
	return password;
}
std::string SQL::getPort() {
	return port;
}
std::string SQL::getValue() {
	return value;
}
std::vector <std::string> SQL::getQueryValues() {
	return queryValues;	
}
int SQL::getDatabaseList(std::vector<std::string>& l_databaseList) {
	try
	{
		std::string query = "SHOW DATABASES;";
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		l_databaseList.clear();
		while (res->next()) {
			l_databaseList.push_back(res->getString(1));
		}
	}
	catch (sql::SQLException& e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
}

int SQL::getTableList(std::vector <std::string>& tableList, std::string database) {
	try
	{
		
		std::string query = "SHOW TABLES FROM " + database + " ;";
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		tableList.clear();
		while (res->next()) {
			tableList.push_back(res->getString(1));
		}
	}
	catch (sql::SQLException& e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
}

int SQL::getTableFields(std::vector<std::string>& tableFields, std::string database, std::string table) {
	try
	{
		std::string query = "SHOW COLUMNS FROM " + database + "." + table + ";";
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		tableFields.clear();
		while (res->next()) {
			tableFields.push_back(res->getString(1));
		}
	}
	catch (sql::SQLException& e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
}

//Methods definition
int SQL::connect(std::string l_IP, std::string l_Port, std::string l_User, std::string l_Pass) {
	try
	{
		driver = get_driver_instance();

		conn = driver->connect(tcp + l_IP + separator + l_Port, l_User, l_Pass);

		connStatus = true;

	}
	catch (sql::SQLException& e)
	{
		std::string _ExceptionString = e.what();
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;

}
int SQL::connect(std::string l_Host, std::string l_User, std::string l_Pass) {
	try
	{
		driver = get_driver_instance();

		conn = driver->connect(tcp + l_Host, l_User, l_Pass);

		connStatus = true;

	}
	catch (sql::SQLException& e)
	{
		std::string _ExceptionString = e.what();
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
}

int SQL::query(std::string query) {
	try
	{
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
	}
	catch (sql::SQLException& e)
	{
		std::string _ExceptionString = e.what();
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
}
int SQL::query(std::string l_Db, std::string l_Table, std::vector<std::string> &l_query) {
	try
	{

		std::string query = "SELECT * FROM " + l_Table + ";";
		
		conn->setSchema(l_Db);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		
		
		
		
		while (res->next()) {		
			
			for (int i = 0; i < res->getMetaData()->getColumnCount(); i++) {
				
				l_query.push_back(res->getString(i+1));
				
			}	
			
			
			
		}
		
	}
	catch (sql::SQLException &e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
}
int SQL::query(std::string l_Db, std::string l_Table, std::string l_Field, std::vector<std::string>& l_query) {
	try
	{
		std::string query = "SELECT " + l_Field + " FROM " + l_Table + ";";
		conn->setSchema(l_Db);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		l_query.clear();
		while (res->next()) {
			l_query.push_back(res->getString(1));
		}
	}
	catch (sql::SQLException &e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
}




void SQL::insert() {
	

	
	try
	{
		std::string queryC = "SELECT * FROM " + getTable() + ";";
		conn->setSchema(getDatabase());
		stmt = conn->createStatement();
		res = stmt->executeQuery(queryC);

		
		conn->setSchema(getDatabase());
		stmt = conn->createStatement();
		
		LOG(res->getMetaData()->getColumnCount());
		
		
		std::vector <std::string> fieldVector;
			
		
		
		for(int i = 0; i < res->getMetaData()->getColumnCount(); i++) {
			fieldVector.push_back(res->getMetaData()->getColumnName(i + 1));
			
		}
		
		

		std::vector <std::string> valuesVector;
		
		for (int i = 0; i < res->getMetaData()->getColumnCount(); i++) {
			std::cout << res->getMetaData()->getColumnName(i + 1) << ": "; 
			std::cout << res->getMetaData()->getColumnTypeName(i + 1) << std::endl;
			std::string values;
			
			valuesVector.push_back(values);
		}
		
		std::string strt;
		strt = "INSERT INTO";
		strt += " " + getTable() + "(";
		for (int i = 0; i < fieldVector.size(); i++) {
			strt += fieldVector[i];
			if (i != fieldVector.size() - 1) {
				strt += ",";
			}
		}
		strt += ") VALUES (";
		for (int i = 0; i < valuesVector.size(); i++) {
			strt += "'" + valuesVector[i] + "'";
			if (i != valuesVector.size() - 1) {
				strt += ",";
			}
		}
		strt += ");";

					
		res=stmt->executeQuery(strt);

		LOG("Insert completed!!!");		
		
		
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


int SQL::createDatabase(std::string database) {
	try
	{
		std::string query = "CREATE DATABASE " + database + ";";
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
	}
	catch (sql::SQLException& e)
	{
		std::string _ExceptionString = e.what();
		return _EXCEPTION_ERROR_;
	}
	return _SUCCESS_;
	
}


//Destructors definition
SQL::~SQL() {
	delete stmt;
	delete conn;
	delete res;
	delete &driver;
}
