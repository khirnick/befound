#include "Manager.h"
#include "Params.h"

using namespace std;

// ������ �������� ������ �� ������ GPS
// � ���������� �� �� LoRa
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

// ������������� ������ LoRa
bool Manager::_initLoRa() {
	return _loRaProvider.init();
}

// ������������� ������� ���������
bool Manager::init() {
	pinMode(_btnPin, OUTPUT);

	_gpsProvider.beginSerial();
	bool initResult = _initLoRa();

	return initResult;
}

// �������� ������ ������ ��� �������� �� �� LoRa
String Manager::getPacketData() {
	float fLatitude = _gpsProvider.getFLatitude();
	float fLongitude = _gpsProvider.getFLongitude();
	float speedKmph = _gpsProvider.getSpeedKmph();

	char fLatChar[16] = { '\0' }, fLonChar[16] = { '\0' }, speedKmphChar[16] = { '\0' };

	dtostrf(fLatitude, 2, 6, fLatChar);
	dtostrf(fLongitude, 2, 6, fLonChar);
	dtostrf(speedKmph, 2, 6, speedKmphChar);

	String completePacket = 
	            String(CARRIER_ID) + ';' +
	            String(fLatChar) + ';' + 
							String(fLonChar) + ';' + 
							String(speedKmphChar) + ';' + 
							_btnStatus;

	return completePacket;
}

// ��������� ������ �� �� LoRa
void Manager::sendDataByLoRa(String data) {
	_loRaProvider.sendData(data);
}
