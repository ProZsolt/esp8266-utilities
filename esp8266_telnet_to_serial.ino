#include <ESP8266WiFi.h>

//how many clients should be able to telnet to this ESP8266
const char* ssid = "********";
const char* password = "********";

WiFiServer server(23);
WiFiClient serverClient;

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  Serial.begin(9600);
  server.begin();
  server.setNoDelay(true);
}

void loop() {
  if (server.hasClient()){
    if (!serverClient || !serverClient.connected()){
      if(serverClient){
        serverClient.stop();
      }
      serverClient = server.available();
    }
    else{
      WiFiClient serverClient = server.available();
      serverClient.stop();
    }
  }
  
  if (serverClient && serverClient.connected() && serverClient.available()){
    while(serverClient.available()){
      Serial.write(serverClient.read());
    }
  }

  if (Serial.available()){
    if (serverClient && serverClient.connected()){
      while(Serial.available()){
        serverClient.write(Serial.read());
      }
    }
  }
}
