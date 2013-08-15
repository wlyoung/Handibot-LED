
#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

int numLEDs = 12;  // number of LEDs in strip
int dataInput = 6; // the input switch connection from the data line on the strip to the arduino

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs, dataInput, NEO_GRB + NEO_KHZ800);
//****************************************************************************/

void setup() {
  // Configure the ShopBot Output switch connections
  
   pinMode(2, INPUT_PULLUP);  // SB Output #1 connected to Arduino Input #2
   pinMode(4, INPUT_PULLUP);  // SB Output #4 connected to Arduino Input #4
   pinMode(5, INPUT_PULLUP);  // SB Output #5 connected to Arduino Input #5
   

  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}


void loop() {
  int sensorVal1 = digitalRead(2); // the connection to the #1 output...there's no #1 input on these Arduinos
  int sensorVal4 = digitalRead(4); // the connection to the #4 output
  int sensorVal5 = digitalRead(5); // the connection to the #5 output
  int switchVal = 0;
  
if (sensorVal1 == HIGH) switchVal =1; 
else if (sensorVal4 == HIGH) switchVal =4;  
else if (sensorVal5 == HIGH) switchVal =5; 

 switch (switchVal)  
 {
   case 1: // fade all pixels RED and then off
         {
           int j;
           int i;
           for (j = 0; j < 127; j++)
              for (i=0; i < strip.numPixels(); i++)
              {
                strip.setPixelColor(i, strip.Color(j,0,0)); //Red
                strip.show();
              }
            delay(4); // adjust this have to speed up or slow down fade time
         }
       
      
     break;
     
   case 4: // random pixel flashes in RED
     for (int p = 0; p < 20; p++)
       {
         
         colorRnd(strip.Color(127,   0,   0), 10); // Red
         colorRnd(strip.Color(127,   0,   0), 10); // Red
       }
     break;
     
   case 5: // YELLOW pixel chace down the strip
     {
       colorWipe(strip.Color(0,   0,   0), 50);  // Off
       strip.show();
       colorWipe(strip.Color(125,   125,   0), 50);  // Yellow
        strip.show();
     }
     break;
     
   default: // all pixels GREEN 
      {
     colorWipe(strip.Color(0,   125,   0), 0);  // Green
      strip.show();
       }
       
 } 

 }
  
// blink random leds
void colorRnd(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  //for(i=0; i<5; i++) {
    int pixelnum = random(numLEDs);
    strip.setPixelColor(pixelnum, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(pixelnum, 0); // Erase pixel, but don't refresh!
    delay(wait);
  //}

  strip.show(); // Refresh to turn off last pixel
}

// Fill the dots progressively along the strip....we don't use
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
