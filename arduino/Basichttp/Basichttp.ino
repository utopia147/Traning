
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "Rawliet";
const char* password = "34073408";
String host = "192.168.0.101";

int ch[] = {16, 5}; 
void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  pinMode(ch[0] , OUTPUT);
  pinMode(ch[1] , OUTPUT);
}

void loop() {
  WiFiClient client;
  HTTPClient http;
  // wait for WiFi connection
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://" + host + "/iot1/api/read.php")) { // HTTP


    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
        DynamicJsonDocument doc(4080);
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          return;
        }
        for (int i = 0; i <= 1; i++) {
          int relay = doc[i]["relayid"];
          int statusRelay = doc[i]["status"];
          Serial.print("Relay: ");
          Serial.print(relay);
          Serial.println();
          Serial.print("Status: ");
          Serial.print(statusRelay);
          Serial.println();
      
          digitalWrite(ch[i] , statusRelay);
          
        }

      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

}
