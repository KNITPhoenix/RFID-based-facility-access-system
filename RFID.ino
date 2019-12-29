#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define SS_PIN 10
#define RST_PIN 8
#include <Servo.h>
int servoPin = 9; 
// Create a servo object 
Servo Servo1; 
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(6 , 7, 5, 4, 3, 2); 
void setup() 
{
  SPI.begin();
  Servo1.attach(servoPin);      
  mfrc522.PCD_Init();   
  lcd.begin(16, 2);
  lcd.print("Scan RFID Card");
  Serial.begin(9600);

}
void clockwise()
{
   // Make servo go to 0 degrees 
   Servo1.write(90); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(0); 
   delay(5000); 
   // Make servo go to 180 degrees 
   Servo1.write(90);  
}


void loop() 
{
  Servo1.write(90);
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  lcd.clear();
  lcd.begin(16, 2);
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
lcd.begin(16, 2);
 content.toUpperCase();
 Serial.print(content);
  if (content.substring(1) == "19 2F 37 09") //Plz change to your cards UID
  {
   lcd.setCursor(0,1);
    lcd.print("Authorized");

    delay(2000);
   lcd.clear();
   clockwise();
    setup();
  }

 else if (content.substring(1) == "E9 48 39 09") //Plz change to your cards UID
  {
   lcd.setCursor(0,1);
    lcd.print("Authorized");

    delay(2000);
   lcd.clear();
   clockwise();
    setup();
  }
  
 else   {
  lcd.setCursor(0, 1);
    lcd.print(" Access denied");
    delay(3000);
    lcd.clear();
      setup();
      }
} 
