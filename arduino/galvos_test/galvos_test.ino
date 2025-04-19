#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioSynthWaveformPWM    pwm1;
AudioSynthWaveformPWM    pwm2;
AudioSynthWaveformSine   sine1;
AudioSynthWaveformSine   sine2;
AudioSynthWaveform       square1;
AudioSynthWaveform       square2;
// AudioSynthWaveformSine   sine3;
AudioOutputI2SQuad       i2s_quad;
AudioConnection          patchCord0(square1,   0, i2s_quad, 0);
AudioConnection          patchCord1(square2,   0, i2s_quad, 1);
AudioConnection          patchCord2(sine1, 0, i2s_quad, 2);
AudioConnection          patchCord3(sine2, 0, i2s_quad, 3);
AudioControlSGTL5000     sgtl5000_1;
AudioControlSGTL5000     sgtl5000_2;

const int ledPin = 13;

void setup() {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  AudioMemory(10);

  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8); // volume of headphone out, above ~0.8 starts to distort
  sgtl5000_1.unmuteLineout();
  sgtl5000_1.lineOutLevel(13);

  sgtl5000_2.enable();
  sgtl5000_2.volume(0.8);
  sgtl5000_2.unmuteLineout();
  sgtl5000_2.lineOutLevel(13);

  sine1.frequency(50);
  sine1.amplitude(1.0);
  sine2.frequency(50);
  sine2.amplitude(1.0);
  sine2.phase(90);

  // sine3.frequency(100);
  // sine3.amplitude(1.0);
  square1.begin(WAVEFORM_SQUARE);
  square2.begin(WAVEFORM_SQUARE);
  square1.frequency(100);
  square1.amplitude(1.0);
  square1.phase(180);
  square2.frequency(100);
  square2.amplitude(1.0);

}

void loop() {

}
