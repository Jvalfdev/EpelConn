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
	int deleteTotals();

	//Articles	
	int addArticle(std::vector<std::string>valueVector);
	int deleteArticle(int id);
	int setDescriptionArticle(std::vector<std::string> descriptions, int Code);	
	int setTareArticle(std::string tare,std::string packingTare, int Code);
	int deleteTareArticle(int code);
	
	//Families	
	int addFamily(std::vector<std::string>valueVector, int dpt);
	int deleteFamily(int id);

	//Clients
	int addCustomer(std::vector<std::string>valueVector);
	int deleteCustomer(int id);

	//Vendors
	int addVendor(std::vector<std::string>valueVector);
	int deleteVendor(int id);

	//Departments
	int addDepartment(std::vector<std::string>valueVector);
	int deleteDepartment(int id);
	int addDepartmentHeader(std::string header, int opt, int Code);
	int addDepartmentFooter(std::string footer, int opt, int Code);
	int addDepartmentLabel(std::string label, int opt, int Code);

	//Tares
	int addTare(std::vector<std::string>valueVector);
	int deleteTare(int id);

	//Vats
	int addVats(std::vector<std::string>valueVector);
	int deleteVats(int id);

	//Scales
	int addScale(std::vector<std::string>valueVector);
	int deleteScale(int id);
	int addScaleHeader( std::string header, int opt, int dpt, int number);
	int addScaleFooter( std::string footer, int opt, int dpt, int number);

	//Traceability
	int addTraceability(std::string name, std::string text, int code);
	int deleteTraceability(int code);

	//Nutritional Info
	int addNutritionalInfo(std::string name, std::string text, int code);
	int deleteNutritionalInfo(int code);
}