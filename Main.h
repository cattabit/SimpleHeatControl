// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Template8266_H_
#define _Template8266_H_

#pragma once
#include "Arduino.h"
//add your includes for the project Template8266 here
#include <Arduino.h>
#include <Bounce2.h>          //библиотека устранения дребезга кнопки
#include <stdlib.h>

#include "libraries/Logger.h"

#include <ArduinoJson.h>
#include <LittleFS.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "libraries/timer.h"
#include "libraries/Settings.h"
#include "libraries/ActualValues.h"
#include "libraries/WebServer.h"
#include "libraries/WiFi.h"

//Можно поменять на 3 , при этом изменить номер внешнего прерывания на "1" (http://arduino.ru/Reference/AttachInterrupt)
#define PowerInd 2            // Индикатор включения платы
#define pressed_long 1500     //продолжительность длительного нажатия кнопки 1,5 сек

#define pinPumpArea1 14			// Управление насосом Контур 1 - Гостинная
#define pinPumpArea2 12			// Управление насосом Контур 2 - Ванная
#define pinPumpArea3 13			// Управление насосом Контур 3 - Второй этаж
#define pinPumpArea4 0			// Управление насосом Контур 4 - Запасной

#define pinDallasTemp 2			// Пин, куда подключены датчики температуры

#define pinDHT22Area4 16		//
#define pinDHT22Area5 5			//
#define pinDHT22Area6 4			//

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(pinDallasTemp);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

Timer timerPowerInd(400);

int impSeriesCnt = 1; // Количество импульсов в серии.

unsigned long pressed_moment1;  // момент нажатия кнопки Режим
Bounce bouncer1 = Bounce();     //создаем экземпляр класса Bounce кнопки Режим

////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------
//             Функция индикации текущего режима работы
//----------------------------------------------------------------------
void powerIndLoop() {
	if (timerPowerInd.ready()) {
		ActlVal.PowerIndStat = !ActlVal.PowerIndStat;
		timerPowerInd.reset();
	}

	if (ActlVal.PowerIndStat)
		digitalWrite(PowerInd, LOW);    //включаем
	else
		digitalWrite(PowerInd, HIGH);    //включаем
}

//----------------------------------------------------------------------
//             Функция опроса и обработки показаний датчиков
//----------------------------------------------------------------------
void sensorLoop() {
//	ActlVal.Area1_TemperatureC = 20 + random(1, 99) / 10;
//	ActlVal.Area2_TemperatureC = 20 + random(1, 99) / 10;
//	ActlVal.Area3_TemperatureC = 20 + random(1, 99) / 10;

	ActlVal.Area4_TemperatureC += 0.3;
	ActlVal.Area4_Humidity += 0.12;

	ActlVal.Area5_TemperatureC += 0.3;
	ActlVal.Area5_Humidity += 0.12;

	ActlVal.Area6_TemperatureC += 0.3;
	ActlVal.Area6_Humidity += 0.12;

	sensors.requestTemperatures();
	ActlVal.Area1_TemperatureC = sensors.getTempCByIndex(0);
	ActlVal.Area2_TemperatureC = sensors.getTempCByIndex(1);
	ActlVal.Area3_TemperatureC = sensors.getTempCByIndex(2);
}

//----------------------------------------------------------------------
//             Функция управления насосами
//----------------------------------------------------------------------
void pumpLoop() {

	// Контур 1
	if (ActlVal.Area1_TemperatureC < Stgs.Area1_tempPumpON) {
		ActlVal.Area1_PumpState = 1;
	}
	if (ActlVal.Area1_TemperatureC > Stgs.Area1_tempPumpOFF) {
		ActlVal.Area1_PumpState = 0;
	}

	// Контур 2
	if (ActlVal.Area2_TemperatureC < Stgs.Area2_tempPumpON) {
		ActlVal.Area2_PumpState = 1;
	}
	if (ActlVal.Area2_TemperatureC > Stgs.Area2_tempPumpOFF) {
		ActlVal.Area2_PumpState = 0;
	}

	// Контур 3
	if (ActlVal.Area3_TemperatureC < Stgs.Area3_tempPumpON) {
		ActlVal.Area3_PumpState = 1;
	}
	if (ActlVal.Area3_TemperatureC > Stgs.Area3_tempPumpOFF) {
		ActlVal.Area3_PumpState = 0;
	}

	// Пишем вычесленные значения на выход
	if (ActlVal.Area1_PumpState == 1)
		digitalWrite(pinPumpArea1, HIGH);
	else
		digitalWrite(pinPumpArea1, LOW);

	if (ActlVal.Area2_PumpState == 1)
		digitalWrite(pinPumpArea2, HIGH);
	else
		digitalWrite(pinPumpArea2, LOW);

	if (ActlVal.Area3_PumpState == 1)
		digitalWrite(pinPumpArea3, HIGH);
	else
		digitalWrite(pinPumpArea3, LOW);
}

//----------------------------------------------------------------------
//             Initialize LittleFS
//----------------------------------------------------------------------
void initFS() {
#ifdef DEBUG
	Logger_printadln("Main",
			LittleFS.begin() ?
					"LittleFS mounted successfully" :
					"An error has occurred while mounting LittleFS!");
#else
	LittleFS.begin();
#endif
}

//----------------------------------------------------------------------
//             Initialize Input/Outputs
//----------------------------------------------------------------------
void initIO() {
//	pinMode(PowerInd, OUTPUT); // Установка режима работы пина управления насосом

	// Нстройка пина управления насосом
	pinMode(pinPumpArea1, OUTPUT); // Установка режима работы пина управления насосом
	pinMode(pinPumpArea2, OUTPUT); // Установка режима работы пина управления насосом
	pinMode(pinPumpArea3, OUTPUT); // Установка режима работы пина управления насосом
	pinMode(pinPumpArea4, OUTPUT); // Установка режима работы пина управления насосом

	// Start the DS18B20 sensor
	sensors.begin();
}

//Do not add code below this line
#endif /* _Template8266_H_ */
