#include <iostream>
#include <windows.h>

#define Wait_time 2000
#define bytes_size 7

class Serial_port
{
private:
	HANDLE  h_com;
	bool    connected;
	COMSTAT status;
	DWORD   ret;

public:
	Serial_port(char* com);
	~Serial_port();

	int Read_Serial(char* buffer, unsigned int size);
	bool Write_Serial(char* buffer, unsigned int size);
	bool isConnected();



};