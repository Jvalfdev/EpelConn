#include "XS.h"
#include <filesystem>

#define LOG(x) std::cout << x << std::endl

SQL sq;




namespace XS
{
	//Connection Methods
	int connect(std::string ip, std::string port) {

		std::string user = "";
		std::string password = "";
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

	
	//Get Time function
	std::string CurrentDate()
	{
		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		char buf[16] = { 0 };
		std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));

		return std::string(buf);
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
	std::vector<std::vector<std::string>> getLastTicketOrdVector() {
		std::vector <std::string> lastTicketOrdHeader;
		std::vector<std::vector<std::string>>  lastTicketOrdLines;
		std::vector<std::vector<std::string>> finalVector;
		std::string queryHeader;
		std::string queryLines;
		
		queryHeader = "SELECT * FROM htickets WHERE Captured IS NULL ORDER BY Id ASC LIMIT 1";
		
		
		sq.query("mbd", queryHeader, lastTicketOrdHeader);
		
		queryLines = "SELECT * FROM ltickets WHERE IdHTicket =  '" + lastTicketOrdHeader[0] + "'";

		
		sq.v_query("mbd", queryLines, lastTicketOrdLines);
		
		sq.update("mbd", "htickets", {"Captured"}, {"*"}, "Id = " + lastTicketOrdHeader[0]);
		
		
		
		finalVector.push_back(lastTicketOrdHeader);

		for (int i = 0; i < lastTicketOrdLines.size(); i++) {
			finalVector.push_back(lastTicketOrdLines[i]);
		}
		
		return finalVector;
	}
	int getLastTicketOrd() {
		std::vector<std::vector<std::string>> vct;
		std::string name;
		int ctr = 0;
		vct = getLastTicketOrdVector();
		bool l_bGood = true;
		
		
		std::filesystem::create_directory("Not_orderer_tickets");
		

		std::ifstream myfile1;		

	
		do {
			if (ctr == 0) {
				name = "Not_orderer_tickets/ticket" + vct[0][0] + ".txt";
			}
			else {
				name = "Not_orderer_tickets/ticket" + vct[0][0] + "_" + std::to_string(ctr) + ".txt";
			}
			
			myfile1.open(name, std::ifstream::in);
			
			l_bGood = myfile1.good();
			ctr++;
		} while (l_bGood);		
		
		std::ofstream myfile(name);

		if (myfile.is_open())
		{
			for (int i = 0; i < vct.size(); i++) {
				for (int j = 0; j < vct[i].size(); j++) {
					myfile << vct[i][j] << " ";
				}
				myfile << "\n";
			}
			myfile.close();
			return _SUCCESS_;
		}
		else {
			return _FAILED_;
		}
		
	}
	std::vector<std::vector<std::string>> getTicket(int id) {
		std::vector <std::string> ticketHeader;
		std::vector<std::vector<std::string>>  ticketLines;
		std::vector<std::vector<std::string>> finalVector;
		std::string queryHeader;
		std::string queryLines;
		
		queryHeader = "SELECT * FROM htickets WHERE Id = " + std::to_string(id);
		
		
		sq.query("mbd", queryHeader, ticketHeader);
		
		queryLines = "SELECT * FROM ltickets WHERE IdHTicket =  '" + ticketHeader[0] + "'";

		
		sq.v_query("mbd", queryLines, ticketLines);
		
		
		
		finalVector.push_back(ticketHeader);

		for (int i = 0; i < ticketLines.size(); i++) {
			finalVector.push_back(ticketLines[i]);
		}
		
		return finalVector;
	}
	std::vector<std::vector<std::string>> getTicketsPausedVector() {
		std::vector<std::string> ticketHeader;
		std::vector<std::vector<std::string>>  ticketLines;
		std::vector<std::vector<std::string>> finalVector;
		std::string queryHeader;
		std::string queryLines;
		
		queryHeader = "SELECT * FROM htickets WHERE Status = 'S' ORDER BY Id ASC LIMIT 1";
			
		sq.query("mbd", queryHeader, ticketHeader);
		
		
		queryLines = "SELECT * FROM ltickets WHERE IdHTicket =  '" + ticketHeader[0] + "'";				
	    sq.v_query("mbd", queryLines, ticketLines);
		
				
	}	
	int getTicketsPaused() {
		std::vector<std::vector<std::string>> ticketHeader;
		std::vector<std::vector<std::string>>  ticketLines;
		std::vector<std::vector<std::string>> finalVector;
		std::string queryHeader;
		std::string queryLines;
		std::string name;
		bool l_bGood = true;
		
		

		std::filesystem::create_directory("Paused_tickets");
		

		queryHeader = "SELECT * FROM htickets WHERE Status = 'C' AND Captured IS NULL ORDER BY Id ASC";
		
		

		sq.v_query("mbd", queryHeader, ticketHeader);
		for (int s = 0; s < ticketHeader.size(); s++) {
			sq.update("mbd", "htickets", {"Captured"}, {"*"}, "Id = " + ticketHeader[s][0]);
		}
		
		
		
		for (int i = 0; i < ticketHeader.size(); i++) {
			finalVector.clear();
			
			finalVector.push_back(ticketHeader[i]);
			
			queryLines = "SELECT * FROM ltickets WHERE IdHTicket =  '" + ticketHeader[i][0] + "'";
			ticketLines.clear();
			
			sq.v_query("mbd", queryLines, ticketLines);
			
			
			
			for (int j = 0; j < ticketLines.size(); j++) {
				finalVector.push_back(ticketLines[j]);
			}
			
			std::ifstream myfile1(name);
			
					
			name = "Paused_tickets/ticket_paused" + finalVector[0][0] + "-" + CurrentDate() + ".txt";
							
				

			std::ofstream myfile(name);

			if (myfile.is_open())
			{
				for (int a = 0; a < finalVector.size(); a++) {
					for (int s = 0; s < finalVector[a].size(); s++) {
						myfile << finalVector[a][s] << " ";
					}
					myfile << "\n";
				}
				myfile.close();
				
			}
			else {
				return _FAILED_;
			}
			
		}
		return _SUCCESS_;
		
	}
	int getTotalItems() {
		//Variables Declarations
		std::vector<std::vector<std::string>> art;
		
		std::string articleQuery;
		
		std::string articleName;
		
		
		std::filesystem::create_directory("Totals");
		//Articles
		std::filesystem::create_directory("Totals\\Article_totals");
		articleQuery = "SELECT * FROM totalitems ORDER BY Date ASC";
		sq.v_query("mbd", articleQuery, art);
		LOG(art.size());

		articleName = "Totals/TotalItems/totalitems -" + CurrentDate() + ".txt";



		std::ofstream myitemfile(articleName);
		

		if (myitemfile.is_open())
		{
			for (int a = 0; a < art.size(); a++) {
				for (int s = 0; s < art[a].size(); s++) {
					myitemfile << art[a][s] << " ";
				}
				myitemfile << "\n";
			}
			myitemfile.close();
			
			
		}
		else {
			return _FAILED_;
		}
		
		
		return _SUCCESS_;
	}
	int getTotalCustomers() {
		std::vector<std::vector<std::string>> vend;
		std::string vendorQuery;
		std::string vendorName;
		//Customers
		std::filesystem::create_directory("Totals");
		
		std::filesystem::create_directory("Totals\\TotalCustomers");
		
		vendorQuery = "SELECT * FROM totalcustomers ";
		sq.v_query("mbd", vendorQuery, vend);

		vendorName = "Totals/TotalCustomers/totalcustomers -" + CurrentDate() + ".txt";



		std::ofstream myvendorfile(vendorName);


		if (myvendorfile.is_open())
		{
			for (int a = 0; a < vend.size(); a++) {
				for (int s = 0; s < vend[a].size(); s++) {
					myvendorfile << vend[a][s] << " ";
				}
				myvendorfile << "\n";
			}
			myvendorfile.close();


		}
		else {
			return _FAILED_;
		}
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
		{
			std::string dInf = "Code = " + std::to_string(Code);
			LOG(sq.deleteSQL("mbd", "items", dInf));
			return _ARTICLE_REMOVED_;
		}
		catch (std::exception& e)
		{
			return _ARTICLE_NOT_REMOVED_;
		}
	}
	int setDescriptionArticle(std::vector <std::string> descriptions, int code) {
		try
		{
			std::vector <std::string> fieldVector = { "Text", "Text2" };
			sq.insert("mbd", "items", fieldVector, descriptions);
			return _ARTICLE_DESCRIPTION_SET_;
		}
		catch (std::exception& e)
		{
			return _ARTICLE_DESCRIPTION_NOT_SET_;
		}
	}
	int setTareArticle(double tare, double packingTare, int code) {
		int ctr = sq.update("mdb", "items", { "Tare", "PackingTare" }, { std::to_string(tare), std::to_string(packingTare) }, "Code = " + std::to_string(code));
		if (ctr == _SUCCESS_) {
			return _ARTICLE_TARE_ADDED_;
		}
		else {
			return _ARTICLE_TARE_NOT_ADDED_;
		}

	}
	int deleteTareArticle(int code) {
		int ctr = sq.update("mdb", "items", { "Tare", "PackingTare" }, { "0", "0" }, "Code = " + std::to_string(code));
		if (ctr == _SUCCESS_) {
			return _ARTICLE_TARE_REMOVED_;
		}
		else {
			return _ARTICLE_TARE_NOT_REMOVED_;
		}
	}
	int setArticleTraceability(int code, int traceability) {
		try {
			int ctr = sq.update("mdb", "items", { "Traceability" }, { std::to_string(traceability) }, "Code = " + std::to_string(code));
			if (ctr == _SUCCESS_) {
				return _ARTICLE_TRACEABILITY_SET_;
			}
			else {
				return _ARTICLE_TRACEABILITY_NOT_SET_;
			}
		} catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}		
	}
	int setArticleNutInfo(int code, int nutinfo) {
		try {
			int ctr = sq.update("mdb", "items", { "NutInfo" }, { std::to_string(nutinfo) }, "Code = " + std::to_string(code));
			if (ctr == _SUCCESS_) {
				return _ARTICLE_NUTINFO_SET_;
			}
			else {
				return _ARTICLE_NUTINFO_NOT_SET_;
			}
		} catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
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
			int err = sq.deleteSQL("mbd", "families", dInf);
			LOG("deleteSQL: " + std::to_string(err));
			if (err == _SUCCESS_) {
				return _FAMILY_REMOVED_;
			}
			return _FAMILY_NOT_REMOVED_;
		}
		catch (std::exception& e) {
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
		}
		catch (std::exception& e)
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
	int addVendor(int vendorCode, std::string vendorName) {
		try
		{
			std::vector <std::string> fieldVector = {
			"Code",
			"Name",
			};

			std::vector <std::string> vendor = {
				std::to_string(vendorCode),
				vendorName
			};

			int err = sq.insert("mbd", "vendors", fieldVector, vendor);

			if (err == _EXISTING_KEYCODE_) {
				sq.update("mbd", "vendors", fieldVector, vendor, "Code = " + std::to_string(vendorCode));
				return _VENDOR_MODIFIED_;
			}
			return _VENDOR_ADDED_;
		}
		catch (std::exception& e) {
			return _VENDOR_NOT_ADDED_;
		}

	}
	int deleteVendor(int id) {
		try {
			std::string dInf = "Code = " + std::to_string(id);
			int ctr = sq.deleteSQL("mbd", "vendors", dInf);
			if (ctr == _SUCCESS_) {
				return _VENDOR_REMOVED_;
			}
			return _VENDOR_REMOVED_;
		}
		catch (std::exception& e) {
			return _VENDOR_NOT_REMOVED_;
		}
	}

	//Departments
	int addDepartment(int code, int counter, std::string name) {
		try {
			std::vector <std::string> fieldVector = {
				"Code",
				"Counter",
				"Name"
			};
			std::vector <std::string> valueVector = {
			std::to_string(code),
			std::to_string(counter),
			name
			};

			int ctr = sq.insert("mbd", "departments", fieldVector, valueVector);

			if (ctr == _EXISTING_KEYCODE_) {
				
				return _EXISTING_DEPARTMENT_;
			}
			else if (ctr == _SUCCESS_) {
				return _DEPARTMENT_ADDED_;
			}
			else {
				return _DEPARTMENT_NOT_ADDED_;
			}
		}
		catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}

	}
	int deleteDepartment(int code, int counter) {
		try {

			std::string strCode = "Code = " + std::to_string(code);
			std::string strCounter = "Counter = " + std::to_string(counter);
			std::string whr = strCode + " AND " + strCounter;
			LOG(whr);
			int ctr = sq.deleteSQL("mbd", "departments", whr);
			if (ctr == _SUCCESS_) {
				return _DEPARTMENT_REMOVED_;
			}
			else {
				return _DEPARTMENT_NOT_REMOVED_;
			};
		}
		catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}

	}
	int addDepartmentHeader(std::string header, int opt, int code, int counter) {
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
				std::to_string(code),
				header
			};

			int ctr = sq.update("mbd", "departments", fieldVector, valueVector, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));
			
			if (ctr == _SUCCESS_) {
				return _DEPARTMENT_HEADER_ADDED_;
			}
			else {
				return _DEPARTMENT_HEADER_NOT_ADDED_;
			}


			
		}
		catch (std::exception& e)
		{
			return _EXCEPTION_ERROR_;
		}

	}
	int deleteDepartmentHeader(int code, int counter, int header) {
		try
		{
			if (header == 0) {
				sq.update("mbd", "departments", { "Text1", "Text2", "Text3", "Text4", "Text5" }, { " ", " ", " ", " ", " " }, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));
				return _DEPARTMENT_HEADER_ALL_REMOVED_;
			}
			std::string strDpt;
			strDpt.clear();
			switch (header) {
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

			int ctr = sq.update("mbd", "departments", { strDpt }, { " " }, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));

			if (ctr == _SUCCESS_) {
				return _DEPARTMENT_HEADER_REMOVED_;
			}
			else {
				return _DEPARTMENT_HEADER_NOT_REMOVED_;
			}
		}
		catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}
	}
	int addDepartmentFooter(std::string footer, int opt, int code, int counter) {

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
					std::to_string(code),
					footer
				};

				int ctr = sq.update("mbd", "departments", fieldVector, valueVector, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));
				
				if (ctr == _SUCCESS_) {
					return _DEPARTMENT_FOOTER_ADDED_;
				}
				else {
					return _DEPARTMENT_FOOTER_NOT_ADDED_;
				}				
			}
			catch (std::exception& e)
			{
				return _EXCEPTION_ERROR_;
			}
		}
	int deleteDepartmentFooter(int code, int counter, int footer) {
		try
		{
			if (footer == 0) {
				sq.update("mbd", "departments", { "Text6", "Text7", "Text8", "Text9", "Text10"}, {" ", " ", " ", " ", " "}, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));
				return _DEPARTMENT_FOOTER_ALL_REMOVED_;
			}
			std::string strDpt;
			strDpt.clear();
			switch (footer) {
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

			int ctr = sq.update("mbd", "departments", { strDpt }, { " " }, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));

			if (ctr == _SUCCESS_) {
				return _DEPARTMENT_FOOTER_REMOVED_;
			}
			else {
				return _DEPARTMENT_FOOTER_NOT_REMOVED_;
			}
		}
		catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}
	}
	int addDepartmentLabel(std::string label, int opt, int code, int counter) {

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
					std::to_string(code),
					label
				};

				int ctr = sq.update("mbd", "departments", fieldVector, valueVector, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));
				
				if (ctr == _SUCCESS_) {
					return _DEPARTMENT_LABEL_ADDED_;
				}
				else {
					return _DEPARTMENT_LABEL_NOT_ADDED_;
				}

			}
			catch (std::exception& e)
			{
				return _EXCEPTION_ERROR_;
			}


		}
	int deleteDepartmentLabel(int code, int counter, int label) {
		try
		{
			if (label == 0) {
				sq.update("mbd", "departments", { "LabelText1", "LabelText2", "LabelText3", "LabelText4", "LabelText5" }, { " ", " ", " ", " ", " " }, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));
				return _DEPARTMENT_LABEL_ALL_REMOVED_;
			}
			std::string strDpt;
			strDpt.clear();
			switch (label) {
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

			int ctr = sq.update("mbd", "departments", { strDpt }, { " " }, "Code = " + std::to_string(code) + " AND Counter = " + std::to_string(counter));

			if (ctr == _SUCCESS_) {
				return _DEPARTMENT_LABEL_REMOVED_;
			}
			else {
				return _DEPARTMENT_LABEL_NOT_REMOVED_;
			}
		}
		catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}
	}

	//Tares
	int addTare(int code, std::string name, double tare) {
		try {
			std::vector <std::string> fieldVector = {
				"Code",
				"Name",
				"Tare"
			};
			std::vector <std::string> valueVector = {
				std::to_string(code),
				name,
				std::to_string(tare)
			};
			sq.getTableFields(fieldVector, "mbd", "tares");

			int ctr = sq.insert("mbd", "tares", fieldVector, valueVector);

			if (ctr == _EXISTING_KEYCODE_) {
				sq.update("mbd", "tares", fieldVector, valueVector, "Code = " + valueVector[0]);
				return _TARE_MODIFIED_;
			}
			else if (ctr == _SUCCESS_) {
				return _TARE_ADDED_;
			}
			else {
				return _TARE_NOT_ADDED_;
			}

		}
		catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}
	}		
	int deleteTare(int id) {
		try {
			std::string dInf = "Code = " + std::to_string(id);
			int ctr = sq.deleteSQL("mbd", "tares", dInf);
			if (ctr == _SUCCESS_) {
				return _TARE_REMOVED_;
			}
			else {
				return _TARE_NOT_REMOVED_;
			}			
			
		} catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}			
	}
	
	//Vats
	int addVats(int code, std::string name, double percent) {
		try {
			std::vector <std::string> fieldVector;
			sq.getTableFields(fieldVector, "mbd", "vats");
			
			std::vector <std::string> valueVector = {
				std::to_string(code),
				name,
				std::to_string(percent)
			};

			int err = sq.insert("mbd", "vats", fieldVector, valueVector);

			if (err == _EXCEPTION_ERROR_) {
				sq.update("mbd", "vats", fieldVector, valueVector, "Code = " + valueVector[0]);
				return _VAT_MODIFIED_;
			} else if (err == _SUCCESS_) {
				return _VAT_ADDED_;
			} else {
				return _VAT_NOT_ADDED_;
			}
			
		} catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}
			
	}
	int deleteVats(int id) {
		try {
			std::string dInf = "Code = " + std::to_string(id);
			int ctr = sq.deleteSQL("mbd", "vats", dInf);
			if (ctr == _SUCCESS_) {
				return _VAT_REMOVED_;
			}
			else {
				return _VAT_NOT_REMOVED_;
			}			
		} catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}
			
	}

	//Scales
	
	int addScaleHeader(std::string header, int opt, int counter, int number) {
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

				int ctr = sq.update("mbd", "scales", fieldVector, valueVector, "Counter =  '" + std::to_string(counter) + "'" + " AND  Number = " + "'" + std::to_string(number) + "'");

				if (ctr == _SUCCESS_) {
					return _SCALE_HEADER_ADDED_;
				}
				else {
					return _SCALE_HEADER_NOT_ADDED_;
				}

			}catch (std::exception& e)
			{
				return _EXCEPTION_ERROR_;
			}

		}
	int deleteScaleHeader(int counter, int number, int header) {
		try
		{
			if (header == 0) {
				sq.update("mbd", "scales", { "Header1", "Header2", "Header3", "Header4", "Header5" }, { " ", " ", " ", " ", " " }, "Code = " + std::to_string(counter) + " AND Counter = " + std::to_string(number));
				return _DEPARTMENT_LABEL_ALL_REMOVED_;
			}
			std::string strDpt;
			strDpt.clear();
			switch (header) {
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

			int ctr = sq.update("mbd", "scales", { strDpt }, { " " }, "Counter = " + std::to_string(counter) + " AND Number = " + std::to_string(number));

			if (ctr == _SUCCESS_) {
				return _SCALE_HEADER_REMOVED_;
			}
			else {
				return _SCALE_HEADER_NOT_REMOVED_;
			}
		}
		catch (std::exception& e) {
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

				int ctr = sq.update("mbd", "scales", fieldVector, valueVector, "Number =  '" + std::to_string(number) + "'" + " AND  Counter = " + "'" + std::to_string(dpt) + "'");

				if (ctr == _SUCCESS_) {
					return _SCALE_FOOTER_ADDED_;
				}
				else {
					return _SCALE_FOOTER_NOT_ADDED_;
				}
				
			}
			catch (std::exception& e)
			{
				return _EXCEPTION_ERROR_;
			}

		}
	int deleteScaleFooter(int counter, int number, int footer) {
		try
		{
			if (footer == 0) {
				sq.update("mbd", "departments", { "Footer1", "Footer2", "Footer3", "Footer4", "Footer5" }, { " ", " ", " ", " ", " " }, "Counter = " + std::to_string(counter) + " AND Number = " + std::to_string(number));
				return _DEPARTMENT_LABEL_ALL_REMOVED_;
			}
			std::string strDpt;
			strDpt.clear();
			switch (footer) {
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

			int ctr = sq.update("mbd", "scales", { strDpt }, { " " }, "Counter = " + std::to_string(counter) + " AND Number = " + std::to_string(number));

			if (ctr == _SUCCESS_) {
				return _SCALE_FOOTER_REMOVED_;
			}
			else {
				return _SCALE_FOOTER_NOT_REMOVED_;
			}
		}
		catch (std::exception& e) {
			return _EXCEPTION_ERROR_;
		}
	}

	//Traceability
	int addTraceability(std::string name, std::string text, int code) {
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
			}
			catch (std::exception& e)
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
			}
			catch (std::exception& e)
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


