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
	//Database objects
	sql::Connection* conn;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::Driver* driver;

	//Database variables
	std::string database;
	std::string table;
	std::string field;
	std::string value;
	
	std::string user;
	std::string password;
	std::string tcp = "tcp://";
	std::string ip;
	std::string separator = ":";
	std::string port;
	bool connStatus = false;
	
	
public:
	//Database call
	
	 

	
	//Constructors declaration
	SQL();
	

	
	
	
	//Setters declaration
	void setTable(std::string table);
	void setField(std::string field);
	void setIp(std::string ip);
	void setUser(std::string user);
	void setPass(std::string password);
	void setPort(std::string port);
	void setDatabase(std::string database);	
	void setValue(std::string value);
	
	
	
	
	
	//Getters declaration
	std::string getDatabase();
	std::string getTable();
	std::string getField();
	std::string getIp();
	std::string getUser();
	std::string getPass();
	std::string getPort();
	std::string getValue();

	//Methods declaration
	void createDatabase(); //Developing
	void query();
	void query(std::string field);
	void fieldQuery();
	void connect();
	void insert();
	
	
	
	//Destructors declaration 
	~SQL();
};

