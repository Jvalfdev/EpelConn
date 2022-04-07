#pragma once
//Local includes
#include "Errors.h"

//External Includes
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

//MySQL includes
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>



#define LOG(x) std::cout << x << std::endl


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
	
	std::vector <std::string> m_vectorValues;
	std::vector <std::string> databasesList;
	std::vector < std::string > queryValues;
	
	bool connStatus = false;
	
	
public:
	
	//Constructors declaration
	SQL();	
	
	//Setters declaration
	void setDatabase(std::string database);
	void setTable(std::string table);
	void setField(std::string field);
	void setIp(std::string ip);
	void setUser(std::string user);
	void setPass(std::string password);
	void setPort(std::string port);	
	void setValue(std::string value);	
	//void setQueryValues(std::vector < std::string> queryValues);
	
	
	//Getters declaration
	std::string getDatabase();	
	std::string getTable();
	std::string getField();
	std::string getIp();
	std::string getUser();
	std::string getPass();
	std::string getPort();
	std::string getValue();
	
	int getDatabaseList(std::vector<std::string>& l_databaseList);//It returns  a database list into a vector
	
	std::vector < std::string> getQueryValues();

	//Methods declaration
	int connect(std::string l_IP, std::string l_Port, std::string l_User, std::string l_Pass);
	int connect(std::string l_Host, std::string l_User, std::string l_Pass);
	
	int query(std::string query);
	int query(std::string l_Db, std::string l_Table, std::vector<std::string>& l_query);
	int query(std::string l_Db, std::string l_Table, std::string l_Field, std::vector<std::string>& l_query);
	

	void insert();
	void createDatabase(); //Developing
	
	
	
	
	
	//Destructors declaration 
	~SQL();
};

