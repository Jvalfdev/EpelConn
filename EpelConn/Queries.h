#pragma once
//Local includes
#include "ConnectDB.h"

//External Includes
#include <iostream>


//MySQL includes
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>






class SQL 

{
private:
	sql::Connection* conn;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::Driver* driver;
	std::string database;
	std::string table;
	std::string field;
	std::string user;
	std::string password;
	std::string tcp = "tcp://";
	std::string ip;
	std::string separator = ":";
	std::string port;
	bool connStatus = false;
	
	
public:
	//Database call
	
	 

	
	//Constructors
	SQL();
	

	//Methods
	void createDatabase(std::string database);
	void query(std::string database, std :: string field);
	void insertData();
	void selectData();
	void updateData();
	void deleteData();
	void dropTable();
	void connect();
	
	
	
	//Setters
	void setDatabase(std::string database);
	void setTable(std::string table);
	void setField(std::string field);
	void setIp(std::string ip);
	void setUser(std::string user);
	void setPassword(std::string password);
	void setPort(std::string port);
	
	
	
	//Getters
	std::string getDatabase();
	std::string getTable();
	std::string getField();
	std::string getIp();
	std::string getUser();
	std::string getPassword();
	std::string getPort();
	
	//Destructors 
	~SQL();
};

