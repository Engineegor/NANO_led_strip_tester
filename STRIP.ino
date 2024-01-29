#include <Arduino.h>
#include <FastLED.h>


#define STRIP_TYPE	WS2812
#define STRIP_SIZE	100
#define STRIP_PIN	5
#define COLOR_ORDER	GRB

CRGB leds[STRIP_SIZE];
CRGB buff_frame[STRIP_SIZE];

uint8_t		curr_step		= 0;
uint8_t		curr_color_step	= 0;
const bool	step_dir		= false;

bool next_color_step(bool dir) {
	if (dir) {
		if (curr_color_step == 0) {
			curr_color_step = 2;
			return true;
		} else curr_color_step--;
	} else {
		if (curr_color_step >= 3) {
			curr_color_step = 0;
			return true;
		} else curr_color_step++;
	}
	return false;
}

void color_step(uint8_t step) {
	CRGB color = 0;
	if (step == 0)		color = CRGB::Green;
	else if (step == 1)	color = CRGB::Red;
	else				color = CRGB:: Blue;

	for (int i = 0; i < STRIP_SIZE; i) {
		buff_frame[i] = color;
	}
}

void next_step(bool dir) {
	if (dir) {
		if (curr_step == 0)				curr_step = STRIP_SIZE - 1;
		else							curr_step--;
	} else {
		if (curr_step >= STRIP_SIZE)	curr_step = 0;
		else							curr_step++;
	}
}

void update_frame(uint8_t step) {
	for (int i = 0; i < STRIP_SIZE; i++) {
		leds[i] = buff_frame[(i + step < STRIP_SIZE) ? i + step : i + step - STRIP_SIZE];
	}
	FastLED.show();
}

void STRIP_SETUP() {
	FastLED.addLeds<STRIP_TYPE, STRIP_PIN, COLOR_ORDER>(leds, STRIP_SIZE);
	FastLED.setMaxRefreshRate(6500, false);
}

void STRIP_TASK(uint32_t period) {
	static  unsigned long task_last_millis = 0;
	if (millis() - task_last_millis > period) {
		task_last_millis = millis();

		if (next_color_step(step_dir)) next_step(step_dir);

		color_step(curr_color_step);
		update_frame(curr_step);
	}
}