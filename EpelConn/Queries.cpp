#include "Queries.h"



//Constructors definition
SQL::SQL(){
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



//Methods definition

void SQL::query() {
	try
	{

		std::string query = "SELECT * FROM " + getTable() + ";";
		std::cout << query << std::endl;
		conn->setSchema(getDatabase());
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
				
		while (res->next()) {		
			
			for (int i = 1; i <= res->getMetaData()->getColumnCount(); i++) {
				std::cout << res->getString(i) << " ";
			}
			std::cout << "" << std::endl;
			
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
void SQL::query(std::string field) {
	try
	{

		std::string query = "SELECT * FROM " + getTable() + ";";
		std::cout << query << std::endl;
		conn->setSchema(getDatabase());
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);

		while (res->next()) {

			std::cout << res->getString(field) << " ";

		}
	}
	catch (sql::SQLException& e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
}
void SQL::fieldQuery() {
	try
	{

		std::string query = "SELECT * FROM " + getTable() + ";";
		std::cout << query << std::endl;
		conn->setSchema(getDatabase());
		stmt = conn->createStatement();
		res = stmt->executeQuery(query);
		

		for (int i = 1; i <= res->getMetaData()->getColumnCount(); i++) {
			
			std::cout << res->getMetaData()->getColumnLabel(i) << " ";

		}
	}
	catch (sql::SQLException& e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
}
void SQL::connect() {
	try
	{
		std::cout << "Connecting to database..." << std::endl;
		driver = get_driver_instance();

		std::cout << "Conecting to " << tcp << ip << separator << port << std::endl;
		conn = driver->connect(tcp + getIp() + separator + getPort(), getUser(), getPass());

		connStatus = true;
		std::cout << "Connected to database" << std::endl;
	}
	catch (sql::SQLException& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;

	}
}
void SQL::insert() {
	try
	{
		std::string query = "INSERT INTO " + getTable() + " (" + getField() + ", Name) VALUES (" + getValue() + ", 'Bobby');";
		std::cout << query << std::endl;
		conn->setSchema(getDatabase());
		stmt = conn->createStatement();
		stmt->execute(query);
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

//Developing
void SQL::createDatabase() {

	/*std::string query = "CREATE DATABASE " + getDatabase() + ";";
	std::cout << query << std::endl;
	conn->setSchema(getDatabase());
	stmt = conn->createStatement();
	stmt->execute("USE " + getDatabase());
	stmt->execute(query);
	stmt->execute("DROP TABLE IF EXISTS " + getTable());
	stmt->execute("CREATE TABLE " + getTable() + "(id INT, label CHAR(1))");
	stmt->execute("INSERT INTO test(id, label) VALUES (1, 'a')");
	std::cout << "Database Created" << std::endl;*/
}


//Destructors definition
SQL::~SQL() {
	delete stmt;
	delete conn;
}
