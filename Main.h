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
#include <Bounce2.h>          //���������� ���������� �������� ������
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

//����� �������� �� 3 , ��� ���� �������� ����� �������� ���������� �� "1" (http://arduino.ru/Reference/AttachInterrupt)
#define PowerInd 2            // ��������� ��������� �����
#define pressed_long 1500     //����������������� ����������� ������� ������ 1,5 ���

#define pinPumpArea1 14			// ���������� ������� ������ 1 - ���������
#define pinPumpArea2 12			// ���������� ������� ������ 2 - ������
#define pinPumpArea3 13			// ���������� ������� ������ 3 - ������ ����
#define pinPumpArea4 0			// ���������� ������� ������ 4 - ��������

#define pinDallasTemp 2			// ���, ���� ���������� ������� �����������

#define pinDHT22Area4 16		//
#define pinDHT22Area5 5			//
#define pinDHT22Area6 4			//

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(pinDallasTemp);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

Timer timerPowerInd(400);

int impSeriesCnt = 1; // ���������� ��������� � �����.

unsigned long pressed_moment1;  // ������ ������� ������ �����
Bounce bouncer1 = Bounce();     //������� ��������� ������ Bounce ������ �����

////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------
//             ������� ��������� �������� ������ ������
//----------------------------------------------------------------------
void powerIndLoop() {
	if (timerPowerInd.ready()) {
		ActlVal.PowerIndStat = !ActlVal.PowerIndStat;
		timerPowerInd.reset();
	}

	if (ActlVal.PowerIndStat)
		digitalWrite(PowerInd, LOW);    //��������
	else
		digitalWrite(PowerInd, HIGH);    //��������
}

//----------------------------------------------------------------------
//             ������� ������ � ��������� ��������� ��������
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
//             ������� ���������� ��������
//----------------------------------------------------------------------
void pumpLoop() {

	// ������ 1
	if (ActlVal.Area1_TemperatureC < Stgs.Area1_tempPumpON) {
		ActlVal.Area1_PumpState = 1;
	}
	if (ActlVal.Area1_TemperatureC > Stgs.Area1_tempPumpOFF) {
		ActlVal.Area1_PumpState = 0;
	}

	// ������ 2
	if (ActlVal.Area2_TemperatureC < Stgs.Area2_tempPumpON) {
		ActlVal.Area2_PumpState = 1;
	}
	if (ActlVal.Area2_TemperatureC > Stgs.Area2_tempPumpOFF) {
		ActlVal.Area2_PumpState = 0;
	}

	// ������ 3
	if (ActlVal.Area3_TemperatureC < Stgs.Area3_tempPumpON) {
		ActlVal.Area3_PumpState = 1;
	}
	if (ActlVal.Area3_TemperatureC > Stgs.Area3_tempPumpOFF) {
		ActlVal.Area3_PumpState = 0;
	}

	// ����� ����������� �������� �� �����
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
//	pinMode(PowerInd, OUTPUT); // ��������� ������ ������ ���� ���������� �������

	// �������� ���� ���������� �������
	pinMode(pinPumpArea1, OUTPUT); // ��������� ������ ������ ���� ���������� �������
	pinMode(pinPumpArea2, OUTPUT); // ��������� ������ ������ ���� ���������� �������
	pinMode(pinPumpArea3, OUTPUT); // ��������� ������ ������ ���� ���������� �������
	pinMode(pinPumpArea4, OUTPUT); // ��������� ������ ������ ���� ���������� �������

	// Start the DS18B20 sensor
	sensors.begin();
}

//Do not add code below this line
#endif /* _Template8266_H_ */
