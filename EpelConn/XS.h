#pragma once

#include "Queries.h"
#include "Errors.h"

namespace XS
{
	//Connection Methods
	int connect(std::string ip, std::string port);
	int getStatus();
	void reset();

	//General Methods		

	//Articles	
	int addArticle(std::vector<std::string>valueVector);
	int deleteArticle(int id);
	int setDescriptionArticle(std::vector<std::string> descriptions, int Code);	

	//Families	
	int addFamily(std::vector<std::string>valueVector, int dpt);
	int deleteFamily(int id);

	//Clients
	int addClient(std::vector<std::string>valueVector);
	int deleteClient(int id);

	//Vendors
	int addVendor(std::vector<std::string>valueVector);
	int deleteVendor(int id);

	//Departments
	int addDepartment(std::vector<std::string>valueVector);
	int deleteDepartment(int id);
	int addDepartmentHeader(std::string header, int opt, int Code);

	//Tares
	int addTare(std::vector<std::string>valueVector);
	int deleteTare(int id);

	//Vats
	int addVats(std::vector<std::string>valueVector);
	int deleteVats(int id);

	//Scales
	int addScale(std::vector<std::string>valueVector);
	int deleteScale(int id);
}