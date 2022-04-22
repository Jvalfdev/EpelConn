//Local includes
#include "main.h"



#define LOG(x) std::cout << x << std::endl
#define LOGs(x) std::cout << x ;

#define _IP "10.8.0.104"
#define _PORT "3306"

int main(void)
{
	std::vector<std::string> customer = {
        "25",  //Codigo (obligatorio)	
        "B4512547",   //CIF (obligatorio)	
        "Grupo Epelsa", //Nombre	
        "C/ punto net, 3", //Direcci�n	
        "Madrid", //Ciudad		
        "28805", //C�digo postal		
        "Espa�a", //Pa�s		
        "652114558",	//Tel�fono	
        "", //Tel�fono 2 (Vac�o)	
        "grupoepelsa.com", //P�gina web	
        "", //Email (Vac�o)
        "" //Descuento (Vac�o)
	};
	LOG(XS::connect(_IP, _PORT));
	LOG(XS::getStatus());
	LOG(XS::addCustomer(customer));
}

