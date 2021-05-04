#include <Keypad.h>
 #include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define Led_red 4
#define Led_Green 6
MFRC522 mfrc522(SS_PIN, RST_PIN);
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
 char data;


 
void setup(){
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(Led_red,OUTPUT);
  pinMode(Led_Green,OUTPUT);
  digitalWrite(Led_red,LOW);
  digitalWrite(Led_Green,LOW);
}
 
void loop(){
  data=Serial.read();
  if (data=='0')
  digitalWrite(Led_red, HIGH); 
  if (data=='1')
  digitalWrite(Led_Green, HIGH); 
  String code;
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  String C(content);
  Serial.println(content.substring(1));
  delay(3000);
  digitalWrite(Led_red, LOW); 
  digitalWrite(Led_Green, LOW); 
}
