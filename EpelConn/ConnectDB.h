#pragma once
//Local includes


//External Includes
#include <iostream>


//MySQL includes
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>




class ConnectDB
{
private:
	//Database variables
	sql::Connection* conn;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::Driver* driver;
	std::string user;
	std::string password;
	std::string tcp = "tcp://";
	std::string ip;
	std::string separator = ":";
	std::string port;
	
	bool connStatus = false;
	
public:
	ConnectDB();
	ConnectDB(std::string ip, std::string port, std::string user, std::string password);
	void setIp(std::string ip);
	void setUser(std::string user);
	void setPassword(std::string password);
	void setPort(std::string port);
	void connect();
	std::string getIp();
	std::string getUser();
	std::string getPassword();
	std::string getPort();
	~ConnectDB();
};


	

