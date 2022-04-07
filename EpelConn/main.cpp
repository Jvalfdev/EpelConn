//Local includes
#include "main.h"


#define LOG(x) std::cout << x << std::endl


int main(void)
{
	SQL sql;
	std::vector<std::string> l_query;

	sql.connect("127.0.0.1:3306", "root", "1234");
	sql.query("mysql", "doggo_info", "Name", l_query);
	
	
	for (int i = 0; i < l_query.size(); i++)
	{
		LOG(l_query[i]);
	}
	
	
}
