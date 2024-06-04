#define BLYNK_TEMPLATE_ID "TMPL3g1INsi2a"
#define BLYNK_TEMPLATE_NAME "Air Quality Monitoring Interface"
#define BLYNK_AUTH_TOKEN "twx2juS_P477MvO4aEB83G3MpF1E1TpH"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <ArduinoJson.h>



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wi-Feynman";
char pass[] = "Ganapati1234";

// Your Blynk Auth Token
char auth[] = "twx2juS_P477MvO4aEB83G3MpF1E1TpH";

// GPIO Pin for MQ135
#define MQ135_PIN A0

// GPIO Pin for DHT11
#define DHT11_PIN D1

// DHT11 Object
DHT dht(DHT11_PIN, DHT11);

void setup() {
 Serial.begin(9600);

 // Blynk Connection
 Blynk.begin(auth, ssid, pass);

 // MQ135 Sensor Calibration
 pinMode(MQ135_PIN, INPUT);

 // DHT11 Sensor
 dht.begin();
}

void loop() {
 Blynk.run();

 // MQ135 Reading
 int mq135_value = analogRead(MQ135_PIN);

 // DHT11 Reading
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();

 // Print Values to Serial Monitor
 Serial.print("MQ135: ");
 Serial.println(mq135_value);

 Serial.print("DHT11 Humidity: ");
 Serial.println(humidity);

 Serial.print("DHT11 Temperature: ");
 Serial.println(temperature);

 // Blynk Connection Check
 if (Blynk.connected()) {
    // Send MQ135 Sensor Value to Virtual Pin V0
    Blynk.virtualWrite(V0, mq135_value);

    // Send DHT11 Sensor Values to Virtual Pins V1 and V2
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, temperature);
 } else {
    Serial.println("Blynk Not Connected");
 }

 delay(2000);
}