//Local includes
#include "main.h"





int main(void)
{
	
	SQL sql;
	sql.setIp("127.0.0.1");
	sql.setPort("3306");
	sql.setUser("root");
	sql.setPass("1234");	
	
	sql.setDatabase("mysql");
	sql.setTable("doggo_info");
	sql.setField("Name");
	std::string fld = sql.getField();
	sql.setValue("5");

	
	
	std::vector <std::string> vectorQuery{ "INSERT", " ", "INTO", " ", sql.getTable(), " (", ") ", "VALUES", " (", ");"};
	std::string query;
	vectorQuery.insert(vectorQuery.begin() + 6, sql.getField());
	vectorQuery.insert(vectorQuery.begin() + 10, sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 11, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 12, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 13, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 14, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 15, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 16, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 17, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 18, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 19, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 20, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 21, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 22, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 23, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 24, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 25, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 26, ", " + sql.getValue());
	vectorQuery.insert(vectorQuery.begin() + 27, ", " + sql.getValue());


	for (int x = 0; x < vectorQuery.size(); x++)
	{
		query.append(vectorQuery[x]);
	};
	
	std::cout << query << std::endl;
	

	
	
	
	
	
}
