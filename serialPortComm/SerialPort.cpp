#include "SerialPort.h"
//config serial param
//send data 
//read serial data
//write serial data
//close serial

serialPort::serialPort(char* portName)
{
	//initialize to avoid error from vs
	errors = 0;
	status = {0};     //how many buf available
	connected = false;

	//create & open serial port 
	COMHandler = CreateFileA(static_cast<LPCSTR>(portName),                   //LPCSTR>
							GENERIC_READ|GENERIC_WRITE ,         //OPEN IT FOR READ AND WRITE
							0 ,
							NULL ,
							OPEN_EXISTING ,
							FILE_ATTRIBUTE_NORMAL ,
							NULL                      );

	//hanlde errors

	DWORD errMsg = GetLastError();

	if (errMsg==ERROR_FILE_NOT_FOUND)  
	{
		printf("ERROR FILE NOT FOUND ,pleas plug in device first .\n");
		return;
	}
	else if(errMsg == ERROR_ACCESS_DENIED)
	{
		printf("ERROR ACCESS DENIED ,another app is already using device .\n");
		return;
	}

	   //configure serial port
	else if(errMsg == 0)    //no errors
	{
		//set setting for DCB
		DCB dcbserialParam = { 0 };
		if (!GetCommState(COMHandler, &dcbserialParam))
		{
			printf("failed to get current serial param");
		}
		else 
		{
			dcbserialParam.BaudRate = CBR_9600;
			dcbserialParam.ByteSize = 8;
			dcbserialParam.StopBits = ONESTOPBIT;    //0
			dcbserialParam.Parity = NOPARITY;
			dcbserialParam.fDtrControl = DTR_CONTROL_ENABLE;

			if (!GetCommState(COMHandler, &dcbserialParam))
			{
				printf("failed to set serial port parameters\n");
			}
			else
			{
				connected = true;
				PurgeComm(COMHandler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(WAIT_TIME);
			}

		}

	}

}

serialPort::~serialPort()
{
	if(connected == true) {
		connected = false;
		CloseHandle(COMHandler);
	}
}

int serialPort::readSerialPort(char* buf, unsigned int buf_size)
{
	DWORD bytesRead;
	unsigned int toRead=0;

	ClearCommError(COMHandler, &errors, &status);

	//get how many bytes to read
	//prepare to read any available bytes not exceed the requested num of bytes
	if (status.cbInQue > 0)
	{
		if (status.cbInQue > buf_size)      //buf_size >num of bytes we want to read
		{
			toRead = buf_size;
		}
		else toRead = status.cbInQue;
	}

	//read bytes we wanna(toRead) read into buffer(buffer) and return num of bytes actually read (bytesRead)
	if (ReadFile(COMHandler, buffer, toRead, &bytesRead, NULL))
	{
		return bytesRead;
	}
	return 0;
}

bool serialPort::writeSerialPort(char* buf, unsigned int buf_size)
{
	return false;
}

bool serialPort::isConnected()
{
	return connected;
}
