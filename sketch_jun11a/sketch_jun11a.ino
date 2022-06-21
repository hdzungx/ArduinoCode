#include <ESP8266WiFi.h>

const char* ssid = "5 nagch 41";

const char* password = "8888899999";

int LED = 13; // LED kết nối với chân D0

WiFiServer server(80);

void setup()

{

  // Khởi động Serial Monitor

  Serial.begin(115200);

  delay(10);

  // Khai báo chân điều khiển LED

  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);

  // Kết nối tới mạng Wifi

  Serial.print("Dang ket noi den mang…");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println("Da ket noi WiFi");

  // Khởi động Server

  server.begin();

  Serial.println("Server da khoi dong");

  Serial.print("Dia chi IP cua mang: "); // In địa chỉ IP trên Serial Monitor

  Serial.println(WiFi.localIP());

  Serial.print("Copy va dan URL nay vao trinh duyet: http://");

  Serial.print(WiFi.localIP());

  Serial.println("/");

}

void loop()

{

  // Kiểm tra nếu có client kết nối

  WiFiClient client = server.available();

  if (!client)

  {

    return;

  }

  // Đợi client gửi dữ liệu

  Serial.println("Co client moi");

  while (!client.available())

  {

    delay(1);

  }

  // Đọc yêu cầu từ client

  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();

  int value = LOW;

  // Kiểm tra yêu cầu là gì

  if (request.indexOf("/LED=ON") != -1)

  {

    digitalWrite(LED, HIGH); // Bật đèn LED

    value = HIGH;

  }

  if (request.indexOf("/LED=OFF") != -1)

  {

    digitalWrite(LED, LOW); // Tắt đèn LED

    value = LOW;

  }

  /*——————Tạo trang HTML———————*/

  client.println("HTTP/1.1 200 OK");

  client.println("Content-Type: text/html");

  client.println("");

  client.println("<!DOCTYPE HTML>");

  client.println("<html>");

  client.print("TRANG THAI CUA DEN LED: ");

  if (value == HIGH)

  {

    client.print("SANG");

  }

  else

  {

    client.print("TAT");

  }

  client.println("<br><br>");

  client.println("<a href=\"/LED=ON\"\"><button>BAT</button></a>");

  client.println("<a href=\"/LED=OFF\"\"><button>TAT</button></a><br />");

  client.println("</html>");

  delay(1);

  Serial.println("Ngat ket noi client");

  Serial.println("");

}
