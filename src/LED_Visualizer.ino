/**
  LED-Music-Visualizer                        ▄██▄██▄
  Based on Devon Crowford's youtube video     ▀█████▀
  No frequecny to voltage converter necesary    ▀█▀

@echan42
**/

#include "FastLED.h"

//  #~~~~~~~~~~~~~~~~~~~~~~~~~~#
//  #      LED Variables       #
//  #  Define Strip properties #
//  #~~~~~~~~~~~~~~~~~~~~~~~~~~#

#define NUM_LEDS 300        
#define updateLEDS 3        
#define COLOR_SHIFT 50  
CRGB leds[NUM_LEDS];        

//  #~~~~~~~~~~~~~~~~~~~~~~~~~~#
//  #    Arduino Variables     #
//  #  Define Pin Variables    #
//  #~~~~~~~~~~~~~~~~~~~~~~~~~~#

// Digital pins
#define DATA_PIN 6          
#define DATA_PIN2 5
#define DATA_PIN3 4
#define DATA_PIN4 7

//Analog pins
#define PITCH_PIN 4         
#define BRIGHT_PIN 4        


unsigned long setTime = COLOR_SHIFT;
int shiftC = 0;
int mulC = 2;

// Initialize RGB variables 
struct color {
  int r;
  int g;
  int b;
};
typedef struct color Color;

void setup() { 
    Serial.begin(9600);
  	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    pinMode(A4, INPUT);

    for(int i = 0; i < NUM_LEDS ; i++) {
      leds[i] = CRGB(0,0,0);
    }  
    
    FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds, NUM_LEDS);
    pinMode(A4, INPUT);

    for(int i = 0; i < NUM_LEDS ; i++) {
      leds[i] = CRGB(0,0,0);
    }
    
    FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds, NUM_LEDS);
    pinMode(A4, INPUT);

    for(int i = 0; i < NUM_LEDS ; i++) {
      leds[i] = CRGB(0,0,0);
    }
    
    FastLED.addLeds<NEOPIXEL, DATA_PIN4>(leds, NUM_LEDS);
    pinMode(A4, INPUT);

    for(int i = 0; i < NUM_LEDS ; i++) {
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
}

void loop() { 
  unsigned long time = millis();

  // Shift the color spectrum by 200 on set intervals (setTime)
  if(time / (double)setTime >= 1) {
    setTime = time + COLOR_SHIFT;
    Serial.println(setTime);
    shiftC += 200;
    mulC++;
    if(shiftC >= 600) {
      shiftC = 0;
    }
    if(mulC > 3) {
      mulC = 2;
    }
  }

  // Left Shift
  for(int i = NUM_LEDS - 1; i >= updateLEDS; i--) {
    leds[i] = leds[i - updateLEDS];
  }

  // Change *3 to achieve diferent effects (don't really know what it does but it works)
  int newPitch = (analogRead(BRIGHT_PIN)*3) + shiftC;
  
  Color nc = pitchConv(newPitch, analogRead(BRIGHT_PIN));
  
  for(int i = 0; i < updateLEDS; i++) {
    leds[i] = CRGB(nc.r, nc.g, nc.b);
  }
  FastLED.show();

  // Uncomment for print
  //printColor(nc);
  delay(6);
}


//What follows is actually stolen word for word from Devon Crowford
/**
 * Converts the analog brightness reading into a percentage
 * 100% brightness is 614.. about 3 volts based on frequency to voltage converter circuit
 * The resulting percentage can simply be multiplied on the rgb values when setting our colors,
 * for example black is (0,0,0) so when volume is off we get 0v and all colors are black (leds are off)
 */
double convBrightness(int b) {
  double c = b / 614.0000;
  if( c < 0.2 ) {
    c = 0;
  }
  else if(c > 1) {
    c = 1.00;
  }
  return c;
}

/**
 * Creates a new color from pitch and brightness readings
 * int p         analogRead(pitch) representing the voltage between 0 and 5 volts
 * double b      analogRead(brightness) representing volume of music for LED brightness
 * returns Color structure with rgb values, which appear synced to the music
 */
Color pitchConv(int p, int b) {
  Color c;
  double bright = convBrightness(b);

  if(p < 40) {
    setColor(&c, 255, 0, 0);
  }
  else if(p >= 40 && p <= 77) {
    int b = (p - 40) * (255/37.0000);
    setColor(&c, 255, 0, b);
  }
  else if(p > 77 && p <= 205) {
    int r = 255 - ((p - 78) * 2);
    setColor(&c, r, 0, 255);
  }
  else if(p >= 206 && p <= 238) {
    int g = (p - 206) * (255/32.0000);
    setColor(&c, 0, g, 255);
  }
  else if(p <= 239 && p <= 250) {
    int r = (p - 239) * (255/11.0000);
    setColor(&c, r, 255, 255);
  }
  else if(p >= 251 && p <= 270) {
    setColor(&c, 255, 255, 255);
  }
  else if(p >= 271 && p <= 398) {
    int rb = 255-((p-271)*2);
    setColor(&c, rb, 255, rb);
  }
  else if(p >= 398 && p <= 653) {
    setColor(&c, 0, 255-(p-398), (p-398));
  }
  else {
    setColor(&c, 255, 0, 0);
  }
  setColor(&c, c.r * bright, c.g * bright, c.b * bright);
  return c;
}

void setColor(Color *c, int r, int g, int b) {
  c->r = r;
  c->g = g;
  c->b = b;
}

// Prints color structure data
void printColor(Color c) {
  Serial.print("( ");
  Serial.print(c.r);
  Serial.print(", ");
  Serial.print(c.g);
  Serial.print(", ");
  Serial.print(c.b);
  Serial.println(" )");
}
