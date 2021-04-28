#define pin_led_vert 9 // led branche sur pin 9
#define pin_led_rouge 10 // led branche sur pin 10
char data ;


void setup() {
  pinMode(pin_led_vert,OUTPUT); 
  digitalWrite(pin_led_vert,LOW);
  pinMode(pin_led_rouge,OUTPUT); 
  digitalWrite(pin_led_rouge,LOW); 
Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() )
  {
    data=Serial.read();
  if (data=='1') 
  {  
    digitalWrite(pin_led_vert,HIGH);
    Serial.write('1');
  }
  
else if (data=='0')  
{
  digitalWrite(pin_led_rouge,HIGH);
    Serial.write('0'); 
} 
}
}
