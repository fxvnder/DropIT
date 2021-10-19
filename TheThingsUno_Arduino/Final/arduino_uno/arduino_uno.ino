#include <TheThingsNetwork.h>

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

const char *appEui = "0000000000000000";
const char *appKey = "CB039607F4F66E28D7C22C78A05DAD41";
    
#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868
    
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
    
void setup() {
  Serial.begin(9600);
  loraSerial.begin(57600);
  debugSerial.begin(9600);
      
  // Initialize LED output pin
  pinMode(LED_BUILTIN, OUTPUT);
    
  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);
    
  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}

void loop() {
  debugSerial.println("-- LOOP");

  int moistSensorVal = analogRead(A0);
  int wet = 190, dry = 530; // (~ dry: 515, wet: 190)
  Serial.println("Moist sensor readings mapped from 0 to 255: (dry: 0, wet: 255)");
  int moistness_mapped = map(moistSensorVal, wet, dry, 255, 0); // map to take only one byte
  Serial.println(moistness_mapped);

  // Prepare the data for sending
  int dht_temprature = 90;
  int dht_humidity = 80;
  byte data[3];
  data[0] = (byte)moistness_mapped;
  data[1] = (byte)dht_temprature;
  data[2] = (byte)dht_humidity;
    
  // Send it off
  ttn.sendBytes(data, sizeof(data));

      
  delay(10000);
}
