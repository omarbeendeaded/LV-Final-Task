#include <LiquidCrystal.h>
#include <string.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int batteryVoltage = 0;
byte lockState = 0;
int distance = 0;
int speed = 0;

int frontLightsPin = 6;
int flasherPin = 5;
int hornPin = 4;
int lockPin = 3;

bool flasherState = 1;
long prevFlash = 0;
int interval = 50;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 4);
  pinMode(frontLightsPin, OUTPUT);
  pinMode(flasherPin, OUTPUT);
  pinMode(hornPin, OUTPUT);
  pinMode(lockPin, INPUT);
}

void loop() {

  if (Serial.available()) {
    String sVoltage = "";
    String sSpeed = "";
    String sDistance = "";

    int count = -1;
    char data = ' ';
    while (Serial.available() && data != 'F') {
      data = Serial.read();
      if (data == 'X') {
        count++;
        continue;
      } else if (count == 0) {
        sVoltage += data;
      } else if (count == 1) {
        sSpeed += data;
      } else if (count == 2) {
        sDistance += data;
      }
    }

    if (count == 2) {
      batteryVoltage = sVoltage.toInt();
      speed = sSpeed.toInt();
      distance = sDistance.toInt();
    }
  }

  long currentTime = millis();

  if (currentTime - prevFlash >= interval) {
    flasherState = !flasherState;
    digitalWrite(flasherPin, flasherState);
    prevFlash = currentTime;
  }

  digitalWrite(frontLightsPin, HIGH);
  digitalWrite(hornPin, HIGH);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Battery: ");
  lcd.print(batteryVoltage);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.print(speed);
  lcd.print(" km/h");

  lcd.setCursor(0, 2);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" m");

  lcd.setCursor(0, 3);
  lcd.print("Lock: ");
  lcd.print(digitalRead(lockPin));

  delay(100);
}