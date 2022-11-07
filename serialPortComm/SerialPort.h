#include <Windows.h>
#include <iostream>

#define WAIT_TIME 2000
using namespace std;


class serialPort {
private:

	HANDLE COMHandler;          //handle apointer to com port
	COMSTAT status;                //struct holds info about comm link >h many buf available,,,
	DWORD errors;
	bool connected;


public:
	serialPort(char* portName);
	~serialPort();

	int readSerialPort(char* buf, unsigned int buf_size);         //unsigned int >32bit
	bool writeSerialPort(char* buf ,unsigned int buf_size);
	bool isConnected();

};