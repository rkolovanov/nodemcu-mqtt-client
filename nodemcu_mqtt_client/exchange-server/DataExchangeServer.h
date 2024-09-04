#ifndef DATA_EXCHANGE_SERVER_H
#define DATA_EXCHANGE_SERVER_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class DataExchangeServer
{
public:
  DataExchangeServer();

  bool connect(const char* ssid, const char* password, float timeout);
  void exec();

private:
  WiFiClient m_server;
  PubSubClient m_mqttClient;
};

#endif DATA_EXCHANGE_SERVER_H
