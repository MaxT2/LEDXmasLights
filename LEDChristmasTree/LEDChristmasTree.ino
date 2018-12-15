#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 350
//#define NUM_STRIPS 7
//For led chips like Neopixels, which have data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
#define CLOCK_PIN 13


// Define the array of leds

CRGB leds[NUM_LEDS];
int BRIGHTNESS = 150;
int SATURATION = 255;
int x = 0;
int xSpeed = 1;
int hue = 0;
int huespeed = 1;
int speedDelay = 10;
int ledPos = 5;
int direction = 1;
int colorPos = 0;
int groupSize = 1;
int rnum = 0;


// define some colors to use

CHSV red = CHSV(0, SATURATION, BRIGHTNESS);
CHSV orange = CHSV(32, SATURATION, BRIGHTNESS);
CHSV yellow = CHSV(64, SATURATION, BRIGHTNESS);
CHSV green = CHSV(96, SATURATION, BRIGHTNESS);
CHSV aqua = CHSV(128, SATURATION, BRIGHTNESS);
CHSV blue = CHSV(160, SATURATION, BRIGHTNESS);
CHSV purple = CHSV(192, SATURATION, BRIGHTNESS);
CHSV pink = CHSV(224, SATURATION, BRIGHTNESS);

//CRGB red = CRGB(255, 0, 0);
//CRGB orange = CRGB(255,100,0);
//CRGB yellow = CRGB(255, 255, 0);
//CRGB green = CRGB(0, 255, 0);
//CRGB aqua = CRGB(200, 100, 100);
//CRGB blue = CRGB(0,0,255);
//CRGB purple = CRGB(255,0,255);
//CRGB pink = CRGB(255,20,147);


CHSV colors[] = {red, orange, yellow, green, aqua, blue, purple, pink};
//CRGB colors[] = {red, orange, yellow, green, aqua, blue, purple, pink};




void setup() {
  // setup led array
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  // set max BRIGHTNESS for power regulation
  FastLED.setBrightness(BRIGHTNESS);

  // these fill the strip with a pattern
  //    traditionalLights();
  //    randomColor();
  //    fillRandomColor();
  //  fillColor(CRGB::Red);
  //  fillPattern(red, green, 50);
  // multiColorRainbow();


  FastLED.show();
  //

}

void loop() {

  demo();

  // rotate strip with delay in ms
  //  rotate(15);
  //RAVE();


  //
  //  cycles through rainbow as a whole strip
  //  rainbow(100);
  //
  //  light up each strand from start to end with green
  //  strandLoop(5);
  //
  //  single pixel moving along the strip
  //  singleMove();
  //
  //  rotate through an array of colors changing them by sweeping down the srip
  //  slowSweepChange();
  //
  //  rainbow and rainbow hue look the same but are technically different
  //  rainbow(50);
  //  rainbowHueRange();
  //
  //  multiColorRainbow(1);
  //
  //  randomTwinkle(10, 20);





  // not working
  //blueTwinkle(1);
  //
  //  thunderLightning();
  //  reverseBlueWhite();



  // Tachoyn - Jaytech 4:50-5:05
  // slow buildup/
  //4:57 flash



}

void demo() {
  int cycles = 100;
  traditionalLights();
  for (int i = 0; i < cycles; i++) {
    rotate(100);
  }

  for (int i = 0; i < 5; i++) {
    slowSweepChange();    
  }

  fillPattern(red,green,10);
  for (int i = 0; i < cycles; i++) {
    rotate(100);    
  }

  for (int i = 0; i < NUM_LEDS*2; i++) {
    RAVE();    
  }

  fillColorSweep(CHSV(0,SATURATION, BRIGHTNESS));

  for (int i = 0; i < cycles; i++) {
    rainbow(50);    
  }

// sudden transition

  for (int i = 0; i < cycles; i++) {
    multiColorRainbow(50);   
  }

  for (int i = 0; i < cycles; i++) {
    strandLoop(5);   
  }






}

