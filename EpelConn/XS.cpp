#include "XS.h"

#define LOG(x) std::cout << x << std::endl

SQL sq;

namespace XS
{
	//Connection Methods
	int connect(std::string ip, std::string port) {

		std::string user = "epelMaster";
		std::string password = "epelsa";
		system(("Ping -n 1 " + ip + " > NUL").c_str());
		if (system(("Ping -n 1 " + ip + " > NUL").c_str()) == 0) {
			int status = sq.connect(ip, port, user, password);
			if (status == _CONNECTION_SUCESSFULL_)
			{
				
				return _CONNECTION_SUCESSFULL_;
			}
			else
			{
				
				return _CONNECTION_ALREADY_OPEN_;
			}
			
		}
		else {
			
			return _CONNECTION_FAILED_;
		}
	}
	int getStatus() {
		bool st = sq.isConnected();
		
		if (st == true) {
			
			return _CONNECTION_ON_;
		}
		else {
			
			return _CONNECTION_OFF_;
		}
	}
	void reset() {		
		sq.reset();	
	}
	
	//General Methods	
	

	//Articles	
	int addArticle(std::vector <std::string> article) {		
		try
		{
			std::vector <std::string> fieldVector = { 
			"Code",
			"Name",
			"ShortName",
			"Family",
			"Price",
			"SaleForm",
			"Counter",
			"PLU",
			"VAT",
			"Expiring",
			"PrefConsumption",
			"OrderKey"
			};

			int err = sq.insert("mbd", "items", fieldVector, article);
			

			if (err == _EXISTING_KEYCODE_) { 
				sq.update("mbd", "items", fieldVector, article, "Code = " + article[0]);
				return _ARTICLE_MODIFIED_;
			}
			return _ARTICLE_ADDED_;
		}
		catch (std::exception& e)
		{			
			return _ARTICLE_NOT_ADDED_;
		}
	}
	int deleteArticle(int Code) {
		try
		{std::string dInf = "Code = " + std::to_string(Code);
		LOG(sq.deleteSQL("mbd", "items", dInf));
		return _ARTICLE_REMOVED_;
		}
		catch (std::exception & e)
		{
			return _ARTICLE_NOT_REMOVED_;
		}
	}
	int setDescriptionArticle(std::vector<std::string> descriptions, int Code) {
		try
		{
			std::vector <std::string> fieldVector = { "Text", "Text2" };
			sq.insert("mbd", "items", fieldVector, descriptions);
			return _ARTICLE_DESCRIPTION_SET_;
		} catch (std::exception& e)
		{
			return _ARTICLE_DESCRIPTION_NOT_SET_;
		}
	}	
	
	//Families	
	int addFamily(std::vector <std::string> family, int dpt) {
		try
		{
			std::string strDpt;
						
			switch (dpt) {
			case 1:
				strDpt = "Dpt1";
				break;
			case 2:
				strDpt = "Dpt2";
				break;
			case 3:
				strDpt = "Dpt3";
				break;
			case 4:
				strDpt = "Dpt4";
				break;
			case 5:
				strDpt = "Dpt5";
				break;
			case 6:
				strDpt = "Dpt6";
				break;
			case 7:
				strDpt = "Dpt7";
				break;
			case 8:
				strDpt = "Dpt8";
				break;
			case 9:
				strDpt = "Dpt9";
				break;
			case 10:
				strDpt = "Dpt10";
				break;
			default:
				return _INVALID_DEPARTMENT_;
			};
				
			std::vector <std::string> fieldVector = {
			"Code",
			"Name",
			strDpt
			};

			family.push_back("1");
			
			int err = sq.insert("mbd", "families", fieldVector, family);

			if (err == _EXISTING_KEYCODE_) {
				sq.update("mbd", "families", fieldVector, family, "Code = " + family[0]);				
				return _FAMILY_MODIFIED_;
			}			
			return _FAMILY_ADDED_;			
		}
		catch (std::exception& e)
		{			
			return _FAMILY_NOT_ADDED_;
		}
	}
	int deleteFamily(int id) {
		try
		{
			std::string dInf = "Code = " + std::to_string(id);
			int err =sq.deleteSQL("mbd", "families", dInf);			
			LOG("deleteSQL: " + std::to_string(err));
			if (err == _SUCCESS_){
				return _FAMILY_REMOVED_;
			}
			return _FAMILY_NOT_REMOVED_;
		} catch (std::exception& e){
			return _EXCEPTION_ERROR_;
		}
	}

