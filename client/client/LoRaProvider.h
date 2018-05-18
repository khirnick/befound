#pragma once

#include <RH_RF95.h>

class LoRaProvider {
public:
	LoRaProvider() {}
	~LoRaProvider() {}

	bool init();

	void sendData(String data);
	void reset();
private:
	RH_RF95 _rf95;
};
