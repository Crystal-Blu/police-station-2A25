#include <Keypad.h>
#define pin_led_vert 11 // led branche sur pin 9
#define pin_led_rouge 10 // led branche sur pin 10
#define lumiere 13

char data ;
const byte ROWS = 4; 
const byte COLS = 3; 
int is_detected=1;
char on_off='1';
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
   pinMode(lumiere,OUTPUT);
  digitalWrite(lumiere,LOW);
   pinMode(10,INPUT);
  digitalWrite(10,LOW);
}
  
void loop(){
  
  char customKey = customKeypad.getKey();
  data=Serial.read();
  if (data=='1') 
  {  
    digitalWrite(pin_led_vert,HIGH);
    delay (100);
    digitalWrite(pin_led_vert,LOW);
    delay (100);
    digitalWrite(pin_led_vert,HIGH);
    delay (100);
    digitalWrite(pin_led_vert,LOW);
    delay (100);
    digitalWrite(pin_led_vert,HIGH);
    delay (100);
    digitalWrite(pin_led_vert,LOW);
  }
  
else if (data=='0')  
{
   digitalWrite(pin_led_rouge,HIGH);
    delay (100);
    digitalWrite(pin_led_rouge,LOW);
    delay (100);
    digitalWrite(pin_led_rouge,HIGH);
    delay (100);
    digitalWrite(pin_led_rouge,LOW);
    delay (100);
    digitalWrite(pin_led_rouge,HIGH);
    delay (100);
    digitalWrite(pin_led_rouge,LOW);
} 
if (data=='2')
{
  on_off='0';
  digitalWrite(lumiere, LOW);  
}
if (data=='3')
{
  on_off='1' ;
}

  if (on_off=='1')
  {
   if (digitalRead(12)==HIGH) 
   {
    
    if (is_detected==0)
    
    {Serial.write("A");
    is_detected=1;}
    digitalWrite(lumiere, HIGH);   
   }
   else 
   {
    if (is_detected==1)
    {
    Serial.write("B");
    is_detected=0;
    }
    digitalWrite(lumiere, LOW);   
    
   }
}
  if (customKey){
    Serial.write(customKey);
  }
  delay (100);
  
  
}
