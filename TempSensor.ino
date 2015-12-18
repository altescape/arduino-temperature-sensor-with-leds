//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __|
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/
//
// Temp sensor test
//
// Made by Michael Watts
// License: CC-BY-SA 3.0
// Downloaded from: https://123d.circuits.io/circuits/1387881-temp-sensor-test/

const int TEMP_PIN = 0;
const int RED_LED = 2;
const int GREEN_LED = 4;
const int BLUE_LED = 6;

void setup()
{
	Serial.begin(9600);

  	
  	// leds
  	pinMode(RED_LED, OUTPUT);
  	pinMode(GREEN_LED, OUTPUT);
  	pinMode(BLUE_LED, OUTPUT);
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

void blink(int led)
{
  digitalWrite(led, HIGH);
}

void turn_off(int led)
{
	digitalWrite(led, LOW);
}

void serial_output(double v, double c, double f)
{
	Serial.println("-=-=-=-=-=-");
	Serial.print("voltage: ");
    Serial.println(v);
    Serial.print("  deg C: ");
    Serial.println(c);
    Serial.print("  deg F: ");
    Serial.println(f);
}

void led_controller(c)
{
  	switch (tempStatus(c)) {
      case -1: // freezing and below
      	blink(BLUE_LED);
        turn_off(RED_LED);
        turn_off(GREEN_LED);
        break;
      case 1: // boiling and above
      	blink(RED_LED);
        turn_off(GREEN_LED);
        turn_off(BLUE_LED);
        break;
      default: // normal
        blink(GREEN_LED);
        turn_off(RED_LED);
        turn_off(BLUE_LED);
      break;
    }
}

void loop()
{
	float voltage = getVoltage(), 
  		  degreesC = getdegreesC(), 
  		  degreesF = getdegreesF();
  
    serial_output(voltage, degreesC, degreesF);
    led_controller(degreesC);
  	
  	delay(100);
}

double getVoltage()
{
	return (analogRead(TEMP_PIN) * 0.004882814);
}

double getdegreesC()
{
	return (getVoltage() - 0.5) * 100.0;
}

double getdegreesF()
{
	return  getdegreesC() * (9.0/5.0) + 32.0;
}
