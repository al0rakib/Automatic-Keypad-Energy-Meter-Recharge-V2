#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

ESP8266WebServer server(80);

void handleSubmit() {
  String msg = server.hasArg("code") ? server.arg("code") : "none";
  server.send(200, "text/plain", "Received: " + msg);
  Serial.println("Code: " + msg);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.on("/submit", handleSubmit);
  server.begin();
}

void loop() {
  server.handleClient();
}