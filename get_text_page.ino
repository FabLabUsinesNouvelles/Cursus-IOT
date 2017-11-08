/*
   Lecteur de page HTML,
   Pour changer la valeur de la page envoyer cette requete :
   http://moumoute.biz/IOT/iot.php?nom=fablab&txt=ON

*/

#include <ESP8266WiFi.h>

const char* ssid     = "Fablab Usines Nouvelles";
const char* password = "usinesnouvelles";

const char* host = "moumoute.biz";
const char* url = "/IOT/fablab";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}


void loop() {
  delay(5000);
  String reponse = get_page_text(host, url);
  Serial.println(reponse);
  if(reponse.equals("ON")==true){
    Serial.println("yeah");
  }

}

String get_page_text(const char* host, const char* url) {
  WiFiClient client;
  const int httpPort = 80;
  client.connect(host, httpPort);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  String lines;
  while (client.available()) {
    lines = client.readStringUntil('\r');
    lines = lines.substring(1, lines.length() );
  }
  return lines;
}

