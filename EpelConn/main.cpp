//Local includes
#include "main.h"



#define LOG(x) std::cout << x << std::endl
#define LOGs(x) std::cout << x ;

#define _IP "10.8.0.104"
#define _PORT "3306"

int main(void)
{
	
	LOG(XS::connect(_IP, _PORT));
	LOG(XS::getStatus());
	
    
    
}


