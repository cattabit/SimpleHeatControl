// Get current sensor readings when the page loads
//window.addEventListener('load', getReadings);
//window.addEventListener('load', getSettings);

// Функция обновления значения элемента, где key = ID элемента, а Value - его значение.
function updateElementsValuesById(objData) {
	//console.log("updateElementsValuesById() ");
	for (var obj in objData) {
		
		if (obj == "gps_fixmode") { 	// Формирование отображения состояния фиксации
			if (document.getElementById("_gps_fixmode_btn")) {
				if (parseInt(objData[obj]) > 0) {
					document.getElementById("_gps_fixmode_btn").className = "button-active pure-button";
					document.getElementById("_gps_fixmode_btn").innerText = "Fix - OK";
				}
				else if (parseInt(objData[obj]) <= 0) {
					document.getElementById("_gps_fixmode_btn").className = "pure-button pure-button-primary";
					document.getElementById("_gps_fixmode_btn").innerText = "No Fix!";
				}
				else {
					document.getElementById("_gps_fixmode_btn").className = "pure-button pure-button-primary";
					document.getElementById("_gps_fixmode_btn").innerText = "NA";
				}
			}
		}
		if (obj == "gps_connect") { 	// Формирование отображения состояния фиксации
			if (document.getElementById("_gps_connect_btn")) {
				if (objData[obj] == "1") {
					document.getElementById("_gps_connect_btn").className = "button-active pure-button";
					document.getElementById("_gps_connect_btn").innerText = "Связь с датчиком: ОК";
				}
				else if (objData[obj] == "0") {
					document.getElementById("_gps_connect_btn").className = "pure-button pure-button-primary";
					document.getElementById("_gps_connect_btn").innerText = "Нет связи с датчиком!";
				}
				else {
					document.getElementById("_gps_connect_btn").className = "pure-button pure-button-primary";
					document.getElementById("_gps_connect_btn").innerText = "NA";
				}
			}
		}




		//else // остальные пытаемся установить по ID
		//console.log("_" + obj + " > " + objData[obj] + " (type: " + typeof objData[obj] + ")");
		if (typeof objData[obj] == 'string' || typeof objData[obj] == 'number') {
			try {
				if (document.getElementById("_" + obj)) {
					//console.log(document.getElementById("_" + obj));
					document.getElementById("_" + obj).value = objData[obj];
				} else {
					console.log('updateElementsValuesById: Ошибка установки значения, не найден элемент id="_' + obj + '" (: ' + objData[obj] + '). Пропускаем.');
				}
			} catch (e) {
				console.log('updateElementsValuesById: Ошибка установки значения: _' + obj + " > " + objData[obj] + " | " + e.name + ":" + e.message + "\n" + e.stack);
				throw e;
			}
		}
		else {
			console.log("Not String or Number type of value! Skip!");
		}
	}
}


// Function to get current readings on the webpage when it loads for the first time
// Функция получения текущих значений при первой загрузке страницы
function getReadings() {
	var xhr = new XMLHttpRequest();
	// Запрос изменяемых параметров
	xhr.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			console.log("getReadings() Server response: " + this.responseText);
			var data = JSON.parse(this.responseText);
			console.log(data);
			updateElementsValuesById(data);
		}
	};
	xhr.open("GET", "/readings", true);
	xhr.send();
}

// Function to get current settings values on the webpage when it loads for the first time
// Функция получения текущих значений при первой загрузке страницы
function getSettings() {
	var xhr = new XMLHttpRequest();
	// Запрос значений настроек
	xhr.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			console.log("getSettings() Server response: " + this.responseText);
			var data = JSON.parse(this.responseText);
			console.log(data);
			updateElementsValuesById(data);
		}
	};
	xhr.open("GET", "/settings", true);
	xhr.send();
}

// Функция получения текущих значений
function getTankLevel() {
	var xhr = new XMLHttpRequest();
	// Запрос значений настроек
	xhr.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			console.log("getTankLevel() Server response: " + this.responseText);
			var data = JSON.parse(this.responseText);
			console.log(data);
			updateElementsValuesById(data);
		}
	};
	xhr.open("GET", "/tanklevel", true);
	xhr.send();
}

function refreshData() {
	getSettings();
	getReadings();
	getTankLevel();
}

// Отправка значений медом POST в /post
function postSettingsReset() {
	console.log("postSettingsReset() started..");
	var xhr = new XMLHttpRequest();
	xhr.open("GET", '/settings_reset_req', true);
	xhr.send();
	xhr.onload = function() {
		console.log("this.responseText = " + this.responseText);
	};
	getSettings(); // Обновим все значения настроек
}

// Отправка значений медом POST в /post
function postTankLevelReset() {
	console.log("postTankLevelReset() started..");
	var xhr = new XMLHttpRequest();
	xhr.open("GET", '/tanklevel_reset_req', true);
	xhr.send();
	xhr.onload = function() {
		console.log("this.responseText = " + this.responseText);
	};
	getTankLevel(); // Обновим все значения настроек
}

// Отправка значений медом POST в /post
function postSettingsRequest(data) {
	console.log("postRequest() started..");
	var xhr = new XMLHttpRequest();
	xhr.open("POST", '/postSettings', true);
	xhr.send(data);
	xhr.onload = function() {
		console.log("this.responseText = " + this.responseText);
		getSettings(); // Обновим все значения настроек
	};
}

// Сохранение значений
function postSettings() {
	console.log("postSettingsMilage() started..");
	var data = new FormData();
	data.set('Area1_tempPumpON', document.getElementById('_Area1_tempPumpON').value);
	data.set('Area1_tempPumpOFF', document.getElementById('_Area1_tempPumpOFF').value);
	
	data.set('Area2_tempPumpON', document.getElementById('_Area2_tempPumpON').value);
	data.set('Area2_tempPumpOFF', document.getElementById('_Area2_tempPumpOFF').value);
	
	data.set('Area3_tempPumpON', document.getElementById('_Area3_tempPumpON').value);
	data.set('Area3_tempPumpOFF', document.getElementById('_Area3_tempPumpOFF').value);
	postSettingsRequest(data);
}



if (!!window.EventSource) {
	var source = new EventSource('/events');
	source.addEventListener('open', function(e) {
		console.log("Events Connected");
	}, false);

	source.addEventListener('error', function(e) {
		if (e.target.readyState != EventSource.OPEN) {
			console.log("Events Disconnected");
		}
	}, false);

	source.addEventListener('message', function(e) {
		console.log("message", e.data);
	}, false);

	source.addEventListener('new_readings', function(e) {
		//console.log("new_readings", e.data);
		var data = JSON.parse(e.data);
		//console.log(data);
		updateElementsValuesById(data);
	}, false);

	source.addEventListener('new_settings', function(e) {
		console.log("new_settings", e.data);
		var data = JSON.parse(e.data);
		//console.log(data);
		updateElementsValuesById(data);
	}, false);

	source.addEventListener('new_tanklevel', function(e) {
		console.log("new_tanklevel", e.data);
		var data = JSON.parse(e.data);
		//console.log(data);
		updateElementsValuesById(data);
	}, false);
}
