#include <ESP8266WiFi.h>

const char* ssid = "********";
const char* password = "********";

WiFiServer server(23);
WiFiClient telnet;

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  Serial.begin(9600);
  server.begin();
  server.setNoDelay(true);
}

void loop() {
  if (server.hasClient()){
    if (!telnet || !telnet.connected()){
      if(telnet) telnet.stop();
      telnet = server.available();
    }
    else{
      server.available().stop();
    }
  }

  if (telnet && telnet.connected() && telnet.available()){
    while(telnet.available()){
      Serial.write(telnet.read());
    }
  }

  if (Serial.available()){
    if (telnet && telnet.connected()){
      while(Serial.available()){
        telnet.write(Serial.read());
      }
    }
  }
}
