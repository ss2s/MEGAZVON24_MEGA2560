
unsigned long startMill = 1UL;
unsigned long currentMill = 1UL;
unsigned long delPeriod = 2000UL;

void setup(){
	pinMode(13, OUTPUT);
}

void loop(){
	startTime = millis();
	while ((currentMillis = millis()) - startTime < 2000ul);
	!digitalWrite(13, HIGH);
}