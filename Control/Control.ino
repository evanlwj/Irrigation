#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);

const int senTemp  = A0;
const int pinRelay = 2;
const int btnMode  = 3;
const int btnPlus  = 4;
const int btnMinus = 5;

const char CLOCK    = 0;
const char TIMER    = 1;
const char DURATION = 2;
const char INTERVAL = 3;

char mode = CLOCK;

const long durationMax = 600;   // 10 minutes
const long durationMin = 5;     //  5 seconds
const long durationGap = 1;
const long intervalMax = 86400; // 24 hours
const long intervalMin = 300;   //  5 minutes
const long intervalGap = 300;

long current   = millis() / 1000;
long countdown = 0;
long duration  = durationMin;
long interval  = 5400;
long lastEvent = current;

void setup() {
  pinMode(btnMode,  INPUT_PULLUP);
  pinMode(btnPlus,  INPUT_PULLUP);
  pinMode(btnMinus, INPUT_PULLUP);
  pinMode(pinRelay, OUTPUT);
  lcd.begin(16, 2);
}

String padNumber (int num) {
  if (num < 10 )
    return "0" + String(num);
  else
    return String(num);
}

bool setMode() {
  if (buttonPressed(btnMode)) {
    mode = mode == INTERVAL ? CLOCK : mode + 1;
    lcd.clear();
    return true;
  }
  return false;
}

bool setValue() {
  if (buttonPressed(btnPlus)) {
    if (mode == DURATION && duration < durationMax) {
      duration = min(durationMax, duration + durationGap);
    }
    else if (mode == INTERVAL && interval < intervalMax) {
      interval = min(intervalMax, interval + intervalGap);
    }
  }
  else if (buttonPressed(btnMinus)) {
    if (mode == DURATION && duration > durationMin) {
      duration = max(durationMin, duration - durationGap);
    }
    else if (mode == INTERVAL && interval > intervalMin) {
      interval = max(intervalMin, interval - intervalGap);
    }
  }
  else {
    return false;
  }
  return true;
}

void showTime(long seconds) {
  byte ss = seconds % 60;
  byte mm = seconds / 60 % 60;
  byte hh = seconds / 3600 % 24;

  String time = padNumber(hh) + ":" + padNumber(mm) + ":" + padNumber(ss);

  lcd.setCursor(4,1);
  lcd.print(time);
}

void showClock() {
  lcd.setCursor(0,0);
  lcd.print("      TIME      ");
  showTime(current);
}

void showDuration() {
  lcd.setCursor(0,0);
  lcd.print("  FOR HOW LONG  ");
  showTime(duration);
}

void showInterval() {
  lcd.setCursor(0,0);
  lcd.print("    ON EVERY    ");
  showTime(interval);
}

void showTimer() {
  lcd.setCursor(0,0);
  lcd.print("      NEXT      ");
  showTime(interval + lastEvent);
}

void showTemperature() {
  lcd.setCursor(0,0);
  lcd.print("  TEMPERATURE   ");
  long tempMVs = (long)analogRead(senTemp) * 1000;
  float degrees = round(tempMVs / 2048.0 - 49.5);
  String celcius = String(degrees, 0) + (char)178 + "C";
  lcd.setCursor(6,0);
  lcd.print(celcius);
}

bool buttonPressed(int button) {
  bool pressed = false;
  while (digitalRead(button) == LOW) {
    delay(10);
    pressed = true;
  }
  return pressed;
}

String centerText(String text, byte width) {
  String result = text;
  if (result.length > width) {
    result.remove(width);
  }
  else {
    while (result.length < width) {
      result = " " + result;
      if (result.length < width) result += " ";
    }
  }
  return result;
}

void loop() {
  
  if (setMode() || setValue()) {
    delay(500); // prevent reading the input continuously
    return;
  }
  
  long now = millis() / 1000;
  
  if (current != now) {

    long elapsed = now - current;
    current = now;

    if (now % interval == 0) {
      digitalWrite(pinRelay, HIGH);
      lastEvent = 0;
      countdown = duration;
    } else {
      lastEvent -= elapsed;
    }

    if (countdown > 0) {
      countdown -= elapsed;
      if (countdown <= 0) {
        digitalWrite(pinRelay, LOW);
      }
    }
    
    switch (mode) {
      case CLOCK:
        showClock();
        break;
      case DURATION:
        showDuration();
        break;
      case INTERVAL:
        showInterval();
        break;
      case TIMER:
        showTimer();
        break;
    }
  }
  delay(100);
}
