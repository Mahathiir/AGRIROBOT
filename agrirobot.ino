//BLUETOOTH SERIAL SELECTION
#define mySerial Serial
//ROBOT
#define IN1 3
#define IN2 2
#define IN3 4
#define IN4 5
void initiateRobotPins() {
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}
void robotStop() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}
void robotForward() {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void robotBackward() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void robotLeft() {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void robotRight() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
//Soil
#define SOIL_PIN A0
int SOIL_VALUE = 0;
void initiateSoilPin() {
pinMode(SOIL_PIN, INPUT);
}
unsigned long soil_millis = 0;
int readSoil() {
if ((soil_millis + 200) < millis()) {
SOIL_VALUE = map(analogRead(SOIL_PIN), 1024, 0, 0, 100);
soil_millis = millis();
}
return SOIL_VALUE;
}
//RELAY
#define RELAY_PIN 10
#define RELAY_ON LOW
#define RELAY_OFF HIGH
void initiateRelayPin() {
pinMode(RELAY_PIN, OUTPUT);
digitalWrite(RELAY_PIN, RELAY_OFF);
}
//DHT
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int DHT_Temp = 0, DHT_Humi = 0;
void initiateDHT() {
dht.begin();
}
unsigned long dht_read_millis = 0;
void readDHT() {
if ((dht_read_millis + 1000) < millis()) {
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
Serial.println(F("Failed to read from DHT sensor!"));
return;
} else {
DHT_Temp = t;
DHT_Humi = h;
}
dht_read_millis = millis();
}
}
//LCD
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = A4, d5 = A3, d6 = A2, d7 = A1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void initiateLCD() {
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Program Started-");
delay(1500);
lcd.clear();
lcd.setCursor(0, 0);
}
unsigned long lcd_millis = 0;
void printLCD() {
if ((lcd_millis + 500) < millis()) {
String row_1 = "SOIL VAL :" + String(SOIL_VALUE) + "%";
for (int i = row_1.length(); i < 16; i++)
row_1 += " ";
lcd.setCursor(0, 0);
lcd.print(row_1);
String row_2 = "T:" + String(DHT_Temp) + "'C";
lcd.setCursor(0,1);
lcd.print(row_2);
row_2 = "H:" + String(DHT_Humi) + "%";
lcd.setCursor(8,1);
for(int i = 0; i < (8 - row_2.length()); i++) lcd.print(" ");
lcd.print(row_2);
lcd_millis = millis();
}
}
//Servo
#include <Servo.h>
Servo myservo;
#define SERVO_PIN 6
int pos = 0;
void initiateServo(){
myservo.attach(SERVO_PIN);
}
unsigned long servo_millis = 0;
void servo_loop(){
if((servo_millis + 25) < millis()){
if(int(pos / 30) == 0) myservo.write(pos);
if(int(pos / 30) == 1) myservo.write((30- - (pos %30)));
pos = (pos + 1) % 360;
servo_millis = millis();
}
}
void setup() {
delay(500);
Serial.begin(9600);
Serial.println();
Serial.println("Program Started-");
initiateRobotPins();
initiateRelayPin();
initiateSoilPin();
initiateDHT();
initiateLCD();
initiateServo();
}
char c = '1';
void loop() {
//DHT
readDHT();
//Display
printLCD();
//SERVO
servo_loop();
if (mySerial.available()) {
c = mySerial.read();
}
if (c != '1') {
Serial.println("Received : " + String(c));
if (c == 'S') {
robotStop();
}
if (c == 'F') {
robotForward();
}
if (c == 'B') {
robotBackward();
}
if (c == 'R') {
 robotRight():
}
If(c==’L’){
 robotLeft():
}
C=’1’:
}
