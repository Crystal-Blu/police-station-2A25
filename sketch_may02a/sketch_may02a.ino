#include <Keypad.h>
 #include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
 
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte pin_rows[ROW_NUM] = {8, 7, 6 ,5}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = { 4,3,2}; //connect to the column pinouts of the keypad
 
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
 
const String password_1 = "1234"; // change your password here
const String password_2 = "5642"; // change your password here
const String password_3 = "4545"; // change your password here
String input_password;
 
void setup(){
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}
 
void loop(){
  char key = keypad.getKey();
 
  if (key){

    Serial.write(key);
    delay(500);
   
  }
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
}
