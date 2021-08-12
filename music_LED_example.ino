#include <Adafruit_NeoPixel.h>
#include "averageStack.h"

#define PIN_1 5
#define PIN_2 3
#define NUM_PIXELS 57
// electrelet microphone should be connected to A0
// if using the sparkfun microphone, connect to the envelope pin on the microphone

Adafruit_NeoPixel pixels_1(NUM_PIXELS, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_2(NUM_PIXELS, PIN_2, NEO_GRB + NEO_KHZ800);

// CONSTANTS FOR MUSIC LIGHTS
const int N_VALUES = 8; // changes the sensitivity of the music strip (most sensitive: 0 < n < inf :least sensitive)
const double GAIN = 500.0; // changes how high the strip will go for a given volume (higher gain will cause shorter peaks, sorry haha its opposite)
const int DELAYVAL = 10; // the smaller this is the more reactive and quick the music strip will be
const int INITIAL_FILL_VALUE = 0;
//--------------------------------

double x = 0; // just a counter for the changing colors
averageStack values = averageStack(N_VALUES, INITIAL_FILL_VALUE); // just helps average all the amplitude values together

void setup() {
  Serial.begin(9600);
  pixels_1.begin();
  pixels_2.begin();
  pixel_1.setBrightness(255);
  pixel_2.setBrightness(255);
}

void loop() {
  values.enqueue(analogRead(A0));
  pixels_1.clear(); // Set all pixel colors to 'off'
  pixels_2.clear();
  Serial.println(values.get_average());
  for(int i= 0; i < values.get_average() / GAIN * NUM_PIXELS; i++) { // For each pixel...
    // pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels_2.setPixelColor(i, 122 * sin(x) + 122, 122 * sin(x + PI / 2) + 122, 122 * sin(x + PI) + 122);
    pixels_1.setPixelColor(i, 122 * sin(x) + 122, 122 * sin(x + PI / 2) + 122, 122 * sin(x + PI) + 122); // periodically oscillates the rgb out of phase with each other
  }
  x += 0.01;
  if (x >= 2 * PI) {
    x = 0;
  }
  pixels_1.show();
  pixels_2.show();
  //delay(DELAYVAL);
}
