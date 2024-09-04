#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace wifi
{
  const char* SSID = "Единый Разум 2,4";
  const char* PASSWORD = "amogusabobus";
} // namespace wifi

namespace server
{
  const char* CLIENT_ID = "ESP8266Client-led";
  const char* IP = "192.168.32.104";
  const int PORT = 1883;
} // namespace server

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setupWifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(wifi::SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi::SSID, wifi::PASSWORD);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived from '");
  Serial.print(topic);
  Serial.print("': ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");

  if ((char)payload[0] == '1') {
    digitalWrite(16, LOW);
  } else {
    digitalWrite(16, HIGH);
  }
}

void reconnect()
{
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(server::CLIENT_ID, "espuser", "esppassword")) {
      Serial.println("connected");
      mqttClient.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(16, OUTPUT);
  Serial.begin(115200);
  setupWifi();
  mqttClient.setServer(server::IP, server::PORT);
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}