/*
    basic fuctions!
    IdeaBoard:
    Thunder lightning like Adam's

*/

// fill strip with random colors
void fillRandomColor() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(rand() % 255, SATURATION, BRIGHTNESS);
  }
}


// fill with a CHVS OR CRGB color
void fillColor(CHSV color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}
void fillColor(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

// fill sweep with a CHVS OR CRGB color
void fillColorSweep(CHSV color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
  }
}
void fillColorSweep(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
  }
}


// fill strip with alternating pattern in a certain groupsize
void fillPattern(CHSV color1, CHSV color2, int group) {
  CHSV color[2] = {color1, color2};
  int position = 1;

  for (int i = 0; i < NUM_LEDS; i += 1 * group) {
    for (int j = 0; j < group; j++) {
      leds[i + j] = color[position];
    }
    if (position == 0) {
      position = 1;
    }
    else {
      position = 0;
    }
  }
}


// rotate any pattern around the strip with a delay between updates
void rotate(int delayS) {
  CRGB lastColor = leds[NUM_LEDS - 1];

  for (int i = NUM_LEDS - 1; i > -1; i--) {
    if ( i == 0) {
      leds[0] = lastColor;
    }
    else {
      leds[i] = leds[i - 1];
    }
  }
  FastLED.show();
  if (delayS != 0) {
    delay(delayS); // delay change input in miliseconds
  }
}



/*
      Slowly fills the strip with random colors by shifting all colors up by 1 and then adds a random color to the start
      Idealy you start this when the strip is already lit or after another patern. If you start this on its own you
      you should run a setup fuction that sets every led to a color before the first FastLED.show

*/

// super quick flashy and colorful
void RAVE() {


  // random colors, shift all down the line then add a random at the begining of the strand
  for (int i = (NUM_LEDS - 1); i > 0 - 1; i--) {
    if (i == 0) {
      //        leds[0] = CRGB((rand() % 100), (rand() % 100), (rand() % 100));
      leds[0] = CHSV((rand() % 255), SATURATION, BRIGHTNESS);

    }
    leds[i + 1] = leds[i];
    // don't delay here because it slows everything down too much
  }


  FastLED.show();
  delay(50); // delay after you updated the entire strip. 50 super fast. 100 fast.


}























/*
   WORKS IN PROGRESS
   some of these may function
   some may do nothing at all
*/



// treats each strand as their own individual strip and they all do the same thing
// currently just fills with a random color
void strandLoop(int numStrands) {

  for (int i = 0; i < (NUM_LEDS / numStrands) - 1; i++) {
    for (int j = 0; j < numStrands; j++) {
      leds[i + (j * 50)] = CHSV(rand() % 255, SATURATION, BRIGHTNESS);
      FastLED.show();
      delay(15);
    }
  }
//  FastLED.clear();
  delay(200);
  FastLED.show();
}


// not working yet
// currently not alternating
void twoColorAlternate(CHSV color1, CHSV color2, int delays) {

  for (int i = NUM_LEDS; i > -1; i--) {
    if (i % 2 == 0) {
      leds[i] = color1;
    } else {
      leds[i] = color2;
    }
    FastLED.show();
    delay(delays);
    for (int i = NUM_LEDS; i > -1; i--) {
      if (i % 2 == 0) {
        leds[i] = color2;
      } else {
        leds[i] = color1;
      }
    }
    FastLED.show();
    delay(delays);

  }
}

