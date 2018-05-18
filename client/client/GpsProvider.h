#pragma once

#include <TinyGPS.h>
#include <SoftwareSerial.h>

class GpsProvider
{
public:
	static const String NONE_DATA;

	const String GPS_DATA = "GPS Data |";
	const String LATITUDE_INFO = " LAT:";
	const String LONGITUDE_INFO = " LONG:";
	const String AGE = " FIX_AGE:";
	const String SPEED = " SPEED:";
	const String DATE = " DATE";

	GpsProvider(uint8_t GpsRx, uint8_t GpsTx, uint8_t gpsCyclesLeftBound) : _gpsSerial(GpsRx, GpsTx), _gpsCyclesLeftBound(gpsCyclesLeftBound) {}
	~GpsProvider() {};

	void beginSerial();
	void initLoopStarted(long loopStarted);

	String tryGetNewData();
	String getGpsDataCoordAgeSpeedRow() const;

	bool getNewDataCame() const;
	long getLatitude() const;
	long getLongitude() const;
	float getFLatitude() const;
	float getFLongitude() const;
	unsigned long getFixAge() const;
	float getSpeedKmph() const;

private:
	const uint8_t _gpsCyclesLeftBound;

	bool _isSerialBegan;
	uint8_t _gpsCyclesLeft;

	TinyGPS _gps;
	SoftwareSerial _gpsSerial;
	bool _newDataCame;
	long _loopStarted;

	long _latitude;
	long _longitude;
	float _fLatitude;
	float _fLongitude;
	unsigned long _fixAge;
	float _speedKmph;

	bool _tryReadGps();
	void _assignGpsData();
};

