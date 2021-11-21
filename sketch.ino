#include <Wire.h>
#include <iarduino_RTC.h>
#include <LiquidCrystal_I2C.h>
iarduino_RTC time(RTC_DS1307);
#define res A0
int rotat; 
#define PIN_MOTOR 13
int t;
unsigned  int r;
int tdiff;
const int buttonPin = 2;
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
    delay(300);   
    pinMode(4, OUTPUT);
    time.begin();
    time.period(1);
    pinMode(res, INPUT);
    tdiff = analogRead(res);
    lcd.init();                   
    lcd.backlight();// Включаем подсветку дисплея
    pinMode(PIN_MOTOR, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
}
void loop(){
    t = analogRead(res);
    if (t/100!=tdiff/100) {
      lcd.setCursor(12, 0);
      lcd.print("   ");
      lcd.setCursor(12, 0);
      lcd.print(analogRead(res)/10);  
      lcd.setCursor(0, 1);
      lcd.print(time.gettime("H:i:s, D"));  
      }
    if(millis()%1000==0){ // если прошла 1 секунда
      lcd.setCursor(0, 0);
      lcd.print(time.gettime("d-m-Y"));      
      lcd.setCursor(0, 1);
      lcd.print(time.gettime("H:i:s, D"));
      if(time.Hours>=8&&time.Hours<23) {
        digitalWrite(4, LOW);}
      else {digitalWrite(4, HIGH); }
      if(time.Hours==10&&time.minutes==00&&time.seconds==00) {
         digitalWrite(PIN_MOTOR, HIGH); 
         r = analogRead(res)*150;
         Serial.println(r);
         delay(r); 
         digitalWrite(PIN_MOTOR, LOW);
      }
      tdiff = analogRead(res);
      int buttonState = digitalRead(buttonPin); // считываем состояние кнопки
      if (buttonState == LOW) {
        digitalWrite(PIN_MOTOR, HIGH); 
      }
      else {
        digitalWrite(PIN_MOTOR, LOW);
      }

}

}
