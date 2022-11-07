#include<iostream>
#include<iomanip>
#include<string>
#include"SerialPort.h"

char* inputData =NULL;

char comPort[] = "COM1";
//char* port = comPort;

using namespace std;
int main()
{
	serialPort serialDevice(comPort);

	if (serialDevice.isConnected())
	{
		cout << "connected to " << comPort << endl;
	}
	else {
		cin.get();
	}

	//loop to read data

	while (serialDevice.isConnected())
	{
		serialDevice.readSerialPort(inputData, sizeof(inputData));

		//convert char to string
		string strIData(inputData);

		//convert string into double
		double x = stod(strIData);

		Sleep(500);
	}



	return 0;

}

