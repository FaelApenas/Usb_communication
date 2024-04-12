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

char content[] = "1"; 

int main()
{
    Serial_port Stm_nucleo(port,CBR_9600);

    if (Stm_nucleo.isConnected())
    {
        std::cout << "Connected to " << port << std::endl;

        for (int i = 0; i < 20; i++) 
        {
            Stm_nucleo.Write_Serial(content, 1);
            std::cout << "Sending : " << content <<"to Nucleo board"<< std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        }
    }
    else
    {
        std::cin.get();
    }
    
    /* 
    while (Stm_nucleo.isConnected())
    {
        Stm_nucleo.Read_Serial(inputData, bytes_size);
        std::string inputValStr(inputData);
        std::cout << inputValStr << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    */



}