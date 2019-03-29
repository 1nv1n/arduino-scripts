/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESPAsyncTCP.h>
#include <fauxmoESP.h>

fauxmoESP fauxmo;

#ifndef STASSID
#define STASSID "CERNER_HOTSPOT_X"
#define STAPSK  "PASS"
#endif

int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 1000;

const char* ssid     = STASSID;
const char* password = STAPSK;

//const char* host = "192.168.1.1";
//const uint16_t port = 3000;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
  
  fauxmo.addDevice("coffee one");

  fauxmo.setPort(80); // required for gen3 devices
  fauxmo.enable(true);
  
  pinMode(5, OUTPUT);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if(state) {
      digitalWrite(5, HIGH);
    } else {
      digitalWrite(5, LOW);
    }
  });
}


void loop() {
//  Serial.print("connecting to ");
//  Serial.print(host);
//  Serial.print(':');
//  Serial.println(port);
//
//  // Use WiFiClient class to create TCP connections
//  WiFiClient client;
//
//  if (!client.connect(host, port)) {
//    Serial.println("connection failed");
//    Serial.println("wait 5 sec...");
//    delay(5000);
//    return;
//  }
//
//  // This will send the request to the server
//  client.println("hello from ESP8266");
//
//  //read back one line from server
//  Serial.println("receiving from remote server");
//  String line = client.readStringUntil('\r');
//  Serial.println(line);
//
//  Serial.println("closing connection");
//  client.stop();
//
//  Serial.println("wait 5 sec...");
//  delay(5000);

  fauxmo.handle();

//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis;
//    if (ledState == LOW) {
//      ledState = HIGH;  // Note that this switches the LED *off*
//    } else {
//      Serial.println("Hello, World!");
//      ledState = LOW;  // Note that this switches the LED *on*
//    }
//    digitalWrite(5, ledState);
//  }
}
