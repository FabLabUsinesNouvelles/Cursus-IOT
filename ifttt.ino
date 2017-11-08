//Import des bibliothèques ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* host = "maker.ifttt.com";
const char* url = "/trigger/temp/with/key/IWCT5W_75j5itNQYNSOWD";
const char* ssid     = "Fablab Usines Nouvelles";
const char* password = "usinesnouvelles";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  send_json( host, url, "12", "12", "44");
  delay(5000);
}

void send_json(const char* host_in, String url_in, String data1, String data2, String data3) {
  String contentType = "application/json";
  String json = "{";
  json += "\"value1\":\"" + data1 + "\"";
  json += ", \"value2\":\"" + data2 + "\"";
  json += ", \"value3\":\"" + data3 + "\"";
  json += "}";
  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host_in, httpPort)) {
    Serial.print("Requesting URL error: ");
    //stream = "false";
    return;
  }

  Serial.print("Requesting URL: ");
  Serial.println(url_in);

  // This will send the request to the server
  client.print(String("GET ") + url_in + " HTTP/1.1\r\n" +
               "Host: " + host_in + "\r\n" +
               "Cache-Control: no-cache" + "\r\n" +
               "Content-Type: " + contentType + "\r\n" +
               "Content-Length: " + json.length() + "\r\n" +
               "\r\n" +
               json + "\r\n" +
               "Connection: close\r\n\r\n");
}

