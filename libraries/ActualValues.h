/*
 * ActualValues.h
 *
 *  Created on: 3 ���. 2022 �.
 *      Author: vector
 */

#ifndef LIBRARIES_ACTUALVALUES_H_
#define LIBRARIES_ACTUALVALUES_H_

#pragma once

class ActualValues {
private:
	bool PumpState = false;      		//������� ��������� ������
	bool PumpPrevState = false;      		//������� ��������� ������
public:
	bool PowerIndStat = false;   		//������� ��������� ��������� ����������

	// �������� �������

	// ������ 1
	float Area1_TemperatureC = 0.0;		// ������ 1 - ����������� - ���������
	byte Area1_PumpState = 0;			// ������� ��������� ������

	// ������ 2
	float Area2_TemperatureC = 0.0;		// ������ 2 - ����������� - ������
	byte Area2_PumpState = 0;			// ������� ��������� ������

	// ������ 3
	float Area3_TemperatureC = 0.0;		// ������ 3 - ����������� - ������ ����
	byte Area3_PumpState = 0;			// ������� ��������� ������

	// ������ 4
	// ������� 	DHT22
	float Area4_TemperatureC = 0.0;		// ������ 4 - ����������� � �������
	float Area4_Humidity = 0.0;			// ������ 4 - ��������� � �������

	// ������ 5
	float Area5_TemperatureC = 0.0;		// ������ 5 - �����������
	float Area5_Humidity = 0.0;			// ������ 5 - ���������

	// ������ 6
	float Area6_TemperatureC = 0.0;		// ������ 6 - �����������
	float Area6_Humidity = 0.0;			// ������ 6 - ���������

	int alivebyte = 0;	// ��������� ���������� ����������� ��� ������� �� ���.

	ActualValues() {

	}
	;

	//----------------------------------------------------------------------
	//             ������� ���������� ���� ������� �������� � JSON ������
	//----------------------------------------------------------------------
	StaticJsonDocument<1024> getValuesJSON() {
		StaticJsonDocument < 1024 > jReadings;

		jReadings["alivebyte"] = alivebyte;

		jReadings["Area1_TemperatureC"] = String(Area1_TemperatureC);
		jReadings["Area1_PumpState"] = String(Area1_PumpState);

		jReadings["Area2_TemperatureC"] = String(Area2_TemperatureC);
		jReadings["Area2_PumpState"] = String(Area2_PumpState);

		jReadings["Area3_TemperatureC"] = String(Area3_TemperatureC);
		jReadings["Area3_PumpState"] = String(Area3_PumpState);

		jReadings["Area4_TemperatureC"] = String(Area4_TemperatureC);
		jReadings["Area4_Humidity"] = String(Area4_Humidity);

		jReadings["Area5_TemperatureC"] = String(Area4_TemperatureC);
		jReadings["Area5_Humidity"] = String(Area4_Humidity);

		jReadings["Area6_TemperatureC"] = String(Area4_TemperatureC);
		jReadings["Area6_Humidity"] = String(Area4_Humidity);

		return jReadings;
	}

	//----------------------------------------------------------------------
	//             ������� ���������� ���� ������� �������� � JSON ������
	//----------------------------------------------------------------------
	String getValuesJSON_String() {
		String jsonString;
		serializeJson(getValuesJSON(), jsonString);
		return jsonString;
	}
};

ActualValues ActlVal;

#endif /* LIBRARIES_ACTUALVALUES_H_ */
