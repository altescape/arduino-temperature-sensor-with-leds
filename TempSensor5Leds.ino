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

const int TEMP_PIN = 14;
const int RED_LED_RIGHT = 2;
const int YELLOW_LED = 3;
const int GREEN_LED = 4;
const int BLUE_LED = 5;
const int RED_LED_LEFT = 6;

void setup()
{
	Serial.begin(9600);
	
	// leds
	pinMode(RED_LED_RIGHT, OUTPUT);
	pinMode(YELLOW_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(BLUE_LED, OUTPUT);
	pinMode(RED_LED_LEFT, OUTPUT);
  
  	// switch on all leds
    test_leds();
}

int tempStatus(float t)
{
	if (t <= -10) {
		return -1;
	} else if (t <= 15) {
		return 0;
	} else if (t <= 50) {
		return 1;
	} else if (t <= 100) {
		return 2;
	} else if (t >= 100) {
		return 3;
	} 
}

void test_leds()
{
  turn_on(RED_LED_LEFT);
  delay(100);
  turn_on(BLUE_LED);
  delay(100);
  turn_on(GREEN_LED);
  delay(100);
  turn_on(YELLOW_LED);
  delay(100);
  turn_on(RED_LED_RIGHT);
  delay(100);
  
  turn_off(RED_LED_LEFT);
  turn_off(BLUE_LED);
  turn_off(GREEN_LED);
  turn_off(YELLOW_LED);
  turn_off(RED_LED_RIGHT);
}

void blink(int led)
{
	digitalWrite(led, HIGH);
  	delay(100);
  	digitalWrite(led, LOW);
  	delay(100);
}

void turn_on(int led)
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

void led_controller(double c)
{
	switch (tempStatus(c)) {
		case -1: // danger! Below freezing point
			blink(BLUE_LED);
      		turn_on(RED_LED_LEFT);
			turn_off(GREEN_LED);
			turn_off(YELLOW_LED);
			turn_off(RED_LED_RIGHT);
			break;
      	
		case 0: // getting colder
			turn_on(BLUE_LED);
			turn_off(RED_LED_LEFT);
			turn_off(GREEN_LED);
			turn_off(YELLOW_LED);
			turn_off(RED_LED_RIGHT);
			break;
      
		case 1: // normal
			turn_on(GREEN_LED);
			turn_off(RED_LED_LEFT);
			turn_off(BLUE_LED);
			turn_off(YELLOW_LED);
			turn_off(RED_LED_RIGHT);
			break;
      	
		case 2: // getting warmer
			turn_on(YELLOW_LED);
			turn_off(GREEN_LED);
			turn_off(RED_LED_LEFT);
			turn_off(RED_LED_RIGHT);
			turn_off(BLUE_LED);
			break;
      
		case 3: // danger! Above boiling point
			blink(YELLOW_LED);
			turn_on(RED_LED_RIGHT);
			turn_off(GREEN_LED);
			turn_off(BLUE_LED);
			turn_off(RED_LED_LEFT);
			break;
      
		default: // normal
			turn_on(GREEN_LED);
			turn_off(RED_LED_LEFT);
			turn_off(BLUE_LED);
			turn_off(YELLOW_LED);
			turn_off(RED_LED_RIGHT);
	}
}

void loop()
{
	float
		voltage = getVoltage(), 
		degreesC = getdegreesC(), 
		degreesF = getdegreesF();
	
	serial_output(voltage, degreesC, degreesF);
	led_controller(degreesC);
  
  	delay(200);
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
