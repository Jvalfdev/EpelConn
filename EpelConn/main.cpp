//Local includes
#include "main.h"


#define LOG(x) std::cout << x << std::endl


int main(void)
{
	//Variables initialization
	SQL sql;
	std::string p_Ip;
	std::string p_Port;
	std::string p_User;
	std::string p_Pass;
	std::string p_Db;
	std::string p_Table;
	int p_Choice;
	int wrm = 1;
	std::vector<std::string> p_DbList;
	std::vector <std::string> p_TableList;
	std::vector <std::string> p_ColumnList;
	



	//Interface starting
	LOG("IP address: ");
	std::getline(std::cin, p_Ip);
	LOG("Port: ");
	std::getline(std::cin, p_Port);
	LOG("User: ");
	std::getline(std::cin, p_User);
	LOG("Password: ");
	std::getline(std::cin, p_Pass);
	
	//SQL connection
	sql.connect(p_Ip, p_Port, p_User, p_Pass);
	if (sql.connect(p_Ip, p_Port, p_User, p_Pass) == 0)
	{
		LOG("Connection successful");

		sql.getDatabaseList(p_DbList);
		for (int i = 0; i < p_DbList.size(); i++)
		{
			LOG(p_DbList[i]);
		}
		
		
		
		
		LOG("Choose what you want: ");
		LOG("1 - Query");
		LOG("2 - Insert");
		LOG("3 - Update");
		LOG("4 - Delete");
		LOG("5 - Create database");
		LOG("0 - Exit");
		
		std::cin >> p_Choice;
		do {
			switch (p_Choice) 
			{
			case 1:
				LOG("1 - Show Database list");
				LOG("2 - Show Table list");
				LOG("3 - Show Table content");
				LOG("4 - Show Table content with filter");
				int p_Choice2;
				std::cin >> p_Choice2;


				switch (p_Choice2)
				{
				case 1:

					sql.getDatabaseList(p_DbList);
					for (int i = 0; i < p_DbList.size(); i++)
					{
						LOG(p_DbList[i]);
					}
					break;

				case 2:

					LOG("Select Database");
					std::cin >> p_Db;



					sql.getTableList(p_TableList, p_Db);
					for (int i = 0; i < p_TableList.size(); i++)
					{
						LOG(p_TableList[i]);
					}
					break;
				case 3:
					LOG("Select db: ");
					std::cin >> p_Db;
					LOG("Select table: ");
					std::cin >> p_Table;

					sql.getTableFields(p_ColumnList, p_Db, p_Table);
					for (int i = 0; i < p_ColumnList.size(); i++)
					{
						LOG(p_ColumnList[i]);
					}
					break;


				default:
					LOG("Wrong choice");
					break;
				}



				break;
			case 2:
				/*LOG("Insert: ");
				std::getline(std::cin, l_query[0]);
				sql.insert(l_query[0]);
				break;*/
			case 3:
				/*LOG("Update: ");
				std::getline(std::cin, l_query[0]);
				sql.update(l_query[0]);
				break;*/
			case 4:
				/*LOG("Delete: ");
				std::getline(std::cin, l_query[0]);
				sql.delete_query(l_query[0]);
				break;*/
			case 5:
				LOG("Create database: ");
				p_Db.clear();
				std::getline(std::cin, p_Db);
				sql.createDatabase(p_Db);
				break;
			case 0:
				wrm = 0;
				break;
			default:
				LOG("Invalid choice");
				break;
			}
			
		} while (wrm = 1);		
		
		
	}
	else
	{
		LOG("Connection failed");
		
	}
	
	
	
	
	
}

