#include <TheThingsNetwork.h>

// DHT22 set-up
#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define fan 4
int maxHum = 60;
int maxTemp = 40;
DHT dht(DHTPIN, DHTTYPE);

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Lora set-up
const char *appEui = "0000000000000000";
const char *appKey = "CB039607F4F66E28D7C22C78A05DAD41";
  
#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868
    
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
    
void setup() {
  pinMode(fan, OUTPUT);
  Serial.begin(9600);
  dht.begin();
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

  // ----------------
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if(h > maxHum || t > maxTemp) {
      digitalWrite(fan, HIGH);
  } else {
     digitalWrite(fan, LOW); 
  }
  Serial.println("DHT22: "); 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

  // separating whole and the decimal parts of the humidity
  int dht_hum_int = (int)h;
  int dht_hum_deci = (int)((h - dht_hum_int)*100);

  // separating whole and the decimal parts of the temprature
  int dht_temp_int = (int)t;
  int dht_temp_deci = (int)((t - dht_temp_int)*100);

  // -----------

  int moistSensorVal = analogRead(A0);
  int wet = 190, dry = 530; // (~ dry: 515, wet: 190)
  Serial.println("Moist sensor readings (0(dry) to 255(wet))");
  int moistness_mapped = map(moistSensorVal, wet, dry, 255, 0); // map to take only one byte
  Serial.println(moistness_mapped);

  // Prepare the data for sending
  byte data[5];
  data[0] = (byte)moistness_mapped;
  data[1] = (byte)dht_hum_int;
  data[2] = (byte)dht_hum_deci;
  data[3] = (byte)dht_temp_int;
  data[4] = (byte)dht_temp_deci;
    
  // Send it off
  ttn.sendBytes(data, sizeof(data));

      
  delay(10000);
}
