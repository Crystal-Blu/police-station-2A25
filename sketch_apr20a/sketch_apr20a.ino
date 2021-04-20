char data ;
int Rfid_detector=2 ;

void setup() {
  pinMode(Rfid_detector,INPUT);
Serial.begin(9600);
}

void loop() {
  if (Serial.available() ) {
    data=Serial.read();
  
   if (digitalRead(Rfid_detector)==HIGH) 
   {
    Serial.write('1');
   }
   else if (digitalRead(Rfid_detector)==LOW)
   {
    Serial.write('0');
   }
    
  }
}
