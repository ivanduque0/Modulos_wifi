#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "your-ssidd"
#define STAPSK  "your-passwordd"
#endif

const char* ssid = "repetidorprueba";
const char* password = "1234567890";

const int led = 2;
const int buzzer = 0;
ESP8266WebServer server(80);

void abrir() {
  digitalWrite(led, HIGH);
  server.send(200, "text/plain", "Abriendo acceso!\r\n");
    //delay(2000);
    tone(buzzer, 523);
    delay(200);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 523);
    delay(200);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 523);
    delay(200);
    noTone(buzzer);

  digitalWrite(led, LOW);
  //digitalWrite(led, 0);
}

void cerrar() {
  //digitalWrite(led, 1);
  server.send(200, "text/plain", "Cerrando acceso!\r\n");
  tone(buzzer, 523);
  delay(1000);
  noTone(buzzer);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/on", abrir);

  server.on("/off", cerrar);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
