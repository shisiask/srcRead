#include <SPI.h>
#include <RFID.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SDA 10
#define RST 9
RFID RC522(SDA, RST);
String u = "";
void setup() {
Serial.begin(9600);
SPI.begin();
RC522.init();


  lcd.init();
  lcd.backlight();
}
void loop() {
if (RC522.isCard())
{
RC522.readCardSerial();
u = "";
for(int i=0;i<5;i++)
{u += String(RC522.serNum[i]);}
//Serial.println(u);
if (u == "26221108126213")
{
  Serial.println("access granted");
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("access granted");
  delay(2000);
  lcd.clear();
  
}
else{
  Serial.println("Nah uh");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nah Uh");
  Serial.println("Nah uh");
  

}

}
delay(500);
}