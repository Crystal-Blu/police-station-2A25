#define red_led 9
#define green_led 10

void setup() {
  // put your setup code here, to run once:
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  analogWrite(red_led,255);
  analogWrite(green_led,255);
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  char led_specifier = Serial.read();
  int led_brightness = Serial.parseInt();
  write_leds(led_specifier,led_brightness);
  
}
}
void write_leds(char led,int brightness)
{
  if (led == 'r'){
    analogWrite(red_led, 255 - brightness);
    return;
  }
  if (led == 'g'){
    analogWrite(green_led, 255 - brightness);
    return;
  }
  return ;
}
