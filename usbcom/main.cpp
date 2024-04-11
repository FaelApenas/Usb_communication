#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "SerialCom.h"
#include<iomanip>
#include <thread>
#include <string>

char inputData[bytes_size];
double inputdbl = 0.0;


char comPort[] = "COM5";
char* port = comPort;


int main()
{
    Serial_port Stm_nucleo(port);

    if (Stm_nucleo.isConnected())
    {
        std::cout << "Connected to " << port << std::endl;
    }
    else
    {
        std::cin.get();
    }

    while (Stm_nucleo.isConnected())
    {
        Stm_nucleo.Read_Serial(inputData, bytes_size);
        std::cout << inputData << std::endl;
        std::chrono::milliseconds(500);

    }




}