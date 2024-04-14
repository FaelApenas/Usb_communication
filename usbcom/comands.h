#pragma once

#include <iostream>
#include <string>
#include <windows.h>

enum command 
{
	UNKNOWN,
	TESTE, 
	HELP,
	CONFIG_COM,
	READ_SERIAL, 
	WRITE_SERIAL 
};

struct config_com
{
	DWORD baud_rate;
	int wait_time;

};

std::string tolowercase(std::string s);
void help_command();
command get_command(const std::string input); 
void execute_command(command c); 

