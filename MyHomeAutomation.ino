#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
// Set these to run example.
#define WIFI_SSID "OnePlus"
#define WIFI_PASSWORD "vishal69"

void setup() {
  Serial.begin(115200);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Firebase.begin("autocure-home.firebaseio.com", "f9gd8731V4n8Asrhxbxo0koxbbA5mqDMcHzx3QAy");
  bool value = Firebase.getBool("light");
  Serial.println("light current status");
  Serial.println(value);
  digitalWrite(D1, value);
  Firebase.stream("/steamschool");  
}


void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  
  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     String eventType = event.getString("type");
     eventType.toLowerCase();
     Serial.print(eventType);
     if (eventType == "put") {
      String path = event.getString("path");
      bool data = event.getBool("data");
      Serial.println(path);
      Serial.println(data);
      if (path.equals("/light")) {
        if (data) {
          Serial.println("on hua");
          digitalWrite(D1, HIGH);
        } else {
          Serial.println("off hua");
          digitalWrite(D1, LOW);
        }
      }
     }
  }   
}
