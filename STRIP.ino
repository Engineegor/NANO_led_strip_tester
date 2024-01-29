CRGB leds[LED_NUM];
CRGB buff_frame[LED_NUM];

const int		frame_timeout		= 1000 / DEFAULT_FPS;
int				frame_step			= 0;
void			(*current_frame)()	= NULL;
uint8_t			color_step 			= 0;
bool			led_state			= 0;
bool			static_switch		= false;

void fill_frame(CRGB color) {
	for(int i = 0; i < LED_NUM; i++) leds[i] = color;
}

void draw_line(uint8_t offset, uint8_t lenght, CRGB color) {
	for (int i = 0; i < lenght; i++) leds[i + offset] = color;
}

void set_frame(void(*frame)()) {
	if (frame != NULL) current_frame = frame;
}

void show_frame(void(*frame)()) {
	if (frame != NULL) frame();
}

//-----------------------PROGRAMS-------------------------

void running_pixel() {
	Serial.println("Running pixel frame");
	switch (color_step) {
		case 0: fill_frame(CRGB::Green);
		break;
		case 1: fill_frame(CRGB::Red);
		break;
		case 2: fill_frame(CRGB::Blue);
		break;
		default: fill_frame(CRGB::Black);
		break;
	}
	color_step++;

	if (color_step > 2) color_step = 0;

	FastLED.show();
	led_state = !led_state;
}

void static_white() {
	Serial.println("Static frame");
	for (int i = 0; i < LED_NUM; i++) leds[i] = CRGB::White;
	FastLED.show();
	led_state = true;
}

void LEDS_SETUP() {
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_NUM);
	FastLED.setMaxRefreshRate(6500, false);
	set_frame(running_pixel);
}

void LEDS_TASK() {
	static unsigned long frame_last_millis = 0;
	if (millis() - frame_last_millis > frame_timeout) {
		frame_last_millis = millis();
		current_frame();
		digitalWrite(13, led_state);
	}
}