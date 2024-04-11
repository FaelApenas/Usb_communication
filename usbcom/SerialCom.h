#include <iostream>
#include <windows.h>

#define Wait_time 1000
#define bytes_size 21

class Serial_port
{
private:
	HANDLE  handle_com;
	bool    connected;
	COMSTAT status;
	DWORD   err;
	
public:
	Serial_port(char* com);
	~Serial_port();

	int Read_Serial(char* buffer, unsigned int size);
	bool Write_Serial(char* buffer, unsigned int size);
	void CustomSyntax(const std::string& syntax_type); 
	bool isConnected();



};