extern bool static_switch;

void BUTTONS_SETUP() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void BUTTONS_TASK() {
	static unsigned long 	buttons_last_millis = 0;
	static bool				button_state		= false;
	static bool				button_trig			= false;
	if (millis() - buttons_last_millis > BUTTONS_PERIOD) {
		buttons_last_millis = millis();

		button_state = digitalRead(BUTTON_PIN);

		if ( button_state && !button_trig) {button_trig = true;}
		if (!button_state &&  button_trig) {button_trig = false;
			Serial.println("Button pressed");
			static_switch = !static_switch;
			if (static_switch)	set_frame(running_pixel);
			else				set_frame(static_white);
		}
	}
}