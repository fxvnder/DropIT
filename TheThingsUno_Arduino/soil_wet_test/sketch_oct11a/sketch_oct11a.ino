long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

const int dry = 515;
const int wet = 190;

uint8_t i=0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorVal = analogRead(A0);
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0);

  Serial.print("\n");
  Serial.print(percentageHumidity);
  Serial.print("% HUMIDADE");
  Serial.print(sensorVal);

  if(percentageHumidity >= 30){
    Serial.print(" - Molhado");
  } else {
    Serial.print(" - Seco");
  }
  
  delay(2000); // 2 segs
}
