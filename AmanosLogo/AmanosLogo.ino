#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    32 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {  
  0,     29,  58,  255,   //bleu
  128,   201,  14,  117,   //rose
  255,   29,  58, 255 }; //bleu

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );     
  currentPalette = heatmap_gp;
  currentBlending = LINEARBLEND;

}

void loop() {
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
    
  FillLEDsFromPaletteColors( startIndex);
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
  
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 64 ;
    CRGBPalette16 myPal = heatmap_gp;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( myPal, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
