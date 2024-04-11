#include "SerialCom.h"


Serial_port::Serial_port(char* com)
{
 
    err = 0;
    status = { 0 };
    connected = 0;
    std::string com_str = com; 
    
    handle_com = CreateFileA(static_cast<LPCSTR>(com), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


    DWORD errMsg = GetLastError();
    if (errMsg == 2)
    {
        printf("Com not found\n");
    }
    else if (errMsg == 5)
    {
        printf("Com Already Using\n");
    }
    else if (errMsg == 0)
    {
        DCB dcb_param = { 0 };
        if (!GetCommState(handle_com, &dcb_param)) printf("Failed to get the com parameters");

        else
        {
            dcb_param.BaudRate = CBR_9600;
            dcb_param.ByteSize = 8;
            dcb_param.StopBits = ONESTOPBIT;
            dcb_param.Parity = NOPARITY;
            dcb_param.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handle_com, &dcb_param))
            {
                std::cout << "Coult not set Serial port parameters " << std::endl;
            }
            else
            {
                connected = true;
                PurgeComm(handle_com, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(Wait_time);


            }


        }
    }


}



Serial_port::~Serial_port()
{
    if (connected == true)
    {
        connected = false;
        CloseHandle(handle_com);
    }


}

int Serial_port::Read_Serial(char* buffer, unsigned int size)
{
    DWORD bytesRead;
    char inc_msg[1]; 
    std::string complete_msg_inc; 
    unsigned int toread = 0;

    ClearCommError(handle_com, &err, &status);

    if (status.cbInQue > 0) toread = size;
    else toread = status.cbInQue;

    if (ReadFile(handle_com, buffer, toread, &bytesRead, NULL)) 
    {
        if()
    }

    return 0;

}


bool Serial_port::Write_Serial(char * buffer,unsigned int size) 
{
    DWORD bytesSent; 
    std::string buffer_str = buffer; 
    
    if (!WriteFile(handle_com, buffer, buffer_str.length(), &bytesSent, nullptr))
    {
        ClearCommError(handle_com,&err,&status); 
        return false;
    }
    else 
    {
        return true; 
    }

}
 


bool Serial_port::isConnected() { return connected; }