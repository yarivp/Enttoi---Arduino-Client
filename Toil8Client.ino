#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

RH_ASK driver;

const int pinSwitch1 = 8;
const int pinSwitch2 = 9;

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    lcd.begin(16,2);
    lcd.backlight();
    lcd.setCursor(0,0); //Start at character 4 on line 0
    lcd.print("Initializing");
    //Activate the pull up resistors
    digitalWrite(pinSwitch1, HIGH);
    digitalWrite(pinSwitch2, HIGH);
}

void loop()
{

    //Floor;Side;Cabin;State
    if(digitalRead(pinSwitch1) == HIGH)
    {
      //2;0;0;2 Second floor, Left Side, Sensor ID, State
      const char *doorMessage = "2;0;0;1";
      Serial.println(doorMessage);
      driver.send((uint8_t *)doorMessage, strlen(doorMessage));
      driver.waitPacketSent();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Door #1 Open");
    }
    else
    {
      //2;0;0;2 Second floor, Left Side, Sensor ID, State
      const char *doorMessage = "2;0;0;0";
      Serial.println(doorMessage);
      driver.send((uint8_t *)doorMessage, strlen(doorMessage));
      driver.waitPacketSent();
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Door #1 Closed");
    }
    delay(3000);
    if(digitalRead(pinSwitch2) == HIGH)
    {
      //2;0;0;2 Second floor, Left Side, Sensor ID, State
      const char *doorMessage = "2;0;1;1";
      Serial.println(doorMessage);
      driver.send((uint8_t *)doorMessage, strlen(doorMessage));
      driver.waitPacketSent();
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Door #2 Open");
    }
    else
    {
      //2;0;0;2 Second floor, Left Side, Sensor ID, State
      const char *doorMessage = "2;0;1;0";
      Serial.println(doorMessage);
      driver.send((uint8_t *)doorMessage, strlen(doorMessage));
      driver.waitPacketSent();
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Door #2 Closed");
    }
    delay(3000);
}
