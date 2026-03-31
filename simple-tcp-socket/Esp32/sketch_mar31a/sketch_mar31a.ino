#include <WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// ipaddress of the server (PC)
const char* host = "192.168.0.100";
const uint16_t port = 3000;

WiFiClient client;

void connectToServer() {
  Serial.print("Connecting to server...");
  if (client.connect(host, port)) {
    Serial.println("connected");
  } else {
    Serial.println("failed");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }

  Serial.print("WiFi OK. IP: ");
  Serial.println(WiFi.localIP());

  connectToServer();
}

void loop() {
  // 끊겼으면 재연결 / Reconnect if disconnected
  if (!client.connected()) {
    client.stop();
    connectToServer();
    delay(1000);
    return;
  }

  // ESP32 → 서버로 메시지 보내기 / Send message from ESP32 to server
  client.println("sensor=42");

  // 서버 → ESP32 응답 읽기 / Read response from server to ESP32  
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.print("Server: ");
    Serial.println(line);
  }

  delay(2000);
}
