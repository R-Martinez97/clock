#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN        6
#define NUMPIXELS  7
#define DIGLEN     7

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



// variables

// bool d_one[] = {0,0,0,0,0,0,0};
//              0 1 2 3 4 5 6
bool d_one[] = {0,0,1,0,0,0,1};
bool d_two[] = {0,1,1,0,1,1,0};

uint8_t red[]     = {255,0,0};
uint8_t magenta[] = {250, 0, 30};

void dig(const bool d[], const uint8_t c[] ) {
  pixels.clear();
  for(int i=0; i < DIGLEN; i++) {
    bool lit = d[i];
    if(lit) {
      pixels.setPixelColor(i, pixels.Color(c[0], c[1], c[2]));
    } else {
      pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
  }
  pixels.show();
}

    // pixels.setPixelColor(i,pixels.Color(250, 0, 30));

    // if(i<8) {
    //    pixels.setPixelColor(i,pixels.Color(250, 0, 30));
    // } else {
    //    pixels.setPixelColor(i,pixels.Color(250, 80, 130));
    // }






void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  const int dly = 10000;
  

  dig(d_one, red);
  delay(dly);

  dig(d_two, red);
  delay(dly);

  dig(d_one, magenta);
  delay(dly);

  dig(d_two, magenta);
  delay(dly);

  
    // delay(300);
}