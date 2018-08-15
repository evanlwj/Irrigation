int segA = 1;
int segB = 2;
int segC = 3;
int segD = 4;
int segE = 5;
int segF = 6;
int segG = 7;
int segP = 8;

int dig1 = 10;
int dig2 = 11;
int dig3 = 12;
int dig4 = 13;

int relay = 9;

int elapsed = millis() / 1000;

void showNumber(byte num) {
  switch (num) {
    case 0:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      break;
    case 1:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
    case 2:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;
    case 3:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;
    case 4:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 5:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 6:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 7:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
    case 8:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 9:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    default:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
  }
}

void selectDigits(byte dig) {
  if (dig & 1)
    digitalWrite(dig1, LOW);
  else
    digitalWrite(dig1, HIGH);

  if (dig & 2)
    digitalWrite(dig2, LOW);
  else
    digitalWrite(dig2, HIGH);

  if (dig & 4)
    digitalWrite(dig3, LOW);
  else
    digitalWrite(dig3, HIGH);

  if (dig & 8)
    digitalWrite(dig4, LOW);
  else
    digitalWrite(dig4, HIGH);
}

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segP, OUTPUT);

  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(dig4, OUTPUT);

  pinMode(relay, OUTPUT);
}

void loop() {
  int current = elapsed;
  int minutes = current / 60;
  int seconds = current % 60;
  int hours   = minutes / 60 % 24;
  int refresh = 5000;
//  byte d1 = minutes % 60 / 10;
//  byte d2 = minutes % 10;
//  byte d3 = seconds / 10;
//  byte d4 = seconds % 10;
  byte d1 = (24 - hours) / 10;
  byte d2 = (24 - hours) % 10 - 1;
  byte d3 = (60 - minutes % 60) / 10 - 1;
  byte d4 = 9 - minutes % 10;
  bool sp = current & 1 == 1 ? HIGH : LOW;
  while (current == elapsed) {
    selectDigits(1);
    showNumber(d1);
    digitalWrite(segP, LOW);
    delayMicroseconds(refresh);
    selectDigits(2);
    showNumber(d2);
    digitalWrite(segP, sp);
    delayMicroseconds(refresh);
    selectDigits(4);
    showNumber(d3);
    digitalWrite(segP, LOW);
    delayMicroseconds(refresh);
    selectDigits(8);
    showNumber(d4);
    digitalWrite(segP, LOW);
    delayMicroseconds(refresh);
    elapsed = millis() / 1000;
  }
  digitalWrite(relay, sp);
}

