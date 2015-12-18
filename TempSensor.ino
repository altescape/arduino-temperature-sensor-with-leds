//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __|
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/
//
// Temp sensor test
//
// Made by Michael Watts
// License: CC-BY-SA 3.0
// Downloaded from: https://123d.circuits.io/circuits/1203766-temp-sensor-test

#include <LiquidCrystal.h>

const int temperaturePin = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
    // lcd
  	lcd.begin(16,2);
  	lcd.print("Temperature");
  	Serial.begin(9600);

  	// leds
  	pinMode(6, OUTPUT);
  	pinMode(7, OUTPUT);
  	pinMode(8, OUTPUT);
}

int tempStatus(float t)
{
  if (t <= 0) {
      return -1;
    } else if (t >= 1 && t <= 99) {
      return 0;
    } else {
      return 1;
    }
}

void blinkLed(int led)
{
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(1000);
}

void loop()
{
	float voltage, degreesC, degreesF;

  	voltage = getVoltage(temperaturePin);

  	degreesC = (voltage - 0.5) * 100.0;

  	degreesF = degreesC * (9.0/5.0) + 32.0;

    Serial.println("-=-=-=-=-=-");
  	Serial.print("voltage: ");
    Serial.println(voltage);
    Serial.print("  deg C: ");
    Serial.println(degreesC);
    Serial.print("  deg F: ");
    Serial.println(degreesF);

  	delay(500);

  	//lcd.clear();
  	lcd.setCursor(0, 1);
  	lcd.print(degreesC);

  	switch (tempStatus(degreesC)) {
      case -1: // below freezing
        digitalWrite(6, LOW);  // red led
        digitalWrite(7, LOW);  // green led
      	blinkLed(8);
        //digitalWrite(8, HIGH); // blue led
        break;
      case 1: // above boiling
      	blinkLed(6);
        //digitalWrite(6, HIGH); // red led
        digitalWrite(7, LOW);  // green led
        digitalWrite(8, LOW);  // blue led
        break;
      default: // normal
        digitalWrite(6, LOW);  // red led
      	blinkLed(7);
        //digitalWrite(7, HIGH); // green led
        digitalWrite(8, LOW);  // blue led
      break;
    }
}

float getVoltage(int pin)
{
	return (analogRead(pin) * 0.004882814);
}
