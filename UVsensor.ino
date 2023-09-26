 /*  GUVA-S12SD-UV-ModuleMade on 03 Feb 2020 by Amir Mohammad Shojaee @ Electropeak Home */
//This file is a mixture of two combine into one you will need the following required files
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
//gps drivers and decoder
//#include <TinyGPS++.h>

//sd card includes
#include <SPI.h>             // f.k. for Arduino-1.5.2
#define USE_SDFAT
#include <SdFat.h>           // Use the SdFat library

#if SPI_DRIVER_SELECT != 2
#error edit SdFatConfig.h .  READ THE SKETCH INSTRUCTIONS
#endif

SoftSpiDriver<12, 11, 13> softSpi; //Bit-Bang on the Shield pins SDFat.h v2
SdFat SD;
#define SD_CS SdSpiConfig(10, DEDICATED_SPI, SD_SCK_MHZ(50), &softSpi)


//TinyGPSPlus gps; // create gps object
File myFile;

MCUFRIEND_kbv tft;
//#include "DHT.h"

#define DHTPIN 23
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//String Latitude, Longitude, Altitude, Speed, Temp, Hum, day, month, year, hour, minute, second, Date, Time, Data;

// work in line numbers.  Font height in ht
int16_t ht = 16, top = 3, line, lines = 1, scroll;
void setup() 
{
  Serial.begin(9600);
  uint16_t id = tft.readID();
    tft.begin(id);
    tft.setRotation(45);     //Portrait
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);     // System font is 8 pixels.  ht = 8*2=16
    tft.setCursor(60, 0);
    tft.print("The Bickering Pigs UV Detector V01.0");
    tft.setCursor(2,20)
    tft.print("UV Reading = ");
    tft.setCursor(2,40)
    tft.print("Voltage = ");
}
 
void loop() 
{
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A7);
  sensorVoltage = sensorValue/1024*5.0;

  tft.vertScroll(top * ht, lines * ht, (scroll) * ht);
  tft.setTextColor(WHITE,BLACK);
  tft.setCursor(60,20)
  tft.print(sensorValue);
  tft.setCursor(60,40)
  tft.print(sensorVoltage);
  tft.println(" V");
  delay(1000);
  line++;
}