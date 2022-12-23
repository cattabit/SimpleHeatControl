#define DEBUG 1               // ���� ���������� ���������

// Do not remove the include below
#include "Main.h"
#include "libraries/Settings.h"

//----------------------------------------------------------------------
//             ������� �������� ��� ���������
//----------------------------------------------------------------------
void setup() {
#ifdef DEBUG
	Serial.begin(115200);                 // ������������� �����
#endif

	delay (2000);
	Logger_printadln("Main", "");
	Logger_printadln("Main", "//----------------------------------------------------------------------");
	Logger_printadln("Main", "//             HeatControl, 2022.");
	Logger_printadln("Main", "//           program starting..");
	Logger_printadln("Main", "//----------------------------------------------------------------------");

	Logger_printadln("Main", "Initialize File System..");
	initFS();

	Logger_printadln("Main", "Load saved settings..");
	Stgs.LoadValues();             //Initialize saved settings values

	Logger_printadln("Main", "Initialize WiFi..");
	initWiFi();

	Logger_printadln("Main", "Initialize Web Server..");
	initWebServer();

	Logger_printadln("Main", "Initialize IO..");
	initIO();




	delay (1000);
	Logger_printad("Main", "Setup() finished.\n");
}

//----------------------------------------------------------------------
//
//             ������� ��������� �����
//
//----------------------------------------------------------------------
void loop() {
	//Logger_printad("Main", "Main Loop() start.\n");
	dnsServerLoop();				// ��������� DNS ��������
	//buttonHandler();              //����� ������� �������������� ������� �������
	WebEvents();                    // ��������� ������� ��� ���-�������

//	GPSMainLoop();					// ���������� ������ GPS
//	oilingCalc();                   // ����� ������� ������

//	powerIndLoop();					//����� ������� ���������� �������� ������

	sensorLoop();					// ���������� ��������� ��������

	pumpLoop();						// ���������� ��������

	delay(50);
}
