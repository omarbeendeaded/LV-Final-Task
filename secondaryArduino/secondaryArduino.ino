#define RX 0
#define TX 1

int batteryPin = A0;
int batteryVoltage = 0;
int rawVoltage = 0;

int sensorTrig = 8;
int sensorEcho = 9;
int time;
int distance;

const int potPin = A1;
int potValue = 0;
int speed = 0;


void setup() {
  Serial.begin(9600);
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);
  pinMode(potPin, INPUT);
  pinMode(batteryPin, INPUT);
}
/////////////////////////////
void loop() {
  String data = "";

  // Battery voltage
  rawVoltage = analogRead(batteryPin);
  batteryVoltage = map(rawVoltage, 0, 107, 0, 100);
  data = data + "X" + batteryVoltage;
  

  // Potentiometer
  potValue = map(analogRead(potPin), 0, 1023, 0, 240);
  speed = 43.18 * potValue * 0.01885;
  data = data + "X" + speed;
  

  // Ultrasonic sensor
  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrig, LOW);
  time = pulseIn(sensorEcho, HIGH);  // function of pulseIn to get total time
  distance = time * 0.034 / 2;
  data = data + "X" + distance + "F";

  Serial.println(data);

  delay(250);
}
