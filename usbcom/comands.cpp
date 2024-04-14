#include "comands.h"



command get_command();


void execute_command(command c)
{    
	switch (c)
	{
	case UNKNOWN:
		std::cout << "Unknown command" << std::endl;
		break;
	case TESTE:
		std::cout << "Hello World" << std::endl;
		break;
	case HELP:
		help_command(); 
		break;
	case CONFIG_COM:
		std::cout << "Not implemented command" << std::endl;
		break;
	case READ_SERIAL:
		std::cout << "Not implemented command" << std::endl;
		break;
	case WRITE_SERIAL:
		std::cout << "Not implemented command" << std::endl;
		break;
	default:
		std::cout << "Unknown command" << std::endl;
		break;
	}
}

void help_command() 
{
	std::cout << "---List of commands---" << std::endl;
	std::cout << "CONFIG_COM, READ_SERIAL, WRITE_SERIAL" << std::endl;

}

void config_com_command() 
{
	int input_baud; 
	int input_waitTime; 
	std::cout << "--Config Command---" << std::endl; 

	std::cout << "Enter the  BaudRate : "; 
	std::cin >> input_baud;
	printf("\n"); 

	std::cout << "Enter the  Wait_time : ";
	std::cin >> input_waitTime;
	printf("\n");



}

command get_command(const std::string input) 
{
	if (input == "teste") {
		return TESTE; }
	else if (input == "help") { return HELP; }
	else if (input == "read_serial") { return READ_SERIAL; }
	else if (input == "write_serial") { return WRITE_SERIAL; }


}
