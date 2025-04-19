#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioInputUSBQuad        usb_quad;
AudioOutputI2SQuad       i2s_quad;
AudioConnection          patchCord1(usb_quad, 0, i2s_quad, 2); // front
AudioConnection          patchCord2(usb_quad, 1, i2s_quad, 3); // front
AudioConnection          patchCord3(usb_quad, 2, i2s_quad, 0); // rear
AudioConnection          patchCord4(usb_quad, 3, i2s_quad, 1); // rear
AudioControlSGTL5000     sgtl5000_1;
AudioControlSGTL5000     sgtl5000_2;

const int ledPin = 13;

void setup() {

   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH);

   AudioMemory(60);

   sgtl5000_1.setAddress(LOW);
   sgtl5000_2.setAddress(HIGH);

   sgtl5000_1.enable();
   sgtl5000_2.enable();

   sgtl5000_1.volume(0.8);
   sgtl5000_1.unmuteLineout();
   sgtl5000_1.lineOutLevel(13);

   sgtl5000_2.volume(0.8);
   sgtl5000_2.unmuteLineout();
   sgtl5000_2.lineOutLevel(13);

}

void loop() {
}
