#include "Manager.h"

using namespace std;

// Начать получать данные от модуля GPS
// и отправлять по БС LoRa
String Manager::startGetDataAndSend() {
	_btnStatus = digitalRead(_btnPin);

	unsigned long loopStarted = millis();

	_gpsProvider.initLoopStarted(loopStarted);

	String gpsDataCoordAgeSpeedRow = _gpsProvider.tryGetNewData();
	
	if (gpsDataCoordAgeSpeedRow != GpsProvider::NONE_DATA) {
		String packet = getPacketData();

		sendDataByLoRa(packet);
	}

	return gpsDataCoordAgeSpeedRow;
}

// Инициализация модуля LoRa
bool Manager::_initLoRa() {
	return _loRaProvider.init();
}

// Инициализация объекта менеджера
bool Manager::init() {
	pinMode(_btnPin, OUTPUT);

	_gpsProvider.beginSerial();
	bool initResult = _initLoRa();

	return initResult;
}

// Получить строку данных для отправки по БС LoRa
String Manager::getPacketData() {
	float fLatitude = _gpsProvider.getFLatitude();
	float fLongitude = _gpsProvider.getFLongitude();
	float speedKmph = _gpsProvider.getSpeedKmph();

	char fLatChar[16] = { '\0' }, fLonChar[16] = { '\0' }, speedKmphChar[16] = { '\0' };

	dtostrf(fLatitude, 2, 6, fLatChar);
	dtostrf(fLongitude, 2, 6, fLonChar);
	dtostrf(speedKmph, 2, 6, speedKmphChar);

	String completePacket = String(fLatChar) + ';' + 
							String(fLonChar) + ';' + 
							String(speedKmphChar) + ';' + 
							_btnStatus;

	return completePacket;
}

// Отправить данные по БС LoRa
void Manager::sendDataByLoRa(String data) {
	_loRaProvider.sendData(data);
}
