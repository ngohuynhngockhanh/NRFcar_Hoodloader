const byte BUTTON_PIN[] = {2, 3, 4, 5};
const byte LED_PIN[] = {6, 7, 8};
const int SENSOR_PIN = A5;
const int MIN_SENSOR = 769;
const int MAX_SENSOR = 1023;
const int RANGE_SENSOR = MAX_SENSOR - MIN_SENSOR;
byte msg;
void setup() {
  Serial.begin(115200);
  for (byte i = 0; i < sizeof(BUTTON_PIN); i++)
    pinMode(BUTTON_PIN[i], INPUT_PULLUP);
  for (byte i = 0; i < sizeof(LED_PIN); i++)
    pinMode(LED_PIN[i], OUTPUT);
  
}

void loop() {
  static int oldSensorValue = 0;
  msg = 0;
  for (byte i = 0; i < sizeof(BUTTON_PIN); i++)
    msg |= (1 && !digitalRead(BUTTON_PIN[i])) << i;
  Serial.write(msg);

  int value = analogRead(SENSOR_PIN);
  if (abs(value - oldSensorValue) > 2) {
    oldSensorValue = value;
    value -= MIN_SENSOR;
    msg = 1 << 7;
    //tắt hết đèn
    for (int i = 0; i < sizeof(LED_PIN); i++)
      digitalWrite(LED_PIN[i], LOW);
    for (int i = 0; i < sizeof(LED_PIN); i++) {
      if (value <= (i + 1) * RANGE_SENSOR / 3) {
        digitalWrite(LED_PIN[i], HIGH);
        msg |= 1 << i;
        Serial.write(msg);
        break;
      }
    }
  }
}
