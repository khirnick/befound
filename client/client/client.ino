#include "Manager.h"
#include "Params.h"

Manager manager(GPS_RX, GPS_TX, BTN_PIN, GPS_CYCLES_LEFT_BOUND);

// »нициализаци€ программы, выполн€юща€с€ только один раз
void setup() {
	Serial.begin(9600);
	manager.init();

	while (!Serial);

	if (!manager.init()) {
		Serial.println("Init failed");

		return;
	}

	Serial.print("besaved v. ");
	Serial.print(VERSION);
	Serial.println(" | Client side started. Monitoring GPS data started...");
}

// ќсновной цикл программы, работающий бесконечно
void loop() {
	String gpsDataCoordAgeSpeedRow = manager.startGetDataAndSend();

	if (gpsDataCoordAgeSpeedRow != GpsProvider::NONE_DATA) {
		Serial.println(gpsDataCoordAgeSpeedRow);
	}	
}