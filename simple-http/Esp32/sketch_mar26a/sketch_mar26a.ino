#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_ID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

// 예시 센서값 (나중에 실제 센서 값으로 대체)
int sensorValue = 42;

// 클라이언트가 센서값 요청
void handleGetSensor() {
  String json = "{\"sensor\":" + String(sensorValue) + "}";
  server.send(200, "application/json", json);
}

// 클라이언트가 ESP32에 명령 보내기
void handlePostControl() {
  if (!server.hasArg("plain")) {
    server.send(400, "text/plain", "No body");
    return;
  }
  String body = server.arg("plain");
  Serial.print("RX control: ");
  Serial.println(body);

  // 여기서 body 파싱해서 제어 처리하면 됨
  server.send(200, "text/plain", "OK");
}
// nodejs에서 get방식 정보 받기
void handleControl() {
  if (server.hasArg("led")) {
    String led = server.arg("led");
    Serial.print("LED: ");
    Serial.println(led);
  }
  server.send(200, "text/plain", "OK");
}

// ESP32가 외부 서버로 센서 데이터 보내기
void postToServer() {
  HTTPClient http;
  http.begin("http://192.168.0.100:3000/sensor");
  http.addHeader("Content-Type", "application/json");

  String payload = "{\"sensor\":" + String(sensorValue) + "}";
  int code = http.POST(payload);
  Serial.print("POST result: ");
  Serial.println(code);

  http.end();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/sensor", HTTP_GET, handleGetSensor);
  
  // post
  //server.on("/control", HTTP_POST, handlePostControl);
  
  // get
  server.on("/control", HTTP_GET, handleControl);


  server.begin();
}

void loop() {
  server.handleClient();

  // 5초마다 외부 서버로 센서 데이터 업로드
  static unsigned long lastPost = 0;
  if (millis() - lastPost > 5000) {
    lastPost = millis();
    postToServer();
  }
}
