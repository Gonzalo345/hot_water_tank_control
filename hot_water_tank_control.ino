// LCD_128x64_ST7920_DS18B20_DHT11
//
// Dallas DS18B20 temperature sensor on pin 6
// DHT11 relative humidity sensor (humidity only) on pin 8
// display
// Uses Olikraus' u8g library
// by Gonzalo Yarv
// 7:46, 20, 5, 2017

#include "U8glib.h"
#include <OneWire.h>
#include <Wire.h>
#include "RTClib.h"
#include <DallasTemperature.h>
#include <DHT.h>

RTC_DS3231 rtc;             // SDA D4 digital 04 pin 7 SCL D5 digital pin 05 pin 08
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int ledPIN = 13;
const int boton1 = 3;
//const int valvePIN = 3;

//DS3231  rtc(SDA, SCL);
char temp_string[3]; //empty char array to hold the converted temp float
char time_string[6]; //
char hum_string[5];  //empty char array to hold the converted humidity float
float hum_float;

// display constructor for u8g library - this one depends on your type of display
U8GLIB_ST7920_128X64 u8g(13, 11, 12, U8G_PIN_NONE);

// DS18B20 section ================================================================

// one wire data probe to pin 6
#define ONE_WIRE_BUS_PIN 6

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress Probe_01 = {0x28, 0xE4, 0xA4, 0x79, 0xA2, 0x00, 0x03, 0xA7};

// each DS18B20 has each own unique address - use address finder sketch


// DHT11 section ==================================================================
// tell the DHT library where to expect a DHT sensor and which type
DHT DHT_sens(8, DHT11);                //  connected to pin 8 of the Arduino


void setup() {

   //pinMode(ledPIN, OUTPUT);
   //pinMode(resistorPIN, OUTPUT);
   //pinMode(valvePIN, OUTPUT);
   pinMode(boton1, INPUT);
   DHT_sens.begin();                       // start DHT sensoring
   sensors.begin();                        // START dallas temperature sensoring
   sensors.setResolution(Probe_01, 10);    // set DS18B20 sensor resolution to 10 bit
   Serial.begin(9600);                     // start serial port
   Serial.print("DS18B20 Temperature Control Library Version ");
   Serial.println(DALLASTEMPLIBVERSION);
   Serial.println ();
   Serial.println ("DHT11 humidity sensor (temp not implemented)");
   Serial.print("Number of Devices found on bus = ");
   Serial.println(sensors.getDeviceCount());
   Serial.println ("============================================");
   
   Serial.print("Getting temperature, humidity... ");
   Serial.println();
   if (! rtc.begin()) {
     Serial.println("Couldn't find RTC");
     while (1);
   }
   //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   if (rtc.lostPower()) {
     Serial.println("RTC lost power, lets set the time!");
     // Comment out below lines once you set the date & time.
     // Following line sets the RTC to the date & time this sketch was compiled
     //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

     // Following line sets the RTC with an explicit date & time
     // for example to set January 27 2017 at 12:56 you would call:
     // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
   }


   // Select font =================================================================

   u8g.setFont(u8g_font_5x7);
   u8g.setColorIndex(1);                   // Instructs the display to draw with a pixel on.
}

void loop() {
  unsigned char i = 0;
  for (i=0; i<36; i+=8){
    u8g.firstPage();
    do {
      fill(i);
      draw();
    }
    while( u8g.nextPage() );
    //digitalWrite(ledPIN, HIGH);
    DateTime now = rtc.now();
    //digitalWrite(resistorPIN, HIGH);
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(2000);
    //digitalWrite(ledPIN, LOW);
    //digitalWrite(resistorPIN, LOW);
    delay(2000);
  }
}

