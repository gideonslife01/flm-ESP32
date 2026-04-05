const int sensorPin = 34; // GPIO34 (ADC1)

void setup() {
  Serial.begin(115200);
}

void loop() {
  int value = analogRead(sensorPin); // 0~4095
  Serial.println(value);
  delay(500);
}
