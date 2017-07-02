#include <Wire.h>

const int ledPin = 13;                // сетодиод
const int speakerPin = 9;
const int btnPin = 2;                 // кнопка
const int toneFrequency = 4000;

bool isAlarm = false;

void setup() {
  pinMode(ledPin, OUTPUT);            // это выход - светодиод
  pinMode(speakerPin, OUTPUT);
  pinMode(btnPin, INPUT);             // а это вход - кнопка

  Wire.begin(); // подключение к шине i2c
}

void loop() {
  if (digitalRead(btnPin) == HIGH) {
    isAlarm = !isAlarm;
  }
  if (isAlarm) {
    digitalWrite(ledPin, HIGH);       // зажигаем светодиод
    tone(speakerPin, toneFrequency);  // выдаём на 12 пине сигнал с частотой 2400 Гц
  } else {
    digitalWrite(ledPin, LOW);        // зажигаем светодиод
    noTone(speakerPin);
  }
  delay(200);
}
