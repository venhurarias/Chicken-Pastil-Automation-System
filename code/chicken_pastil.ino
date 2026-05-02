#include <Streaming.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Chrono.h>

#define HEATER_PIN 7
#define VALVE_PIN 6
#define PILOT_PIN 8
#define MOTOR_A_PIN 9
#define MOTOR_B_PIN 10
#define SPINNER_PIN 11
#define BUTTON_PIN A2
#define LIMIT_RET_PIN A0
#define LIMIT_EXT_PIN A3
#define BUZZER_PIN 13


#define HEATER_TIME 20000
#define VALVE_TIME 20000
#define MOTOR_TIME 20000
#define SPINNER_TIME 20000
#define HEATER_REST_TIME 300000

LiquidCrystal_I2C lcd(0x27, 20, 4);
Chrono myChrono, buzzerChrono, heaterChrono;

bool isBuzzerOn = false;


int mode = -1;
void setup() {
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);
  pinMode(PILOT_PIN, OUTPUT);
  pinMode(MOTOR_A_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN, OUTPUT);
  pinMode(SPINNER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LIMIT_RET_PIN, INPUT_PULLUP);
  pinMode(LIMIT_EXT_PIN, INPUT_PULLUP);
  allOff();
  Serial.begin(9600);
  Serial.setTimeout(100);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0), lcd << F("====================");
  lcd.setCursor(0, 1), lcd << F("       CHICKEN      ");
  lcd.setCursor(0, 2), lcd << F("       PASTIL       ");
  lcd.setCursor(0, 3), lcd << F("====================");
  delay(2000);
}

void loop() {
  // Serial << "Button :: " << isButtonPress() << "\t\tLimit RET :: " << isLimitRetPress() << "\t\tLimit EXT :: " << isLimitExtPress() << endl;
  // testing();
  // normalProccess();
}

void normalProccess() {

  switch (mode) {
    case -1:
      motorCCW();
      if (isLimitRetPress()) {
        motorOff();
        mode = 0;
      }
      break;

    case 0:
      lcd.setCursor(0, 0), lcd << F("====================");
      lcd.setCursor(0, 1), lcd << F("     PRESS START    ");
      lcd.setCursor(0, 2), lcd << F("                    ");
      lcd.setCursor(0, 3), lcd << F("====================");
      if (isButtonPress()) {
        mode = 10;
        myChrono.restart();
        heaterChrono.restart();
        buzzerOn();
        delay(500);
        buzzerOff();
        delay(500);
        buzzerOn();
        delay(500);
        buzzerOff();
        delay(500);
      }
      break;

    case 10:
      heaterOn();
      if (heaterChrono.hasPassed(HEATER_REST_TIME)) {
        heaterChrono.restart();
        heaterOff();
        delay(10000);
      }
      if (myChrono.hasPassed(HEATER_TIME)) {
        myChrono.restart();
        heaterOff();
        mode = 20;
      }

      break;

    case 20:
      valveOn();
      if (myChrono.hasPassed(VALVE_TIME)) {
        myChrono.restart();
        valveOff();
        mode = 30;
      }
      break;

    case 30:
      motorCW();
      if (isLimitExtPress()) {
        if (myChrono.hasPassed(MOTOR_TIME)) {
          myChrono.restart();
          mode = 40;
        }
        motorOff();
      } else {
        myChrono.restart();
      }
      break;

    case 40:
      motorCCW();
      if (isLimitRetPress()) {
        myChrono.restart();
        motorOff();
        mode = 50;
      }
      break;

    case 50:
      spinnerOn();
      if (myChrono.hasPassed(SPINNER_TIME)) {
        myChrono.restart();
        spinnerOff();
        mode = 60;
      }
      break;

    case 60:
      buzzerAlarm();
      if (isButtonPress()) {
        buzzerOff();
        mode = 70;
        delay(500);
      }
      break;

    case 70:
      if (!isButtonPress()) {
        mode = 0;
      }
      break;
  }
}


void testing() {
  if (Serial.available()) {
    String reading = Serial.readString();
    reading.trim();
    Serial << reading << endl;
    if (reading == "0") {
      Serial << "All OFF" << endl;
      allOff();
    } else if (reading == "q") {
      Serial << "Heater On" << endl;
      heaterOn();
    } else if (reading == "w") {
      Serial << "Valve On" << endl;
      valveOn();
    } else if (reading == "e") {
      Serial << "Pilot On" << endl;
      pilotOn();
    } else if (reading == "r") {
      Serial << "Motor CW" << endl;
      motorCW();
    } else if (reading == "t") {
      Serial << "Motor CCW" << endl;
      motorCCW();
    } else if (reading == "y") {
      Serial << "Spinner On" << endl;
      spinnerOn();
    } else if (reading == "u") {
      Serial << "Buzzer On" << endl;
      buzzerOn();
    }
  }
}

void buzzerAlarm() {
  if (buzzerChrono.hasPassed(1000)) {
    buzzerChrono.restart();
    if (isBuzzerOn) {
      buzzerOff();
      pilotOff();
    } else {
      buzzerOn();
      pilotOn();
    }
  }
}


void allOff() {
  heaterOff();
  valveOff();
  pilotOff();
  motorOff();
  spinnerOff();
  buzzerOff();
}

void buzzerOn() {
  digitalWrite(BUZZER_PIN, HIGH);
}

void buzzerOff() {
  digitalWrite(BUZZER_PIN, LOW);
}

void heaterOn() {
  digitalWrite(HEATER_PIN, HIGH);
}

void heaterOff() {
  digitalWrite(HEATER_PIN, LOW);
}

void valveOn() {
  digitalWrite(VALVE_PIN, HIGH);
}

void valveOff() {
  digitalWrite(VALVE_PIN, LOW);
}

void pilotOn() {
  digitalWrite(PILOT_PIN, LOW);
}

void pilotOff() {
  digitalWrite(PILOT_PIN, HIGH);
}

void motorCW() {
  digitalWrite(MOTOR_A_PIN, HIGH);
  digitalWrite(MOTOR_B_PIN, LOW);
}

void motorCCW() {
  digitalWrite(MOTOR_A_PIN, LOW);
  digitalWrite(MOTOR_B_PIN, HIGH);
}

void motorOff() {
  digitalWrite(MOTOR_A_PIN, HIGH);
  digitalWrite(MOTOR_B_PIN, HIGH);
}


void spinnerOn() {
  digitalWrite(SPINNER_PIN, HIGH);
}

void spinnerOff() {
  digitalWrite(SPINNER_PIN, LOW);
}

bool isButtonPress() {
  return !digitalRead(BUTTON_PIN);
}

bool isLimitRetPress() {
  return !digitalRead(LIMIT_RET_PIN);
}

bool isLimitExtPress() {
  return !digitalRead(LIMIT_EXT_PIN);
}
