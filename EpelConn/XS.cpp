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
	int deleteTotals() {
		sq.deleteSQL("mbd", "totals");
		sq.deleteSQL("mbd", "totalcustomers");
		sq.deleteSQL("mbd", "totalitems");
		sq.deleteSQL("mbd", "totalpaymethods");
		sq.deleteSQL("mbd", "totalvats");
		sq.deleteSQL("mbd", "htickets");
		sq.deleteSQL("mbd", "ltickets");
		return _SUCCESS_;
	}	

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
	int setTareArticle(std::string tare, std::string packingTare, int Code) {
		sq.update("mdb", "items", { "Tare", "PackingTare" }, { tare, packingTare }, "Code = " + std::to_string(Code));
		return _SUCCESS_;
	}
	int deleteTareArticle(int Code) {
		sq.update("mdb", "items", { "Tare", "PackingTare" }, { "0", "0" }, "Code = " + std::to_string(Code));
		return _SUCCESS_;
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
	int addCustomer(std::vector <std::string> customer) {
		try
		{
			std::vector <std::string> fieldVector = {
				"Code",
				"CIF",
				"Name",
				"Address",
				"City",
				"ZIPCode",
				"Country",
				"Phone1",
				"Phone2",
				"Website",
				"Email",
				"Discount"
			};			

			int err = sq.insert("mbd", "customers", fieldVector, customer);

			if (err == _EXISTING_KEYCODE_) {
				sq.update("mbd", "customers", fieldVector, customer, "Code = " + customer[0]);
				return _CLIENT_MODIFIED_;
			}
			return _CLIENT_ADDED_;
		} catch (std::exception& e)
		{
			return _CLIENT_NOT_ADDED_;
		}
	}
	int deleteCustomer(int id) {
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
		try
		{
			std::string strDpt;
			strDpt.clear();
			switch (opt) {
			case 1:
				strDpt = "Text1";
				break;
			case 2:
				strDpt = "Text2";
				break;
			case 3:
				strDpt = "Text3";
				break;
			case 4:
				strDpt = "Text4";
				break;
			case 5:
				strDpt = "Text5";
				break;
			default:
				return _INVALID_DEPARTMENT_;
			};

			std::vector <std::string> fieldVector = {
				"Code",
				strDpt
			};

			std::vector <std::string> valueVector = {
				std::to_string(Code),
				header
			};

			sq.update("mbd", "departments", fieldVector, valueVector, "Code = " + valueVector[0]);



			return _SUCCESS_;
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}

	}
	int addDepartmentFooter(std::string footer, int opt, int Code) {

		try
		{
			std::string strDpt;
			strDpt.clear();
			switch (opt) {
			case 1:
				strDpt = "Text6";
				break;
			case 2:
				strDpt = "Text7";
				break;
			case 3:
				strDpt = "Text8";
				break;
			case 4:
				strDpt = "Text9";
				break;
			case 5:
				strDpt = "Text10";
				break;
			default:
				return _INVALID_DEPARTMENT_;
			};

			std::vector <std::string> fieldVector = {
				"Code",
				strDpt
			};

			std::vector <std::string> valueVector = {
				std::to_string(Code),
				footer
			};

			sq.update("mbd", "departments", fieldVector, valueVector, "Code = " + valueVector[0]);



			return _SUCCESS_;
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}


	}
	int addDepartmentLabel(std::string label, int opt, int Code) {

		try
		{
			std::string strDpt;
			strDpt.clear();
			switch (opt) {
			case 1:
				strDpt = "LabelText1";
				break;
			case 2:
				strDpt = "LabelText2";
				break;
			case 3:
				strDpt = "LabelText3";
				break;
			case 4:
				strDpt = "LabelText4";
				break;
			case 5:
				strDpt = "LabelText5";
				break;
			default:
				return _INVALID_DEPARTMENT_;
			};

			std::vector <std::string> fieldVector = {
				"Code",
				strDpt
			};

			std::vector <std::string> valueVector = {
				std::to_string(Code),
				label
			};

			sq.update("mbd", "departments", fieldVector, valueVector, "Code = " + valueVector[0]);



			return _SUCCESS_;
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}


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
	int addScaleHeader(std::string header, int opt, int dpt, int number) {
		try
		{
			std::string strDpt;
			strDpt.clear();
			switch (opt) {
			case 1:
				strDpt = "Header1";
				break;
			case 2:
				strDpt = "Header2";
				break;
			case 3:
				strDpt = "Header3";
				break;
			case 4:
				strDpt = "Header4";
				break;
			case 5:
				strDpt = "Header5";
				break;
			default:
				return _INVALID_DEPARTMENT_;
			};

			std::vector <std::string> fieldVector = {
				
				strDpt
			};

			std::vector <std::string> valueVector = {

				
				header
			};

			sq.update("mbd", "scales", fieldVector, valueVector, "Number =  '" + std::to_string(number) + "'" + " AND  Counter = " + "'" + std::to_string(dpt) + "'" );



			return _SUCCESS_;
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}

	}
	int addScaleFooter(std::string footer, int opt, int dpt, int number) {
		try
		{
			std::string strDpt;
			strDpt.clear();
			switch (opt) {
			case 1:
				strDpt = "Footer1";
				break;
			case 2:
				strDpt = "Footer2";
				break;
			case 3:
				strDpt = "Footer3";
				break;
			case 4:
				strDpt = "Footer4";
				break;
			case 5:
				strDpt = "Footer5";
				break;
			default:
				return _INVALID_DEPARTMENT_;
			};

			std::vector <std::string> fieldVector = {
				
				strDpt
			};

			std::vector <std::string> valueVector = {
				
				footer
			};

			sq.update("mbd", "scales", fieldVector, valueVector, "Number =  '" + std::to_string(number) + "'" + " AND  Counter = " + "'" + std::to_string(dpt) + "'");



			return _SUCCESS_;
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}

	}

	//Traceability
	int addTraceability(std::string name, std::string text, int code ) {
		try
		{
			std::vector <std::string> fieldVector = {
				"Code",
				"Name",
				"Info"
			};

			std::vector <std::string> valueVector = {
				std::to_string(code),
				name,
				text
			};

			int err = sq.insert("mbd", "traceability", fieldVector, valueVector);

			if (err == _EXISTING_KEYCODE_) {
				sq.update("mbd", "traceability", fieldVector, valueVector, "Code = " + std::to_string(code));
				return _TRACEABILITY_MODIFIED_;
			}
			return _TRACEABILITY_ADDED_;
		} catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}
	}
	int deleteTraceability(int code) {
		try
		{
			int con = sq.deleteSQL("mbd", "traceability", "Code = " + std::to_string(code));
			
			if (con == _SUCCESS_) {
				return _TRACEABILITY_REMOVED_;
			}
			else {
				return _TRACEABILITY_NOT_REMOVED_;
			}
		} catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}
		
		
	}

	//Nutritional info
	int addNutritionalInfo(std::string name, std::string text, int code) {
		try
		{
			std::vector <std::string> fieldVector = {
				"Code",
				"Name",
				"Info"
			};

			std::vector <std::string> valueVector = {
				std::to_string(code),
				name,
				text
			};

			int err = sq.insert("mbd", "nutritionalinfo", fieldVector, valueVector);

			if (err == _EXISTING_KEYCODE_) {
				sq.update("mbd", "nutritionalinfo", fieldVector, valueVector, "Code = " + std::to_string(code));
				return _NUTRITIONAL_MODIFIED_;
			}
			return _NUTRITIONAL_ADDED_;
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}
	}
	int deleteNutritionalInfo(int code) {
		try
		{
			int con = sq.deleteSQL("mbd", "nutritionalinfo", "Code = " + std::to_string(code));

			if (con == _SUCCESS_) {
				return _NUTRITIONAL_REMOVED_;
			}
			else {
				return _NUTRITIONAL_NOT_REMOVED_;
			}
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}
	}	
}

