#include "GpsProvider.h"

// Константное значение, указывающее на отсутствие данных
const String GpsProvider::NONE_DATA = "none";

void GpsProvider::beginSerial() {
	if (!_isSerialBegan) {
		_gpsSerial.begin(9600);

		Serial.println("GPS init successful");
	}
}

// Инициализация значения времени цикла
void GpsProvider::initLoopStarted(long loopStarted) {
	_loopStarted = loopStarted;
}

// Попытаться получить новые данные с GPS модуля
String GpsProvider::tryGetNewData() {
	if (_gpsCyclesLeftBound != 0) {
		_gpsCyclesLeft++;
	}

	while (millis() - _loopStarted < 500) {
		if (_tryReadGps()) {
			_newDataCame = true;
		}
	}

	if (_gpsCyclesLeft == _gpsCyclesLeftBound) {
		_gpsCyclesLeft = 0;
	}

	if (_newDataCame) {
		_assignGpsData();
		String gpsDataCoordAgeSpeedRow = getGpsDataCoordAgeSpeedRow();

		return gpsDataCoordAgeSpeedRow;
	}

	return NONE_DATA;
}

// Получить координаты и скорость в виде строки
String GpsProvider::getGpsDataCoordAgeSpeedRow() const {
	String gpsDataCoordAgeSpeed = GPS_DATA + LATITUDE_INFO;
	gpsDataCoordAgeSpeed += String(getFLatitude(), 8);
	gpsDataCoordAgeSpeed += LONGITUDE_INFO;
	gpsDataCoordAgeSpeed += String(getFLongitude(), 8);
	gpsDataCoordAgeSpeed += AGE;
	gpsDataCoordAgeSpeed += getFixAge();

	return gpsDataCoordAgeSpeed;
}

// Получить переменную, указывающую на наличие новых данных
bool GpsProvider::getNewDataCame() const {
	return _newDataCame;
}

// Получить долготу
long GpsProvider::getLatitude() const {
	return _latitude;
}

// Получить широту
long GpsProvider::getLongitude() const {
	return _longitude;
}

// Получить долготу в float-формате
float GpsProvider::getFLatitude() const {
	return _fLatitude;
}

// Получить широту в float-формате
float GpsProvider::getFLongitude() const {
	return _fLongitude;
}

// Получить значение, указывающее как давно были раскодированы данные от GPS модуля
unsigned long GpsProvider::getFixAge() const {
	return _fixAge;
}

// Получить скорость в км/ч
float GpsProvider::getSpeedKmph() const {
	return _speedKmph;
}

// Попытаться прочитать данные с GPS-модуля
bool GpsProvider::_tryReadGps() {
	if (_gpsCyclesLeft != _gpsCyclesLeftBound) {
		return false;
	}

	while (_gpsSerial.available()) {
		int ch = _gpsSerial.read();

		if (_gps.encode(ch)) {
			return true;
		}
	}

	return false;
}

// Присвоить раскодированные данные переменным объекта
void GpsProvider::_assignGpsData() {
	_gps.get_position(&_latitude, &_longitude, &_fixAge);
	_gps.f_get_position(&_fLatitude, &_fLongitude, &_fixAge);
	_speedKmph = _gps.f_speed_kmph();
}