unsigned long currentMillis = 1UL;
unsigned long previousMillis = 1UL;
 
void setup() {
 
}
 
void loop() {
    currentMillis = millis();
     
    if ( currentMillis - previousMillis >= 500UL ){
        previousMillis = currentMillis;
         
        //этот код повторяться каждые 500 мсек
 
    }
 
 
}