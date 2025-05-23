#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN			5
#define LED_NUM			312
#define LED_TYPE		WS2812
#define COLOR_ORDER		GRB
#define DEFAULT_FPS		3
#define	BUTTON_PIN		9
#define BUTTONS_PERIOD	20

void setup() {
	LEDS_SETUP();
	BUTTONS_SETUP();
	pinMode(13, OUTPUT);
	Serial.begin(38400);

	Serial.println("\n Let's go!");
}

void loop() {
	LEDS_TASK();
	BUTTONS_TASK();
}
