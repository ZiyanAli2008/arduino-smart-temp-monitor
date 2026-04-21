#include "DHT.h"

#define DHTPIN A2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int buzzer = 8;

const int green = 6;
const int yellow = 5;
const int red = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(buzzer, OUTPUT);

  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float humidity = dht.readHumidity();
  float temperatureF = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temperatureF)) {
    Serial.println("Error reading data!");
    delay(2000);
    return;
  }

  if (temperatureF >= 80) {
    tone(buzzer, 1000, 300);
  } else {
    noTone(buzzer);
  }

  if (temperatureF <= 77) { 
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  } else if (temperatureF > 77 && temperatureF < 80) {
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
  } else {
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
  }

  Serial.println("Temperature: " + String(temperatureF) + "F");
  Serial.println("Humidity: " + String(humidity) + "%");
  delay(2000);
}
