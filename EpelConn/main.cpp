//Local includes
#include "main.h"



#define LOG(x) std::cout << x << std::endl
#define LOGs(x) std::cout << x ;

#define _IP "10.8.0.104"
#define _PORT "3306"

int main(void)
{
	std::vector<std::string> article = {
		"44", 
		"TestArticle",
		"",
		"",
		"",
		"",
		"",
		"44",
		"",
		"",
		"",
		""		
	};
	LOG(XS::connect(_IP, _PORT));
	LOG(XS::getStatus());
	LOG(XS::addArticle(article));	
	LOG(XS::deleteArticle(44));
}

