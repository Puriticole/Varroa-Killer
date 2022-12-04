#include <OneWire.h>
const int fanPin = 6;

// PWM channel 0 parameter
const int freq = 1; // 5000 Hz
const int fanChannel = 0;
const int resolution = 8; // 8-bit resolution

void setup(){
    // Configure the channel 0
    ledcSetup(fanChannel, freq, resolution);

    // Attach the channel 0 on the 3 pins
    ledcAttachPin(fanPin, fanChannel);
}

void loop(){
    // Increase the brightness of the led in the loop
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
        ledcWrite(fanChannel, dutyCycle);
        delay(15);
    }
}
