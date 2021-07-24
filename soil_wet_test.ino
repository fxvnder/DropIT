
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

const int dry = 1230; //value for dry sensor
const int wet = 760; //value for dry sensor

void setup() {
  // setup code

  Serial.begin(9600);
}

void loop() {
  // main code
  // Serial.println(analogRead(ADC)); //directly extract the reciven value
  int sensorVal = analogRead(ADC);

  // More info: https://www.arduino.cc/reference/en/language/functions/math/map/
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0);

  Serial.print("\n");
  Serial.print(percentageHumidity);
  Serial.print("% HÚMIDO");

  if(percentageHumidity >= 50){
    Serial.print(" - Molhado");
  } else Serial.print(" - Seco");
  
  delay(500);
}
