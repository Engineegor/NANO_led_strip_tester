#define STRIP_TASK_PERIOD	700

void setup() {
	STRIP_SETUP();
}

void loop() {
	STRIP_TASK(STRIP_TASK_PERIOD);
}