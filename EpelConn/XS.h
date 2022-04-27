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
	int setDescriptionArticle(std::vector <std::string> descriptions, int code);	
	int setTareArticle(double tare,double packingTare, int code);
	int deleteTareArticle(int code);
	
	//Families	
	int addFamily(std::vector<std::string> family, int dpt);
	int deleteFamily(int id);

	//Clients
	int addCustomer(std::vector<std::string>customer);
	int deleteCustomer(int id);

	//Vendors
	int addVendor(std::vector<std::string>vendor);
	int deleteVendor(int id);

	//Departments
	int addDepartment(int code, int counter, std::string name);
	int deleteDepartment(int code, int counter);
	int addDepartmentHeader(std::string header, int opt, int code, int counter);
	int deleteDepartmentHeader(int code, int counter, int header);
	int addDepartmentFooter(std::string footer, int opt, int code, int counter);
	int deleteDepartmentFooter(int code, int counter, int footer);
	int addDepartmentLabel(std::string label, int opt, int code, int counter);
	int deleteDepartmentLabel(int code, int counter, int label);
	
	//Tares
	int addTare(int code, std::string name, double tare);
	int deleteTare(int id);

	//Vats
	int addVats(int code, std::string name, double percent);
	int deleteVats(int id);

	//Scales
	
	int addScaleHeader(std::string header, int opt, int counter, int number);
	int deleteScaleHeader(int counter, int number, int header);
	int addScaleFooter(std::string footer, int opt, int counter, int number);
	int deleteScaleFooter(int counter, int number, int footer);

	//Traceability
	int addTraceability(std::string name, std::string text, int code);
	int deleteTraceability(int code);

	//Nutritional Info
	int addNutritionalInfo(std::string name, std::string text, int code);
	int deleteNutritionalInfo(int code);
}