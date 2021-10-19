#include "DHT.h"

#define DHTPIN ADC
#define DHTTYPE DHT22

int maxHum = 60;
int maxTemp = 40;

DHT dht(DHTPIN, DHTTYPE);

uint8_t i=0;

void setup() {
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
  delay(2000); // delay = 2 segundos

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("-- ERRO A LER O DHT! --");
    return;
  }

  Serial.print("HUMIDADE: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("TEMPERATURA: "); 
  Serial.print(t);
  Serial.println("C ");

}