// sorta working but occationally a light is not set back to the stored value after the flash
void randomTwinkle(int delaySpeed, int burstCount ) {
  // generate 5 random numbers

  CRGB stored[burstCount] = {CRGB::Black};
  int randoms[burstCount] = {0};
  for (int i = 0; i < burstCount; i++) {
    randoms[i] = (rand() % NUM_LEDS);
    stored[i] = leds[randoms[i]];
    leds[randoms[i]] = CRGB(200, 200, 200);

  }

  FastLED.show();
  if (delaySpeed != 0) {
    delay(50);
  }
  for (int j = 0; j < burstCount; j++) {
    leds[randoms[j]] = stored[j];

  }
  FastLED.show();

  if (delaySpeed != 0) {
    delay(50);
  }
  delay(1000);
}


// twinkle with frequency
void Twinkle(int frequency) {
  for (int i = 0; i < frequency; i ++) {
    int r = rand() % NUM_LEDS;
    CRGB currentColor = leds[r];
    leds[r] = CRGB::White;
    FastLED.show();
    leds[r] = currentColor;
    FastLED.show();
    delay(100);
  }
}



// twinkle one light
// simple but better if you have input for more options
void Twinkle() {
  int r = rand() % NUM_LEDS;
  CRGB currentColor = leds[r];
  leds[r] = CRGB::White;
  FastLED.show();
  leds[r] = currentColor;
  FastLED.show();
  delay(500);
}




void randomColor() {

  for (int i = (NUM_LEDS - 1); i > 0 - 1; i--) {
    if (i == 0) {
      //        leds[0] = CRGB((rand() % 100), (rand() % 100), (rand() % 100));
      leds[0] = CHSV((rand() % 255), SATURATION, BRIGHTNESS);

    }
    leds[i + 1] = leds[i];
    //      delay(10);
  }


  FastLED.show();
  delay(50);

  //  delay(10);
  //    delay(400);


}

void multiColorRainbow(int delayms) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 2), SATURATION, BRIGHTNESS);
    //    FastLED.show();

  }
  hue += 1;
  if (hue > 255) {
    hue = 0;
  }
  FastLED.show();

  delay(delayms);


}

void rainbow(int delaySpeed) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, SATURATION, BRIGHTNESS);
  }
  // change += to increase difference between updates
  hue += 1;
  if (hue > 255) {
    hue = 0;
  }
  FastLED.show();
  delay(delaySpeed);


}

// supposidly hue boucnes between values instead of looping which are pretty much the same
//void rainbowHueRange() {
//
//  for (int i = 0; i < NUM_LEDS; i++) {
//
//    leds[i] = CHSV(hue, SATURATION, BRIGHTNESS);
//
//  }
//  FastLED.show();
//  delay(50);
//  if (hue == 255 || hue == 0) {
//    huespeed *= -1;
//  }
//  hue += huespeed;
//
//}


void slowSweepChange() {

  for (int i = 0; i < NUM_LEDS; i++) {

    leds[i] = colors[colorPos];
    FastLED.show();
    delay(20);
  }

  colorPos += 1;
  if (colorPos > 7) {
    colorPos = 0;
  }




}




void singleMove() {
  for (int i = 0; i < NUM_LEDS; i++) {

    leds[i] = blue;
    FastLED.show();
    delay(50);
    leds[i] = CRGB::Black;
  }
}





void traditionalLights() {

  for ( int i = 0; i < NUM_LEDS; i++) {
    switch (i % 5) {
      case 0:
        leds[i] = red;
        break;

      case 1:
        leds[i] = green;
        break;

      case 2:
        leds[i] = blue;
        break;

      case 3:
        leds[i] = pink;
        break;

      case 4:
        leds[i] = orange;
        break;

    }



  }
  FastLED.show();
}


void blueTwinkle(int variation) {
  switch (variation) {
    case 1:
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = blue;
      }

      FastLED.show();

      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }

      delay(200);
      for (int i = 0; i < 10; i++) {
        rnum = rand() % 49;
        leds[rnum] = CRGB::White;
        FastLED.show();
        delay(20);
        leds[rnum] = blue;
        FastLED.show();
        delay(600);

      }
      break;

  }
}

// something to go along to a song to work on eventually
void tachyon() {

}
