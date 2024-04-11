#include "SerialCom.h"


Serial_port::Serial_port(char* com)
{
    ret = 0;
    status = { 0 };
    connected = 0;

    h_com = CreateFileA(static_cast<LPCSTR>(com), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


    DWORD errMsg = GetLastError();
    if (errMsg == 2)
    {
        printf("Error com\n");
    }
    else if (errMsg == 5)
    {
        printf("Com Already Using\n");
    }
    else if (errMsg == 0)
    {
        DCB dcb_param = { 0 };
        if (!(GetCommState(h_com, &dcb_param)))
        {
            dcb_param.BaudRate = CBR_9600;
            dcb_param.ByteSize = 8;
            dcb_param.StopBits = ONESTOPBIT;
            dcb_param.Parity = NOPARITY;
            dcb_param.fDtrControl = DTR_CONTROL_ENABLE;
            if (!SetCommState(h_com, &dcb_param))
            {
                std::cout << "Coult not set Serial port parameters " << std::endl;
            }
            else
            {
                printf("Connected");
                connected = true;
                PurgeComm(h_com, PURGE_RXCLEAR | PURGE_TXCLEAR);
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
        CloseHandle(h_com);
    }


}

int Serial_port::Read_Serial(char* buffer, unsigned int size)
{
    DWORD bytesRead;
    unsigned int toread = 0;

    ClearCommError(h_com, &ret, &status);

    if (status.cbInQue > 0) toread = size;
    else toread = status.cbInQue;

    if (ReadFile(h_com, buffer, toread, &bytesRead, NULL)) return bytesRead;

    return 0;

}


bool Serial_port::isConnected() { return connected; }