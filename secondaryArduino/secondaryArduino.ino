#define RX 0
#define TX 1

int batteryPin = A1;
int batteryVoltage = 0;
int rawVoltage = 0;

int sensorTrig = 8;
int sensorEcho = 9;
long time, distance;

const int potPin = A0;
int potValue = 0;
int speed = 0;


void setup() {
  Serial.begin(9600);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);
  pinMode(potPin, OUTPUT);
  pinMode(batteryPin, INPUT);
}
/////////////////////////////
void loop() {

  // Battery voltage
  rawVoltage = analogRead(batteryPin);
  batteryVoltage = map(rawVoltage, 0, 1023, 0, 100);
  Serial.write(batteryVoltage);
  

  // Potentiometer
  potValue = map(analogRead(potPin), 0, 1023, 0, 240);
  speed = 43.18 * potValue * 0.001885;
  Serial.write(speed);
  

  // Ultrasonic sensor
  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrig, LOW);
  time = pulseIn(sensorEcho, HIGH);  // function of pulseIn to get total time
  distance = time / 29 / 2;
  Serial.write(distance);
  

  // Car Lock
  lockState = digitalRead(lockPin);
  Serial.write(lockState);

  delay(50);
}
