#include "CubeCell_NeoPixel.h"
CubeCell_NeoPixel pixels(1, RGB, NEO_GRB + NEO_KHZ800);

#include "DHT.h"

#define DHTPIN ADC
#define DHTTYPE DHT22

int maxHum = 60;
int maxTemp = 40;

DHT dht(DHTPIN, DHTTYPE);

uint8_t i=0;

void setup() {
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(i, i, i));
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
  delay(2000); // delay = 2 segundos

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    pixels.setPixelColor(0, pixels.Color(i, 0, 0));
    pixels.show();
    Serial.println("-- ERRO A LER O DHT! --");
    return;
  }

  pixels.setPixelColor(0, pixels.Color(0, i, 0));
  pixels.show();
  
  Serial.print("HUMIDADE: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("TEMPERATURA: "); 
  Serial.print(t);
  Serial.println("C ");

}
