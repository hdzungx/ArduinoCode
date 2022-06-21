#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <DHT.h>

#define DHTPIN 2// chan vat ly
#define DHTTYPE DHT11//bat ctr +shif +m hien thi man hinh
DHT dht(DHTPIN,DHTTYPE);
const char *ssid ="5 nagch 41"; //tên wifi 
const char *password = "8888899999";//pass wifi
void setup() {
Serial.begin(9600);
WiFiServer server(80);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);// khoi tao wifi
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

server.begin();
Serial.println("Server started");
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
dht.begin();
}
void loop() {
WiFiClient client = Server.available();
float h = dht.readHumidity();
float t = dht.readTemperature();
WiFiClient client = server.available();
if (!client) {
return;
}
Serial.println("new client");
while(!client.available()){
delay(1);
}
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head><title> YASUO </title></head>");
client.println("<body>");
client.println("<H5>Thong tin nhiet do va do am :</H5>");
client.println("<H3 style='color:#339966'>Nhiet do la :");
client.println(t);
client.println("*C");
client.println("</H3>");
client.println("<H3 style='color:#339966'>Do am la: ");
client.println(h);
client.println("%");
client.println("</H3>");
client.println("</body>");
client.println("</html>");
delay(20);
Serial.println("Client disonnected");
Serial.println("");
delay(1000);
}
