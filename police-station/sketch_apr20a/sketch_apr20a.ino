#include <Keypad.h>
#define pin_led_vert 11 // led branche sur pin 9
#define pin_led_rouge 10 // led branche sur pin 10
char data ;
const byte ROWS = 4; 
const byte COLS = 3; 
int is_detected=1;
char on_off;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(pin_led_vert,OUTPUT); 
  digitalWrite(pin_led_vert,LOW);
  pinMode(pin_led_rouge,OUTPUT); 
  digitalWrite(pin_led_rouge,LOW); 
}
  
void loop(){
  
  char customKey = customKeypad.getKey();
  data=Serial.read();
   if (data=='0')
  on_off=0;
  if (data=='1')
  on_off=1;
  if (data=='2')
  digitalWrite(Led_red, HIGH); 
  if (data=='3')
  digitalWrite(Led_Green, HIGH); 

   if (digitalRead(8)==HIGH) 
   {
    
    Serial.write("1");
    is_detected=1;
    digitalWrite(lumiere, HIGH);   
   }
   else 
   {
    
    Serial.write("0");
    is_detected=0;
    digitalWrite(lumiere, LOW);   
    
   }
  if (customKey){
    Serial.write(customKey);
  }
  if (Serial.available() )
  {
    data=Serial.read();
  if (data=='0') 
  {  
    digitalWrite(pin_led_vert,HIGH);
  }
  
else if (data=='1')  
{
  digitalWrite(pin_led_rouge,HIGH);
} 
}
  
  
}
