// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 144 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    13
#define CLOCKPIN   12
//Adafruit_DotStar strip = Adafruit_DotStar(
//  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BGR);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  //Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  strip.begin(); // Initialize pins for output
  strip.setBrightness(32);
  strip.show();  // Turn all LEDs off ASAP
  //while ( !Serial ) delay(10);   // for nrf52840 with native usb

  //Serial.println(F("Adafruit Bluefruit52 Controller App for Dotstar string"));
  //Serial.println(F("-------------------------------------------"));
  
}

int      head  = 0, tail = -8; // Index of first 'on' and 'off' pixels
uint32_t colorRED = 0xFF0000;      // 'On' color (starts red)
uint32_t colorOFF = 0x000000;      // 'Off' color (starts red)

void loop() {
  //Serial.println(F("in loop"));
  strip.setPixelColor(head, colorRED); // 'On' pixel at head
  digitalWrite(LED_BUILTIN, HIGH); 
  strip.show();                     // Refresh strip
  delay(1000);                        // Pause 20 milliseconds (~50 FPS)
  strip.setPixelColor(head, colorOFF); // 'On' pixel at head
  digitalWrite(LED_BUILTIN, LOW);  
  strip.show();                     // Refresh strip
  delay(1000);
}
