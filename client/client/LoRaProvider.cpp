#include "LoRaProvider.h"
#include "Params.h"

// Инициализация LoRa
bool LoRaProvider::init() {
	pinMode(9, OUTPUT);

	reset();

	if (_rf95.init()) {
		_rf95.setFrequency(LORA_FREQ);
		_rf95.setTxPower(14, false);
		_rf95.setPromiscuous(true);
		_rf95.setThisAddress(LORA_SEND_FROM_ID);
		_rf95.setHeaderFrom(LORA_SEND_FROM_ID);
		_rf95.setHeaderTo(LORA_SEND_TO_ID);

		Serial.print("LoRa init successful.\nFrequency: ");
		Serial.print(LORA_FREQ);
		Serial.print("; From node id: ");
		Serial.print(LORA_SEND_FROM_ID);
		Serial.print("; To send id: ");
		Serial.println(LORA_SEND_TO_ID);

		return true;
	}
	return false;
}

// Отправить данные по БС LoRa
void LoRaProvider::sendData(String data) {
	const int dataLen = data.length();
	uint8_t dataBytes[dataLen];

	for (int i = 0; i < data.length(); i++) {
		dataBytes[i] = data[i];		
	}

	_rf95.send(dataBytes, data.length());

	bool checkSending = _rf95.waitPacketSent();
	
	if (checkSending) {
		Serial.print("Packet sent by LoRa | ");
		Serial.print("size: ");
		Serial.println(dataLen);
	}
}

void LoRaProvider::reset() {
	digitalWrite(9, LOW);
	delay(1000);
	digitalWrite(9, HIGH);
}
