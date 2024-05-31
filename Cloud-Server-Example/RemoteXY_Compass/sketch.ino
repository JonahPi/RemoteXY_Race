#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>

#define REMOTEXY_MODE__WIFI_CLOUD

#define WIFI_CHANNEL 6

#define REMOTEXY_WIFI_SSID "Wokwi-GUEST"
#define REMOTEXY_WIFI_PASSWORD ""
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "your-token"

#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 26 bytes
  { 255,4,0,0,0,19,0,17,0,0,0,31,1,106,200,1,1,1,0,8,
  43,90,20,20,0,24 };
  
// this structure defines all the variables and events of your control interface 
struct {
    // input variables
  float compass_01; // from 0 to 359.999

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)

#define PIN 27 // Pin connected to the NeoPixel ring
#define NUMPIXELS 17 // Number of LEDs in the NeoPixel ring

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  RemoteXY_Init(); 
  pixels.begin(); // Initialize the NeoPixel library
  pixels.clear(); // Clear all the pixels
  pixels.show(); // Make sure all pixels are off
}

void loop() { 
  RemoteXY_Handler();
  
  // Scale compass value to the range of LED indices
  int ledIndex = map(RemoteXY.compass_01, 0, 359, 0, NUMPIXELS - 1);
  
  // Update the LEDs
  updateLEDs(ledIndex);
}

void updateLEDs(int ledIndex) {
  pixels.clear(); // Turn off all LEDs
  pixels.setPixelColor(ledIndex, pixels.Color(255, 0, 0)); // Turn on the LED corresponding to the compass direction
  pixels.show(); // Update the ring with the new LED state
}
