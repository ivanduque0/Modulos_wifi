#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#define LED_Green 12
#define LED_Red 16
const char* ssid     = "ALC_Oficina";
const char* password = "S3gur1c3l_99";
const char* remote_host = "192.168.0.124";
void setup() {
  
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.println("");
  Serial.println("Connecting to WiFi");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    
    delay(100);
    Serial.print(".");
    
  }
  Serial.println("");
  Serial.print("Local IP Address: ");  
  Serial.print(WiFi.localIP());
  Serial.println("");
  Serial.print("Pinging: ");
  Serial.print(remote_host);
  Serial.println("");
  Serial.println("");
}
void loop() { 
  
    if(Ping.ping(remote_host)) {
    Serial.println("Online");
    //delay(1000);

  } else {
    
    Serial.println("Offline");
    //delay(1000);
    
  }}
