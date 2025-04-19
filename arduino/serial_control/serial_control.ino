#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


AudioSynthWaveform       waveform1;
AudioSynthWaveform       waveform2;
AudioSynthWaveform       waveform3;

AudioSynthWaveformSine   sine1;
AudioSynthWaveformSine   sine2;

AudioOutputI2SQuad       i2s_quad;
AudioConnection          patchCord1(waveform1, 0, i2s_quad, 1);
AudioConnection          patchCord2(waveform2, 0, i2s_quad, 2);
AudioConnection          patchCord3(waveform3, 0, i2s_quad, 3);
AudioControlSGTL5000     sgtl5000_1;
AudioControlSGTL5000     sgtl5000_2;

int16_t x[256], y[256], laser[256];


void setup() {

   AudioMemory(10);

   sgtl5000_1.setAddress(LOW);
   sgtl5000_2.setAddress(HIGH);

   sgtl5000_1.enable();
   sgtl5000_1.volume(0.80); // volume of headphone out, above ~0.8 starts to distort
   sgtl5000_1.unmuteLineout();
   sgtl5000_1.lineOutLevel(13);

   sgtl5000_2.enable();
   sgtl5000_2.volume(0.80);
   sgtl5000_2.unmuteLineout();
   sgtl5000_2.lineOutLevel(13);

   int sq = 1;
   for(int i=0; i<256; i++) {
      x[i] = int16_t(32767 * sin(i*TWO_PI/256.0));
      y[i] = int16_t(32767 * cos(i*TWO_PI/256.0));
      if(i%(256/10) == 0) {
         sq *= -1;
      }
      laser[i] = sq * 32767;
   }

   Serial.begin(115200);
   while(!Serial) {}
   Serial.println("BEGIN");

   waveform1.arbitraryWaveform(laser, 172.0);
   waveform2.arbitraryWaveform(x, 172.0);
   waveform3.arbitraryWaveform(y, 172.0);

   waveform1.begin(WAVEFORM_ARBITRARY);
   waveform2.begin(WAVEFORM_ARBITRARY);
   waveform3.begin(WAVEFORM_ARBITRARY);

   waveform1.frequency(100);
   waveform1.amplitude(1.0);
   waveform2.frequency(100);
   waveform2.amplitude(1.0);
   waveform3.frequency(100);
   waveform3.amplitude(1.0);

}

void loop() {

   // delay(3000);

   // float a = random(1000) / 1000.0;
   // int sq = 1;
   // for(int i=0; i<256; i++) {
   //    x[i] = int16_t(a * 32767 * sin(i*TWO_PI/256.0));
   //    y[i] = int16_t(a * 32767 * cos(i*TWO_PI/256.0));
   //    if(i%(256/10) == 0) {
   //       sq *= -1;
   //    }
   //    laser[i] = sq * 32767;
   // }

   // for(int i=0; i<256; i++) {
   //    Serial.print(x[i]);
   //    Serial.print(',');
   //    Serial.print(y[i]);
   //    Serial.print(',');
   //    Serial.println(laser[i]);
   // }
}

void serialEvent() {
   // Serial.println("RECEIVING_BYTES");
   byte in_buffer[1536];
   int num_bytes_received = Serial.readBytes(in_buffer, 1536);

   for(int i=0; i<512; i+=2) {
      x[i/2] = combineBytes(in_buffer[i+1], in_buffer[i]);
   }
   for(int i=512; i<1024; i+=2) {
      y[(i-512)/2] = combineBytes(in_buffer[i+1], in_buffer[i]);
   }
   for(int i=1024; i<1536; i+=2) {
      laser[(i-1024)/2] = combineBytes(in_buffer[i+1], in_buffer[i]);
   }

   Serial.print("received bytes: ");
   Serial.println(num_bytes_received);

   // for(int i=0; i<256; i++) {
   //    Serial.print(x[i]);
   //    Serial.print(',');
   //    Serial.print(y[i]);
   //    Serial.print(',');
   //    Serial.println(laser[i]);
   // }
}

int16_t combineBytes(uint8_t msb, uint8_t lsb) {
   // Shift the MSB to the left by 8 bits and OR it with the LSB
   return (int16_t)((msb << 8) | lsb);
}