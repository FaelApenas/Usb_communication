#include "SerialCom.h"


Serial_port::Serial_port(char* com, DWORD baud_rate )
{
    if (!check_com_format(com)) 
    {
        printf("Com format not available ");
        return;
    } 
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
            dcb_param.BaudRate = baud_rate;
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

int Serial_port::Read_Serial(char *buffer, unsigned int size)
{
    DWORD bytesRead;
    unsigned int toread = 0;

    ClearCommError(handle_com, &err, &status);
        
    if (status.cbInQue > 0) 
    {
        if (status.cbInQue > size) toread = size;


        else toread = status.cbInQue;
    }

    if (ReadFile(handle_com, buffer, toread, &bytesRead, nullptr)) 
    {
        return bytesRead;
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
 
void Serial_port::CustomSyntax(const std::string& syntax_type)
{
    std::ifstream syntaxfile_exist("syntax_config.txt");

    if (!syntaxfile_exist)
    {
        std::ofstream syntaxfile;
        syntaxfile.open("syntax_config.txt");

        if (syntaxfile)
        {
            syntaxfile << "json { }\n";
            syntaxfile << "greater_less_than < >\n";
            syntaxfile.close();
        }
    }

    syntaxfile_exist.close();

    std::ifstream syntaxfile_in;
    syntaxfile_in.open("syntax_config.txt");

    std::string line;
    bool found = false;

    if (syntaxfile_in.is_open())
    {
        while (syntaxfile_in)
        {
            syntaxfile_in >> syntax_name_ >> front_delimiter_ >> end_delimiter_;
            getline(syntaxfile_in, line);

            if (syntax_name_ == syntax_type)
            {
                found = true;
                break;
            }
        }

        syntaxfile_in.close();

        if (!found)
        {
            syntax_name_ = "";
            front_delimiter_ = ' ';
            end_delimiter_ = ' ';
            std::cout << "Warning: Could not find delimiters, may cause problems!\n";
        }
    }
    else
    {
        std::cout << "Warning: No file open\n";
    }
}


bool Serial_port::check_com_format(char* com)
{
    //Format COMX or COMXX 
    std::string comStr(com); 
    if (comStr.length() > 5 || comStr.length() < 3) return false; 

    return true;

}
 char* Serial_port::handle_higher_com(char* com) 
{
    std::string comStr(com); 
    const char* prefix = "\\\\.\\";
    if (comStr.length() == 5)
    {
        strcat_s(com, sizeof(com), prefix);
      
        return com; 

    }
    else return com; 
}   
bool Serial_port::isConnected() { return connected; }