#pragma once

#include "GpsProvider.h"
#include "LoRaProvider.h"

class Manager {
public:
	Manager(uint8_t GpsRx, uint8_t GpsTx, uint8_t btnPin, uint8_t gpsCyclesLeftBound) : _gpsProvider(GpsRx, GpsTx, gpsCyclesLeftBound), _btnPin(btnPin) {}
	~Manager() {}
	
	bool init();
	String startGetDataAndSend();
	String getPacketData();

	void sendDataByLoRa(String data);
private:
	uint8_t _btnPin;
	uint8_t _btnStatus;
	GpsProvider _gpsProvider;
	LoRaProvider _loRaProvider;

	bool _initLoRa();
	void _stringToByteArray(String str, byte arr[], int size);
};
