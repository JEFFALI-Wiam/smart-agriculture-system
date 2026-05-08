#include <DHT.h>

#define DHTPIN D2

#define DHTTYPE DHT22

#define soilPin A0
#define pumpRelay D1
#define fanRelay D5

DHT dht(DHTPIN, DHTTYPE);

int soilValue;

void setup() {

  Serial.begin(115200);
  dht.begin();
  delay(2000);

  pinMode(pumpRelay, OUTPUT);
  pinMode(fanRelay, OUTPUT);

  digitalWrite(pumpRelay, HIGH);
  digitalWrite(fanRelay, HIGH);
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  soilValue = analogRead(soilPin);

  Serial.print("Soil: ");
  Serial.println(soilValue);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT error");
  } else {

    Serial.print("Temp: ");
    Serial.println(temperature);

    Serial.print("Hum: ");
    Serial.println(humidity);
    
  }

  // irrigation
  if (soilValue > 500) {
    digitalWrite(pumpRelay, LOW);
    Serial.println("Pompe ON");
  } else {
    digitalWrite(pumpRelay, HIGH);
    Serial.println("Pompe OFF");
  }

  // ventilateur
  if (temperature > 10) {
    digitalWrite(fanRelay, LOW);
    Serial.println("Fan ON");
  } else {
    digitalWrite(fanRelay, HIGH);
    Serial.println("Fan OFF");
  }

  delay(2000);
}
