#include "CubeCell_NeoPixel.h"
CubeCell_NeoPixel pixels(1, RGB, NEO_GRB + NEO_KHZ800);

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

const int dry = 1230;
const int wet = 760;

uint8_t i=0;

void setup() {
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(i, i, i));
  Serial.begin(9600);
}

void loop() {
  int sensorVal = analogRead(ADC);
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0);

  
  pixels.setPixelColor(0, pixels.Color(0, i, 0));
  Serial.print("\n");
  Serial.print(percentageHumidity);
  Serial.print("% HUMIDADE");

  if(percentageHumidity >= 50){
    pixels.setPixelColor(0, pixels.Color(0, 0, i));
    Serial.print(" - Molhado");
  } else {
    pixels.setPixelColor(0, pixels.Color(i, i, i));
    Serial.print(" - Seco");
  }
  
  delay(2000); // 2 segs
}
