#include <LiquidCrystal.h>

int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
int trigPin=6;
int echoPin=5;
int buttonPin=2;

int buttonVal;
int numMeas=50;
float avgDis;
float bucket=0;
int j;
int pingTravelTime;
float distance;

String msg="Avg. Distance";
String msg2="cm";
String msg3="Press To Start";

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  lcd.begin(16,2);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin,HIGH);
  Serial.begin(9600);
}

void loop() {
  buttonVal=digitalRead(buttonPin);
  Serial.println(buttonVal);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg3);
  bucket=0;

  while(buttonVal==1){
    buttonVal=digitalRead(buttonPin);
  }
  lcd.setCursor(0,0);
  lcd.print("Measuring . . .");
  for(j=1;j<=numMeas;j=j+1){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    pingTravelTime=pulseIn(echoPin,HIGH);
    distance=pingTravelTime*(0.0343);
    bucket=bucket+distance;
  }
  avgDis=bucket/numMeas;

  Serial.print(bucket);
  Serial.print(" ");
  Serial.println(avgDis);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg);
  lcd.setCursor(0,1);
  lcd.print(avgDis);
  lcd.setCursor(6,1);
  lcd.print(msg2);
  delay(5000);
}
