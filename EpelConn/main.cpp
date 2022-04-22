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
        "C/ punto net, 3", //Dirección	
        "Madrid", //Ciudad		
        "28805", //Código postal		
        "España", //País		
        "652114558",	//Teléfono	
        "", //Teléfono 2 (Vacío)	
        "grupoepelsa.com", //Página web	
        "", //Email (Vacío)
        "" //Descuento (Vacío)
	};
	LOG(XS::connect(_IP, _PORT));
	LOG(XS::getStatus());
	LOG(XS::addCustomer(customer));
}

