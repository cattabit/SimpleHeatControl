/*
 * Config.h
 *
 *  Created on: 3 июл. 2022 г.
 *      Author: vector
 */

#ifndef LIBRARIES_SETTINGS_H_
#define LIBRARIES_SETTINGS_H_

#pragma once
#include <ArduinoJson.h>
#include <Arduino.h>

#include <LittleFS.h>

//#define DEBUG 1               // Флаг отладочных сообщений

#define CONFIG_FILE_NAME	"/voiler.settings"

//#define tempPumpMin 3  //Значение
//#define tempPumpMax 50  //Значение

class SettingsVOoiler {
private:
	float tempPumpMax = 50.0; // Макс.значене температуры для проверки
	float tempPumpMin = 5.0; // Макс.значене температуры для проверки

public:

	// Контур 1
	float Area1_tempPumpON = 21.0;		// Температура включения насоса
	float Area1_tempPumpOFF = 22.0;		// Температура Выключения насоса

	// Контур 2
	float Area2_tempPumpON = 21.0;		// Температура включения насоса
	float Area2_tempPumpOFF = 22.0;		// Температура Выключения насоса

	// Контур 3
	float Area3_tempPumpON = 21.0;		// Температура включения насоса
	float Area3_tempPumpOFF = 22.0;		// Температура Выключения насоса

	SettingsVOoiler() {
	}
	;

	//----------------------------------------------------------------------
	//             Функция обновления настроечных параметров, значениями,
	//          полученными от веб-интерфейса
	//----------------------------------------------------------------------
	String setSettingsValue(String par, String value) {
		Logger_printadln("Settings", "\"" + par + "\" = " + value);

		/// говнокод какой-то.. потом переделать нужно.
		int ival;
		float fval;
		unsigned long ulval;

		String result = "Atribute " + par + " not found!";

		if (par.length() < 2 || value.length() < 1) {
			result = "par.length = " + String(par.length()) + ",  value.length = " + String(value.length())
					+ "! Failed parce values!";
		}
		else {

			//////////////////////////////////
			if (par.equals("Area1_tempPumpON")) {
				fval = atof(value.c_str());
				if (tempPumpMin <= fval and fval <= (Area1_tempPumpOFF - 0.5)) {
					Area1_tempPumpON = fval;
					result = "Atribute " + par + " - OK";
				}
				else
					result = "Atribute " + par + " value should be between " + String(tempPumpMin) + " and "
							+ String(tempPumpMax) + "!";
			}

			if (par.equals("Area1_tempPumpOFF")) {
				fval = atof(value.c_str());
				if ((Area1_tempPumpON + 0.5) <= fval and fval <= tempPumpMax) {
					Area1_tempPumpOFF = fval;
					result = "Atribute " + par + " - OK";
				}
				else
					result = "Atribute " + par + " value should be between " + String(tempPumpMin) + " and "
							+ String(tempPumpMax) + "!";
			}

			//////////////////////////////////
			if (par.equals("Area2_tempPumpON")) {
				fval = atof(value.c_str());
				if (tempPumpMin <= fval and fval <= (Area2_tempPumpOFF - 0.5)) {
					Area2_tempPumpON = fval;
					result = "Atribute " + par + " - OK";
				}
				else
					result = "Atribute " + par + " value should be between " + String(tempPumpMin) + " and "
							+ String(tempPumpMax) + "!";
			}
			if (par.equals("Area2_tempPumpOFF")) {
				fval = atof(value.c_str());
				if ((Area2_tempPumpON + 0.5) <= fval and fval <= tempPumpMax) {
					Area2_tempPumpOFF = fval;
					result = "Atribute " + par + " - OK";
				}
				else
					result = "Atribute " + par + " value should be between " + String(tempPumpMin) + " and "
							+ String(tempPumpMax) + "!";
			}

			//////////////////////////////////
			if (par.equals("Area3_tempPumpON")) {
				fval = atof(value.c_str());
				if (tempPumpMin <= fval and fval <= (Area3_tempPumpOFF - 0.5)) {
					Area3_tempPumpON = fval;
					result = "Atribute " + par + " - OK";
				}
				else
					result = "Atribute " + par + " value should be between " + String(tempPumpMin) + " and "
							+ String(tempPumpMax) + "!";
			}
			if (par.equals("Area3_tempPumpOFF")) {
				fval = atof(value.c_str());
				if ((Area3_tempPumpON + 0.5) <= fval and fval <= tempPumpMax) {
					Area3_tempPumpOFF = fval;
					result = "Atribute " + par + " - OK";
				}
				else
					result = "Atribute " + par + " value should be between " + String(tempPumpMin) + " and "
							+ String(tempPumpMax) + "!";
			}
		}
		Logger_printadln("Settings", result);
		return result;
	}

