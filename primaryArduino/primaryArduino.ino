#include <SoftwareSerial.h>
#define RXLCD 2
#define TXLCD 3

SoftwareSerial mySerial(RXLCD, TXLCD);

byte Buffer[20];
byte Buffer_len = 0;
unsigned char flag = 0;
int SPEED_ADDRESS = 0x10;
int BATTERY_ADDRESS = 0x11;
int PSENSOR_ADDRESS = 0x12;
int CARLOCK_ADDRESS = 0x13;
int LIGHTS_ADDRESS = 0x14;
int FLASHER_ADDRESS = 0x15;
int HORN_ADDRESS = 0x16;

int batteryVoltage = 0;
byte lockState = 0;
int distance = 0;
int speed = 0;

int frontLightsPin = 9;
int flasherPin = 8;
int hornPin = 7;
int lockPin = 6;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(frontLightsPin, OUTPUT);
  pinMode(flasherPin, OUTPUT);
  pinMode(hornPin, OUTPUT);
  pinMode(lockPin, INPUT);
}

void loop() {
  if (Serial.available()) {
    batteryVoltage = Serial.parseInt();
    speed = Serial.parseInt();
    distance = Serial.parseInt();
    lockState = Serial.parseInt();
  }

  lockState = digitalRead(lockPin);

  // Send to LCD
  DISPLAY_send_Int(batteryVoltage, BATTERY_ADDRESS);
  DISPLAY_send_Int(speed, SPEED_ADDRESS);
  DISPLAY_send_Int(distance, PSENSOR_ADDRESS);
  DISPLAY_send_Int(lockState, CARLOCK_ADDRESS);

  // Read from LCD
  Display_switchRead(LIGHTS_ADDRESS);
  Display_switchRead(FLASHER_ADDRESS);
  Display_switchRead(HORN_ADDRESS);

  delay(50);
}

void Display_switchRead(int address) {
  if (mySerial.available()) {
    Buffer[Buffer_len] = mySerial.read();
    Buffer_len++;
    flag = 1;
  } else {
    if (flag == 1) {
      if (Buffer[0] == 0x5A) {
        //////////////////
        if (Buffer[4] == LIGHTS_ADDRESS) {
          digitalWrite(frontLightsPin, (bitRead(Buffer[8], 0)));
        } else if (Buffer[4] == FLASHER_ADDRESS) {
          digitalWrite(flasherPin, (bitRead(Buffer[8], 0)));
        } else if (Buffer[4] == HORN_ADDRESS) {
          digitalWrite(hornPin, (bitRead(Buffer[8], 0)));
        }
      }
      Buffer_len = 0;
      flag = 0;
    }
  }
}
void DISPLAY_send_Int(int data, int address) {
  mySerial.write(0x5A);
  mySerial.write(0xA5);
  mySerial.write(0x05);
  mySerial.write(0x82);
  mySerial.write(address);
  mySerial.write((byte)0x00);
  mySerial.write(highByte(data));
  mySerial.write(lowByte(data));
}

