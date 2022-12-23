/*
 * ActualValues.h
 *
 *  Created on: 3 июл. 2022 г.
 *      Author: vector
 */

#ifndef LIBRARIES_ACTUALVALUES_H_
#define LIBRARIES_ACTUALVALUES_H_

#pragma once

class ActualValues {
private:
	bool PumpState = false;      		//Текущее состояние насоса
	bool PumpPrevState = false;      		//Текущее состояние насоса
public:
	bool PowerIndStat = false;   		//Текущее состояние светового индикатора

	// ЗНачения текущие

	// Контур 1
	float Area1_TemperatureC = 0.0;		// Контур 1 - Температура - Гостинная
	byte Area1_PumpState = 0;			// Текущее состояние насоса

	// Контур 2
	float Area2_TemperatureC = 0.0;		// Контур 2 - Температура - Ванная
	byte Area2_PumpState = 0;			// Текущее состояние насоса

	// Контур 3
	float Area3_TemperatureC = 0.0;		// Контур 3 - Температура - Второй Этаж
	byte Area3_PumpState = 0;			// Текущее состояние насоса

	// Контур 4
	// Датчики 	DHT22
	float Area4_TemperatureC = 0.0;		// Контур 4 - Температура в парилке
	float Area4_Humidity = 0.0;			// Контур 4 - Влажность в парилке

	// Контур 5
	float Area5_TemperatureC = 0.0;		// Контур 5 - Температура
	float Area5_Humidity = 0.0;			// Контур 5 - Влажность

	// Контур 6
	float Area6_TemperatureC = 0.0;		// Контур 6 - Температура
	float Area6_Humidity = 0.0;			// Контур 6 - Влажность

	int alivebyte = 0;	// индикатор активности контроллера для отладки на веб.

	ActualValues() {

	}
	;

	//----------------------------------------------------------------------
	//             Функция упаковывки всех текущих значений в JSON формат
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
	//             Функция упаковывки всех текущих значений в JSON формат
	//----------------------------------------------------------------------
	String getValuesJSON_String() {
		String jsonString;
		serializeJson(getValuesJSON(), jsonString);
		return jsonString;
	}
};

ActualValues ActlVal;

#endif /* LIBRARIES_ACTUALVALUES_H_ */
