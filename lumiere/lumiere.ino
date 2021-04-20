#define pin_led 11 // led branchée sur pin 11
char data ;
int capteur=2 ; // initialisation de la pin 2

void setup() {
  pinMode(pin_led,OUTPUT); 
  digitalWrite(pin_led,LOW);
  pinMode(capteur,INPUT);
Serial.begin(9600);
}

void loop() {
  if (Serial.available() ) {
    data=Serial.read();
  if (data=='1') 
  {  
   if (digitalRead(capteur)==HIGH) 
   {
    digitalWrite(pin_led,HIGH);
    Serial.write('1');
   }
   else if (digitalRead(capteur)==LOW)
   {
    digitalWrite(pin_led,LOW);
    Serial.write('0');
   }
}
else if (data=='0')  
{
  digitalWrite(pin_led,LOW);
  Serial.write('2');
}
  
  
}}
