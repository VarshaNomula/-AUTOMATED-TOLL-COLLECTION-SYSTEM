#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define RST_PIN 8
#define SS_PIN 10

Servo myservo;
int servoPos =0;
#define num 7

char Data[num];
byte data_count = 0;
String num1, card;
int val,pinIR;
char Key;
int car_balance;
int bus_balance;
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  car_balance = 1000;
  bus_balance = 1000;
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(9600);
  myservo.attach(7);
  myservo.write(90);
  pinIR=6;
}
void rfid()
{
  if (! mfrc522.PICC_IsNewCardPresent())
  {
  return;
  }
  if (! mfrc522.PICC_ReadCardSerial())
  {
  return;
  }
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
  content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
  content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "13 A3 3A 1D")
  {
  if(car_balance>=120){
  myservo.write(180);
  car_balance = car_balance -120;
  Serial.println("Car fair: 120");
  //Serial.println("Bus fair: 200");
  Serial.print("Car Remaining balance: ");
  Serial.println(car_balance);
  delay(2000);
  }
  else{
  Serial.println("Your car remaining balance is not sufficient");
  delay(1000);
  }
  }
   /*if (content.substring(1) == "C1 37 CE 24")
  {
   if(bus_balance>=200){
  myservo.write(90);
  bus_balance = bus_balance -200;
  Serial.println("Car fair: 120");
  Serial.println("Bus fair: 200");
  Serial.print("Bus Remaining balance: ");
  Serial.println(bus_balance);
  delay(2000);
  }
  else{
  Serial.println("Your bus remaining balance is not sufficient");
  delay(1000);
  }
  }
  */
}
/*void exiting(){
  myservo.write(0); //this is an interrupt function when car exits
}*/
 void loop(){
    val = digitalRead(pinIR);
  
    if (val ==0){
      myservo.write(150);
      delay(100);
    }
    else
    {
      myservo.write(10);
      delay(100);
    }
    rfid();
 }
