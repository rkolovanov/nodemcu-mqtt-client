#include "DataExchangeServer.h"

namespace
{
  const unsigned int WIFI_STATUS_DELAY_MS = 50;
} // namespace

DataExchangeServer::DataExchangeServer():
  m_mqttClient("192.168.32.104", 8883, m_server)
{}

bool DataExchangeServer::connect(const char* ssid, const char* password, float timeout)
{
  WiFi.begin(ssid, password);

  float startTime = millis();
  while(WiFi.status() != WL_CONNECTED && (millis() - startTime) < timeout)
  {
    delay(WIFI_STATUS_DELAY_MS);
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());

  if (!m_mqttClient.connect("radclient", "rkolovanov", "196618")) {
    Serial.print("not connected");
  }
  else {
    m_mqttClient.publish("outTopic","hello world");
  }

  return WiFi.status() == WL_CONNECTED;
}

void DataExchangeServer::exec()
{
  
}
