#include "GpsProvider.h"

// ����������� ��������, ����������� �� ���������� ������
const String GpsProvider::NONE_DATA = "none";

void GpsProvider::beginSerial() {
	if (!_isSerialBegan) {
		_gpsSerial.begin(9600);

		Serial.println("GPS init successful");
	}
}

// ������������� �������� ������� �����
void GpsProvider::initLoopStarted(long loopStarted) {
	_loopStarted = loopStarted;
}

// ���������� �������� ����� ������ � GPS ������
String GpsProvider::tryGetNewData() {
	while (millis() - _loopStarted < 5000) {
		if (_tryReadGps()) {
			_newDataCame = true;
		}
	}
 
 if (_newDataCame) {
    _assignGpsData();
    String gpsDataCoordAgeSpeedRow = getGpsDataCoordAgeSpeedRow();

    return gpsDataCoordAgeSpeedRow;
  }

	return NONE_DATA;
}

// �������� ���������� � �������� � ���� ������
String GpsProvider::getGpsDataCoordAgeSpeedRow() const {
	String gpsDataCoordAgeSpeed = GPS_DATA + LATITUDE_INFO;
	gpsDataCoordAgeSpeed += String(getFLatitude(), 8);
	gpsDataCoordAgeSpeed += LONGITUDE_INFO;
	gpsDataCoordAgeSpeed += String(getFLongitude(), 8);
	gpsDataCoordAgeSpeed += AGE;
	gpsDataCoordAgeSpeed += getFixAge();

	return gpsDataCoordAgeSpeed;
}

// �������� ����������, ����������� �� ������� ����� ������
bool GpsProvider::getNewDataCame() const {
	return _newDataCame;
}

// �������� �������
long GpsProvider::getLatitude() const {
	return _latitude;
}

// �������� ������
long GpsProvider::getLongitude() const {
	return _longitude;
}

// �������� ������� � float-�������
float GpsProvider::getFLatitude() const {
	return _fLatitude;
}

// �������� ������ � float-�������
float GpsProvider::getFLongitude() const {
	return _fLongitude;
}

// �������� ��������, ����������� ��� ����� ���� ������������� ������ �� GPS ������
unsigned long GpsProvider::getFixAge() const {
	return _fixAge;
}

// �������� �������� � ��/�
float GpsProvider::getSpeedKmph() const {
	return _speedKmph;
}

// ���������� ��������� ������ � GPS-������
bool GpsProvider::_tryReadGps() {
	while (_gpsSerial.available()) {
		int ch = _gpsSerial.read();

		if (_gps.encode(ch)) {      
			return true;
		}
	}

	return false;
}

// ��������� ��������������� ������ ���������� �������
void GpsProvider::_assignGpsData() {
	_gps.get_position(&_latitude, &_longitude, &_fixAge);
	_gps.f_get_position(&_fLatitude, &_fLongitude, &_fixAge);
	_speedKmph = _gps.f_speed_kmph();
}