	//Clients
	int addClient(std::vector <std::string> valueVector) {
		try
		{
			std::vector <std::string> fieldVector;
			sq.getTableFields(fieldVector, "mbd", "customers");

			sq.insert("mbd", "customers", fieldVector, valueVector);

			if (sq.insert("mbd", "customers", fieldVector, valueVector) == _EXCEPTION_ERROR_) {
				sq.update("mbd", "families", fieldVector, valueVector, "Code = " + valueVector[0]);
				return _CLIENT_MODIFIED_;
			}
			return _CLIENT_ADDED_;
		} catch (std::exception& e)
		{
			return _CLIENT_NOT_ADDED_;
		}
	}
	int deleteClient(int id) {
		try
		{
			std::string dInf = "Code = " + std::to_string(id);
			sq.deleteSQL("mbd", "customers", dInf);
			return _CLIENT_REMOVED_;
		}
		catch (std::exception& e)
		{
			return _CLIENT_NOT_REMOVED_;
		}
	}

	//Vendors
	int addVendor(std::vector <std::string> valueVector) {
		std::vector <std::string> fieldVector;
		sq.getTableFields(fieldVector, "mbd", "vendors");

		sq.insert("mbd", "vendors", fieldVector, valueVector);

		if (sq.insert("mbd", "vendors", fieldVector, valueVector) == _EXCEPTION_ERROR_) {
			sq.update("mbd", "vendors", fieldVector, valueVector, "Code = " + valueVector[0]);
		}
		return _SUCCESS_;
	}
	int deleteVendor(int id) {
		std::string dInf = "Code = " + std::to_string(id);
		sq.deleteSQL("mbd", "vendors", dInf);
		return _SUCCESS_;
	}

	//Departments
	int addDepartment(std::vector <std::string> valueVector) {
		std::vector <std::string> fieldVector;
		sq.getTableFields(fieldVector, "mbd", "departments");

		sq.insert("mbd", "departments", fieldVector, valueVector);

		if (sq.insert("mbd", "departments", fieldVector, valueVector) == _EXCEPTION_ERROR_) {
			sq.update("mbd", "departments", fieldVector, valueVector, "Code = " + valueVector[0]);
		}
		return _SUCCESS_;
	}
	int deleteDepartment(int id) {
		std::string dInf = "Code = " + std::to_string(id);
		sq.deleteSQL("mbd", "departments", dInf);
		return _SUCCESS_;
	}
	int addDepartmentHeader(std::string header, int opt, int Code) {

		std::vector<std::string>fieldValueVector;
		fieldValueVector.push_back("Text1 = '" + header + "'");

		sq.update("mbd", "departments", fieldValueVector, "Code = " + std::to_string(Code));

		return _SUCCESS_;

	}

	//Tares
	int addTare(std::vector <std::string> valueVector) {
		std::vector <std::string> fieldVector;
		sq.getTableFields(fieldVector, "mbd", "tares");

		sq.insert("mbd", "tares", fieldVector, valueVector);

		if (sq.insert("mbd", "tares", fieldVector, valueVector) == _EXCEPTION_ERROR_) {
			sq.update("mbd", "tares", fieldVector, valueVector, "Code = " + valueVector[0]);
		}
		return _SUCCESS_;
	}
	int deleteTare(int id) {
		std::string dInf = "Code = " + std::to_string(id);
		sq.deleteSQL("mbd", "tares", dInf);
		return _SUCCESS_;
	}

	//Vats
	int addVats(std::vector <std::string> valueVector) {
		std::vector <std::string> fieldVector;
		sq.getTableFields(fieldVector, "mbd", "vats");

		sq.insert("mbd", "vats", fieldVector, valueVector);

		if (sq.insert("mbd", "vats", fieldVector, valueVector) == _EXCEPTION_ERROR_) {
			sq.update("mbd", "vats", fieldVector, valueVector, "Code = " + valueVector[0]);
		}
		return _SUCCESS_;
	}
	int deleteVats(int id) {
		std::string dInf = "Code = " + std::to_string(id);
		sq.deleteSQL("mbd", "vats", dInf);
		return _SUCCESS_;
	}

	//Scales
	int addScale(std::vector <std::string> valueVector) {
		std::vector <std::string> fieldVector;
		sq.getTableFields(fieldVector, "mbd", "scales");

		sq.insert("mbd", "scales", fieldVector, valueVector);

		if (sq.insert("mbd", "scales", fieldVector, valueVector) == _EXCEPTION_ERROR_) {
			sq.update("mbd", "scales", fieldVector, valueVector, "MAC = " + valueVector[0]);
		}
		return _SUCCESS_;
	}
	int deleteScale(int id) {
		std::string dInf = "MAC = " + std::to_string(id);
		sq.deleteSQL("mbd", "scales", dInf);
		return _SUCCESS_;
	}
}

