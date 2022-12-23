#define DEBUG 1               // Флаг отладочных сообщений

// Do not remove the include below
#include "Main.h"
#include "libraries/Settings.h"

//----------------------------------------------------------------------
//             Функция настроек при включении
//----------------------------------------------------------------------
void setup() {
#ifdef DEBUG
	Serial.begin(115200);                 // инициализация порта
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
//             Функция основного цикла
//
//----------------------------------------------------------------------
void loop() {
	//Logger_printad("Main", "Main Loop() start.\n");
	dnsServerLoop();				// Обработка DNS запросов
	//buttonHandler();              //вызов функции обрабатывающей команды нажатий
	WebEvents();                    // Обработка событий для веб-сервера

//	GPSMainLoop();					// Обновление данных GPS
//	oilingCalc();                   // Вызов функции смазки

//	powerIndLoop();					//Вызов функции индикатора текущего режима

	sensorLoop();					// обновление показаний датчиков

	pumpLoop();						// Управление насосами

	delay(50);
}
