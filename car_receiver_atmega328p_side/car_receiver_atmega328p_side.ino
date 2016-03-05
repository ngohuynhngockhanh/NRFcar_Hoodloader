byte forward = 0;
byte backward= 0;
byte left = 0;
byte right = 0;
byte threshold = 30;


const int motorA1 = 3;
const int motorA2 = 5;
const int motorB1 = 6;
const int motorB2 = 9;
const int MAX_SPEED = 255;

void setup() {
  Serial.begin(115200);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
}

void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void moveBackward() {
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB2, HIGH);
  digitalWrite(motorB1, LOW);
}

void rotateRight() {
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB2, LOW);
  digitalWrite(motorB1, HIGH);
}

void rotateLeft() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnRight() {
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(motorA1, threshold);
  digitalWrite(motorA2, LOW);
  
}

void turnLeft() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  analogWrite(motorB1, threshold);
  digitalWrite(motorB2, LOW);
}

void backRight() {
  digitalWrite(motorB2, HIGH);
  digitalWrite(motorB1, LOW);
  analogWrite(motorA2, threshold);
  digitalWrite(motorA1, LOW);
  
}

void backLeft() {
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorA1, LOW);
  analogWrite(motorB2, threshold);
  digitalWrite(motorB1, LOW);
}

void stop() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

void controlMotor() {
  if (forward == 1 && left == 1) {
    turnLeft();
  } else if (forward == 1 && right == 1) {
    turnRight();
  } else if (backward == 1 && left == 1) {
    backLeft();
  } else if (backward == 1 && right == 1) {
    backRight();
  } else if (forward == 1) {
    moveForward();
  } else if (backward == 1) {
    moveBackward();
  } else if (left == 1) {
    rotateLeft();
  } else if (right == 1) {
    rotateRight();
  } else 
    stop();
}

void loop() {
  while (Serial.available()) {
    byte msg = Serial.read();
    if ((msg >> 7) == 0) { //di chuyển
      forward = 1 & (msg >> 3);
      backward = 1 & (msg >> 2);
      left = 1 & (msg >> 1);
      right = 1 & msg;
      controlMotor();
    } else { //tốc độ
      threshold = 20;
      for (int i = 2; i >= 0; i--, threshold += 10)
        if (((msg >> i) & 1) == 1)
          break;
    }
  }
}
