//////////////////////// NEO PIXEL INCLUDE

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//////////////////////// Encoder
#include <BasicEncoder.h>

#define ROTBUTTON     8

BasicEncoder encoder(9,10);

#define LEDPIN        6



// NOT A PIN:::
#define NUMPIXELS     7
#define DIGLEN        7

Adafruit_NeoPixel pixels(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);



// variables

// bool d_one[] = {0,0,0,0,0,0,0};
//                0 1 2 3 4 5 6
bool d_zero[]  = {1,1,0,1,1,1,1};
bool d_one[]   = {0,0,1,0,0,0,1};
bool d_two[]   = {0,1,1,0,1,1,0};
bool d_three[] = {0,1,1,1,0,1,1};
bool d_four[]  = {1,0,1,1,0,0,1};

bool *d_all[] = {d_zero, d_one, d_two, d_three, d_four};
const int d_total = 5;

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



void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();

  Serial.begin(115200);

  pinMode(ROTBUTTON, INPUT);
}


int state = 0;

void loop() {
  const int dly = 10000;
  // dig(d_all[2], red);
  // dig(d_three, red);
  // delay(dly);

  encoder.service();

  int encoder_change = encoder.get_change();
  if (encoder_change != 0) {
    Serial.println(encoder_change);
  }

  state = state + encoder_change;
  Serial.println(state);
  state = (state+d_total) % d_total;

  bool pressed;
  if(digitalRead(ROTBUTTON)) {
    pressed = false;
  } else {
    pressed = true;
  }

  if(pressed) {
    Serial.println("press");
  }
  if(pressed) {
    dig(d_all[state], magenta);

  } else {
    dig(d_all[state], red);
  }
  
}