	//----------------------------------------------------------------------
	//             Функция формирования JSON-объекта с текущими значениями настроек
	//----------------------------------------------------------------------
	StaticJsonDocument<1024> getValuesJSON() {
		StaticJsonDocument<1024> doc;

		// Set the values in the document
		doc["Area1_tempPumpON"] = String(Area1_tempPumpON);
		doc["Area1_tempPumpOFF"] = String(Area1_tempPumpOFF);

		doc["Area2_tempPumpON"] = String(Area2_tempPumpON);
		doc["Area2_tempPumpOFF"] = String(Area2_tempPumpOFF);

		doc["Area3_tempPumpON"] = String(Area3_tempPumpON);
		doc["Area3_tempPumpOFF"] = String(Area3_tempPumpOFF);

		return doc;
	}

	//----------------------------------------------------------------------
	//             Функция упаковывки всех текущих значений в JSON формат
	//          Используется для передачи
	//----------------------------------------------------------------------
	String getValuesJSON_String() {
		String jsonString;
		serializeJson(getValuesJSON(), jsonString);
		return jsonString;
	}

	//----------------------------------------------------------------------
	//    Функция загрузки ранее сохраненных значений параметров (настроек)
	//----------------------------------------------------------------------
	bool LoadValues() {
#ifdef DEBUG
		Serial.println("LoadSettings() started.");
#endif
		// Allocate a temporary JsonDocument
		// Don't forget to change the capacity to match your requirements.
		// Use https://arduinojson.org/v6/assistant to compute the capacity.
		StaticJsonDocument<1024> doc;

		File file = LittleFS.open(CONFIG_FILE_NAME, "r");
		if (!file) {
#ifdef DEBUG
			Serial.println("Failed to open file  for reading");
#endif
			// Если файл с настройками отсутствует - создаем его и записываем текущие значения настроек.
			SaveValues();
		}

		// Deserialize the JSON document
		DeserializationError error = deserializeJson(doc, file);
		file.close();
		if (error) {
#ifdef DEBUG
			Serial.println(
					F("Failed to read file, using default configuration"));
#endif
			return false;
		}
		else {

#ifdef DEBUG
			String jsonString;
			serializeJson(doc, jsonString);
			Serial.println(jsonString);
			Serial.printf("Parce setting pairs from file:\n");
#endif

			// Copy values from the JsonDocument to the Config
			JsonObject root = doc.as<JsonObject>();

			// using C++11 syntax (preferred):
			for (JsonPair kv : root) {
#ifdef DEBUG
				Serial.printf("('%s': %s)\n", kv.key().c_str(),
						kv.value().as<String>());
				Serial.println(
						setSettingsValue(kv.key().c_str(),
								kv.value().as<String>()));
#else
				setSettingsValue(kv.key().c_str(), kv.value().as<String>());
#endif
			}

#ifdef DEBUG
			Serial.println(F("Configuration loaded successfully:"));
			Serial.println(getValuesJSON_String());
#endif
			return true;
		}
	}

	//----------------------------------------------------------------------
	//             Функция сохранения текущих значений параметров (настроек)
	//----------------------------------------------------------------------
	bool SaveValues() {
		// Allocate a temporary JsonDocument
		// Don't forget to change the capacity to match your requirements.
		// Use https://arduinojson.org/assistant to compute the capacity.
		StaticJsonDocument<1024> doc = getValuesJSON();

#ifdef DEBUG
		Serial.printf("saveSettings( ");
		Serial.printf( CONFIG_FILE_NAME);
		Serial.println(")..");
		if (!LittleFS.exists(CONFIG_FILE_NAME))
		Serial.println("File doesn't exist ");
		else
		Serial.println("File exists ");
#endif
		LittleFS.remove(CONFIG_FILE_NAME);

		File file = LittleFS.open(CONFIG_FILE_NAME, "w");
#ifdef DEBUG
		if (!file) {
			Serial.println("Failed to open file for writing");
		}
#endif

		// Serialize JSON to file
		if (serializeJson(doc, file) == 0) {
#ifdef DEBUG
			Serial.println("Failed to write to file ");
#endif
			return false;
		}
		file.close();

		return true;
	}

	//----------------------------------------------------------------------
	//             Функция восстановления значений по-умолчанию
	//----------------------------------------------------------------------
	void ResetSettings() {
		LittleFS.remove(CONFIG_FILE_NAME);
	}

	//----------------------------------------------------------------------
	//             Перезагрузка контроллера
	//----------------------------------------------------------------------
	void reboot() {
		wdt_disable();
		wdt_enable(WDTO_15MS);
		while (1) {
		}
	}

}
;

SettingsVOoiler Stgs;

#endif /* LIBRARIES_SETTINGS_H_ */
