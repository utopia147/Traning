
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN 14
#define DHTTYPE DHT11
const char* ssid     = "Rawliet";
const char* password = "34073408";
String host = "192.168.0.101";

DHT dht(DHTPIN, DHTTYPE);

int ch[] = {16, 5};

unsigned long pevDht = 0;
int dhtsend = 1000;
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
  dht.begin();
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
  unsigned long currentDht = millis();
  if (currentDht - pevDht >= dhtsend) {
    pevDht = currentDht;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t) ) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    Serial.println(t);
    Serial.println(h);
    WiFiClient client;
    HTTPClient http;
    String path = "/iot1/api/send.php";
    String url = host + path;
    StaticJsonDocument<256> jsondoc;
    jsondoc["id"] = 1;
    jsondoc["temp"] = t;
    jsondoc["humidity"] = h;
    char postdata[100];
    serializeJson(jsondoc, postdata);
    Serial.println(postdata);

    http.begin(client, "http://" + url);
    http.addHeader("Content-Type", "application/json");
    int httpCodeStatus = http.POST(postdata);
    String payload = http.getString(); //Get the response payload
    //  Serial.printf("[HTTP] POST... code: %d\n", httpCodeStatus); //Print HTTP return code
    //  Serial.println(payload); //Print request response payload
    http.end();
  }

}
