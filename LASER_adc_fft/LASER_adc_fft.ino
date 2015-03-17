// Audio Spectrum Display
// Copyright 2013 Tony DiCola (tony@tonydicola.com)

// This code is part of the guide at http://learn.adafruit.com/fft-fun-with-fourier-transforms/

#define ARM_MATH_CM4
#include <arm_math.h>


////////////////////////////////////////////////////////////////////////////////
// CONIFIGURATION 
////////////////////////////////////////////////////////////////////////////////

int SAMPLE_RATE_HZ = 512;             // Sample rate of the audio in hertz.
// Useful for turning the LED display on and off with commands from the serial port.
const int FFT_SIZE = 256;              // Size of the FFT.  Realistically can only be at most 256 
// without running out of memory for buffers and other state.
const int AUDIO_INPUT_PIN = 14;        // Input ADC pin for audio data.
const int ANALOG_READ_RESOLUTION = 10; // Bits of resolution for the ADC.
const int ANALOG_READ_AVERAGING = 1;  // Number of samples to average with each ADC reading.
const int POWER_LED_PIN = 13;          // Output pin for power LED (pin 13 to use Teensy 3.0's onboard LED).


////////////////////////////////////////////////////////////////////////////////
// INTERNAL STATE
// These shouldn't be modified unless you know what you're doing.
////////////////////////////////////////////////////////////////////////////////

IntervalTimer samplingTimer;
float samples[FFT_SIZE*2];
float magnitudes[FFT_SIZE];

q15_t samples2[FFT_SIZE*2];
q15_t magnitudes2[FFT_SIZE];
float mag[FFT_SIZE];

int sampleCounter = 0;
float max13=0;


////////////////////////////////////////////////////////////////////////////////
// MAIN SKETCH FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void setup() {
  // Set up serial port.
  Serial.begin(115200);

  // Set up ADC and audio input.
  pinMode(AUDIO_INPUT_PIN, INPUT);
  analogReadResolution(ANALOG_READ_RESOLUTION);
  analogReadAveraging(ANALOG_READ_AVERAGING);

  // Turn on the power indicator LED.
  pinMode(POWER_LED_PIN, OUTPUT);
  digitalWrite(POWER_LED_PIN, HIGH); 

  // Begin sampling audio
  samplingBegin();
}

void loop() {
  // Calculate FFT if a full sample is available.
  if (samplingIsDone()) {
    // Run FFT on sample data.
    long a=micros();
//    arm_cfft_radix4_instance_f32 fft_inst;
//    arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
//    arm_cfft_radix4_f32(&fft_inst, samples);
//////    long b=micros()-a;
////    // Calculate magnitude of complex numbers output by the FFT.
//////    long a=micros();
//    arm_cmplx_mag_f32(samples, magnitudes, FFT_SIZE);
//    long b=micros()-a;
    //    arm_cfft_radix4_instance_q31 fft_inst;
    //    arm_cfft_radix4_init_q31(&fft_inst, FFT_SIZE, 0, 1);
    //    arm_cfft_radix4_q31(&fft_inst, samples2);
    //    long b=micros()-a;
    //    // Calculate magnitude of complex numbers output by the FFT.
    //    arm_cmplx_mag_q31(samples2, magnitudes2, FFT_SIZE);

    arm_cfft_radix4_instance_q15 fft_inst;
    arm_cfft_radix4_init_q15(&fft_inst, FFT_SIZE, 0, 1);
    arm_cfft_radix4_q15(&fft_inst, samples2);
    
//    int j=0;
//    for (int i=0;i<FFT_SIZE;i++){
//      mag[i] =(float)sqrt(pow(samples2[j],2)+pow(samples2[j+1],2));
//      j+=2;
//      }
    mag[13] =(float)sqrt(pow(samples2[24],2)+pow(samples2[25],2));
    long b=micros()-a;
    if(mag[13]>max13)max13=mag[13];
    
//    Serial.print(mag[11]);
//    Serial.print("  ");
//    Serial.print(mag[12]);
    Serial.print("Medida ");
    Serial.print(mag[13]);
    Serial.print("  Max ");
    Serial.print(max13);
    Serial.print("  ");
    Serial.println(b);

    // Restart audio sampling.
    samplingBegin();
  }

}


////////////////////////////////////////////////////////////////////////////////
// SAMPLING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void samplingCallback() {
  // Read from the ADC and store the sample data
//  samples2[sampleCounter] =(q15_t)analogRead(AUDIO_INPUT_PIN);
//  samples[sampleCounter] = (float32_t)analogRead(AUDIO_INPUT_PIN);
  samples2[sampleCounter] = (q15_t)analogRead(AUDIO_INPUT_PIN);
  samples2[sampleCounter+2] = samples2[sampleCounter];
  // Complex FFT functions require a coefficient for the imaginary part of the input.
  // Since we only have real data, set this coefficient to zero.
  samples2[sampleCounter+1] = 0;
  samples2[sampleCounter+3] = 0;
//  samples[sampleCounter+1] = 0.0;
  // Update sample buffer position and stop after the buffer is filled
  sampleCounter += 4;
  if (sampleCounter >= FFT_SIZE*2) {
    samplingTimer.end();
  }
}

void samplingBegin() {
  // Reset sample buffer position and start callback at necessary rate.
  sampleCounter = 0;
  samplingTimer.begin(samplingCallback, 1000000/SAMPLE_RATE_HZ);
}

boolean samplingIsDone() {
  return sampleCounter >= FFT_SIZE*2;
}


