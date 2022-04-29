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
		return e.getErrorCode();
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
		return e.getErrorCode();
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
		return e.getErrorCode();
	}
	return _SUCCESS_;
}

//Methods definition
int SQL::connect(std::string l_IP, std::string l_Port, std::string l_User, std::string l_Pass) {
	try
	{
		driver = get_driver_instance();

		conn = driver->connect(tcp + l_IP + separator + l_Port, l_User, l_Pass);

		if (connStatus == false)
		{
			connStatus = true;
			return _CONNECTION_SUCESSFULL_;
		}
		else
		{
			return _CONNECTION_ALREADY_OPEN_;
		}
		

	}
	catch (sql::SQLException& e)
	{
		return e.getErrorCode();
	}
	

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
		
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::reset() {
	try
	{
		conn->close();
		connStatus = false;
		return _SUCCESS_;
	}
	catch (sql::SQLException& e)
	{
		return e.getErrorCode();
	}
}
bool SQL::isConnected() {
	if (connStatus==true) {
		return true;
	}
	else {
		return false;
	}
}
int SQL::query(std::string database, std::string query) {
	try
	{
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
	}
	catch (sql::SQLException& e)
	{
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::query(std::string database, std::string query, std::vector<std::string> &queryValues) {
	try
	{
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		
		if (res->next()) {
			
			for (int i = 1; i <= res->getMetaData()->getColumnCount(); i++) {
				
				queryValues.push_back(res->getString(i));
			}
		}
	}
	catch (sql::SQLException& e)
	{
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::v_query(std::string database, std::string query, std::vector<std::vector<std::string>>&queryValues) {
	try
	{
		std::vector<std::string> row;
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		

		while (res->next()) {
			
			row.clear();
			for (int i = 1; i <= res->getMetaData()->getColumnCount(); i++) {
				row.push_back(res->getString(i));
			}
			queryValues.push_back(row);
		}
	}
	catch (sql::SQLException& e)
	{
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::query(std::string database, std::string l_Table, std::string l_Field, std::vector<std::vector<std::string>>& l_query) {
	try
	{
		std::vector<std::string> strV;
		std::string query = "SELECT " + l_Field + " FROM " + l_Table + ";";
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		l_query.clear();
		while (res->next()) {
			strV.clear();

			for (int i = 0; i < res->getMetaData()->getColumnCount(); i++) {

				strV.push_back(res->getString(i + 1));
			}
			l_query.push_back(strV);
		}
	}
	catch (sql::SQLException &e)
	{
		
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::insert(std::string database, std::string table, std::vector<std::string> fieldVector, std::vector<std::string> valueVector) {	
		
	try
	{
		std::string fields;
		for (int i = 0; i < fieldVector.size(); i++) {
			fields.append(fieldVector[i]);
			if (i != fieldVector.size() - 1) {
				fields.append(", ");
			}
		}

		std::string values;
		for (int i = 0; i < valueVector.size(); i++) {
			values.append("'" + valueVector[i] + "'");
			if (i != valueVector.size() - 1) {
				values.append(", ");
			}
		}
		
		std::string query = "INSERT INTO " + table + " (" + fields + ") VALUES (" + values + ");";
		
		conn->setSchema(database);
		stmt = conn->createStatement();		
		res = stmt->executeQuery(query);			
		
	}
	catch (sql::SQLException &e)
	{
		
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::update(std::string database, std::string table, std::vector<std::string> fieldVector, std::vector<std::string> valueVector, std::string where) {
	try
	{
		std::string fields;
		for (int i = 0; i < fieldVector.size(); i++) {
			fields.append(fieldVector[i] + " = '" + valueVector[i] + "'");
			if (i != fieldVector.size() - 1) {
				fields.append(", ");
			}
		}
		
		
		
		std::string query = "UPDATE " + table + " SET " + fields + " WHERE " + where + ";";
		conn->setSchema(database);
		stmt = conn->createStatement();
		
		res = stmt->executeQuery(query);
	}
	catch (sql::SQLException &e)
	{
		
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::update(std::string database, std::string table, std::vector<std::string> fieldValueVector, std::string where) {
	try
	{
		std::string fields;
		for (int i = 0; i < fieldValueVector.size(); i++) {
			fields.append(fieldValueVector[i]);			
		}
		std::string query = "UPDATE " + table + " SET " + fields + " WHERE " + where + ";";
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
	}
	catch (sql::SQLException& e)
	{
		
		return e.getErrorCode();
	}
	return _SUCCESS_;
}
int SQL::deleteSQL(std::string database, std::string table, std::string where) {	
	try
	{
		std::string query = "DELETE FROM " + table + " WHERE " + where + ";";
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		return _SUCCESS_;
	} 
	catch (sql::SQLException& e)
	{		
		return e.getErrorCode();
	}
}
int SQL::deleteSQL(std::string database, std::string table) {
	try
	{
		std::string query = "DELETE FROM " + table + ";";
		conn->setSchema(database);
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		return _SUCCESS_;
	}
	catch (sql::SQLException& e)
	{
		return e.getErrorCode();
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
