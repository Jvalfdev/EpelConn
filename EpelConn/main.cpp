//Local includes
#include "main.h"





int main(void)
{
	
	SQL sql;
	sql.setIp("127.0.0.1");
	sql.setPort("3306");
	sql.setUser("root");
	sql.setPass("1234");	
	sql.connect();
	sql.setDatabase("mysql");
	sql.setTable("doggo_info");
	sql.setField("Name");
	std::string fld = sql.getField();
	sql.setValue("5");

	sql.fieldQuery();
	sql.query();
	

	
	
	
	
	
}
