


#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <string.h> 

#define Wait_time 1000
#define bytes_size 21

class Serial_port
{
private:
	HANDLE  handle_com;
	bool    connected;
	COMSTAT status;
	DWORD   err;
	std::string syntax_name_;
	char front_delimiter_;
	char end_delimiter_;
	
public:
	Serial_port(char* com);
	~Serial_port();

	int Read_Serial(char* buffer, unsigned int size);
	bool Write_Serial(char* buffer, unsigned int size);
	void CustomSyntax(const std::string& syntax_type); 
	bool isConnected();
	bool check_com_format(char* com);
	 char* handle_higher_com(char* com);


};



