//#include "ConnectDB.h"
//
//
//
//
//
////Constructors definition
//ConnectDB::ConnectDB(){
//}
//ConnectDB::ConnectDB(std::string ip, std::string port, std::string user, std::string password){
//	this->ip = ip;
//	this->port = port;
//	this->user = user;
//	this->password = password;
//}
//
////Setters definition
//void ConnectDB::setIp(std::string ip) {
//	this->ip = ip;
//}
//void ConnectDB::setUser(std::string user) {
//	this->user = user;
//}
//void ConnectDB::setPassword(std::string password) {
//	this->password = password;
//}
//void ConnectDB::setPort(std::string port) {
//	this->port = port;
//}
//void ConnectDB::connect() {
//	try
//	{
//		std::cout << "Connecting to database..." << std::endl;
//		driver = get_driver_instance();
//
//		std::cout << "Conecting to " << tcp << ip << separator << port << std::endl;
//		conn = driver->connect(tcp + getIp() + separator + getPort(), getUser(), getPassword());
//
//		connStatus = true;
//		std::cout << "Connected to database" << std::endl;
//	}
//	catch (sql::SQLException& e)
//	{
//		std::cout << "ERROR: " << e.what() << std::endl;
//
//	}
//}
//
////Getters definition
//std::string ConnectDB::getIp() {
//	return ip;
//}
//std::string ConnectDB::getUser() {
//	return user;
//}
//std::string ConnectDB::getPassword() {
//	return password;
//}
//std::string ConnectDB::getPort() {
//	return port;
//}
//
////Destructors definition
//ConnectDB::~ConnectDB() {
//	try
//	{
//		std::cout << "Closing connection..." << std::endl;
//		conn->close();
//		connStatus = false;
//		std::cout << "Connection closed" << std::endl;
//	}
//	catch (sql::SQLException& e)
//	{
//		std::cout << "ERROR: " << e.what() << std::endl;
//	}
//}