void draw(){

  u8g.setFont(u8g_font_5x7);
  // upper frame ===============================================================
  u8g.drawFrame(65,5,8,8);
  u8g.drawStr( 60, 20, "Carg"); //Carga
  u8g.drawFrame(85,5,8,8);
  u8g.drawStr( 83, 20, "Res");
  u8g.drawFrame(105,5,8,8);
  u8g.drawStr( 102, 20, "Frio"); // Frio
  //u8g.drawFrame(112,5,8,8);
  //u8g.drawStr( 112, 20, "Ca");
  // lower frame =============================================================
  //u8g.setFont(u8g_font_5x7);
  //u8g.setFont(u8g_font_micro);
  //u8g.drawFrame(9,51,8,8);
  //u8g.drawStr( 11, 58, "R");
  //u8g.drawFrame(22,51,8,8);

  //u8g.drawFrame(35,51,8,8);
  //u8g.drawFrame(48,51,8,8);
  // level circle ============================================================
  u8g.drawCircle(88, 42, 18);
  // Auto ====================================================================
  u8g.setFont(u8g_font_5x8);
  u8g.drawStr(105,60, "Auto");
  // clocks ==================================================================
  u8g.drawCircle(10, 34, 5);
  u8g.drawLine(10, 34, 13, 34);
  u8g.drawLine(10, 34, 10, 31);
  u8g.drawCircle(10, 52, 5);
  u8g.drawLine(10, 52, 10, 49);
  u8g.drawLine(10, 52, 13, 52);
  // Times oo ================================================================
  u8g.drawCircle(20, 31, 2);
  u8g.drawCircle(20, 37, 2);
  u8g.drawCircle(20, 49, 2);
  u8g.drawCircle(20, 56, 2);
  // Cte =====================================================================
  u8g.setFont(u8g_font_5x8);
  u8g.drawStr(30,57, "TCte");
  // Time ====================================================================
  u8g.setFont(u8g_font_10x20);
  DateTime now = rtc.now();
  dtostrf(now.hour(), 2, 0, time_string);
  u8g.drawStr(5,17, time_string);
  u8g.drawStr(22,17, ":");
  dtostrf(now.minute(), 2, 0, time_string);
  u8g.drawStr(30,17, time_string);
  
  //
  // Temperature =============================================================
  //  u8g.setFont(u8g_font_10x20);
  //  u8g.drawStr(30,42, "24");
  // °C ======================================================================
  //u8g.drawCircle(52, 29, 1);
  //u8g.drawStr(53,42, "C");

  // DS18B20 section ===========================================================
  sensors.requestTemperatures();

  Serial.print("temperatura: ");
  float tempC = sensors.getTempC(Probe_01);
  //float tempC = DHT_sens.readTemperature();
  //float tempC = 17.6;
  Serial.print (tempC,1);
  Serial.println(" *C\t");
  if (tempC == -127.00)
  {
  Serial.print("Error getting temperature  ");
  }
  else
  {

  // DHT 11 section ================================================================
  hum_float = DHT_sens.readHumidity();
  //hum_float = 40.0;
  Serial.print ("Humedad: ");
  Serial.print (hum_float,1);
  Serial.print (" %\t");
  Serial.println();

  // convert floats into char u8g strings
  // u8g.drawStr( 15, 13, "Temp");       // do this for temperature
  dtostrf(tempC, 2, 0, temp_string);
  // Temperature =============================================================
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(30,42, temp_string);
  // °C ======================================================================
  u8g.drawCircle(52, 30, 1);
  u8g.drawStr(54,42, "C");


  //u8g.drawStr(26,45, "Hum");             // do this for humidity
  //dtostrf(hum_float, 3, 1, hum_string);
  //u8g.drawStr(40,60, hum_string);
  //u8g.drawStr(75,60, "%");

  }
}

void fill(unsigned char percent) {     // Filled test
    // Llenado circulo 25% =====================================================
  unsigned char largo[] = {4,  7,   9, 10, 11, 12, 13, 14, 15, 15, 16, 16, 17,
  17, 17, 17, 17, 17, 17, 17, 17 , 17, 16, 16, 16, 15, 15, 14, 13, 12, 11, 10,
   9,  7,  4};
  unsigned char i, x, y;
  y = 59;
  x = 88;
  for (i=0; i < percent; i++){
    u8g.drawLine(x-largo[i] , y-i, x+largo[i] , y-i);
  }
  u8g.setFont(u8g_font_5x8);
  if (percent <= 8)                   u8g.drawStr(105,30, "25%" );
  if (percent > 8  && percent <= 17)  u8g.drawStr(105,30, "50%" );
  if (percent > 17 && percent <= 26)  u8g.drawStr(105,30, "75%" );
  if (percent > 26 && percent <= 35)  u8g.drawStr(105,30, "100%");
}
