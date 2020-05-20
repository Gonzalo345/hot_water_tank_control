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
   #include <DallasTemperature.h>
   #include <DHT.h>

   char temp_string[5]; //empty char array to hold the converted temp float
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
   DeviceAddress Probe_01 = {0x28, 0xFF, 0x0A, 0x75, 0xA3, 0x15, 0x04, 0xBC};
// each DS18B20 has each own unique address - use address finder sketch


// DHT11 section ==================================================================
// tell the DHT library where to expect a DHT sensor and which type
   DHT DHT_sens(8, DHT11);                //  connected to pin 8 of the Arduino


   void setup() {

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


  // Select font =================================================================

  //u8g.setFont(u8g_font_unifont);
  u8g.setFont(u8g_font_5x7);
  // u8g.setFont(u8g_font_unifont_0_8);
  // u8g.setFont(u8g_font_courB10);
  // u8g.setFont(u8g_font_courB08);
  // u8g.setFont(u8g_font_7x14B);
  // u8g.setFont(u8g_font_8x13);
  // u8g.setFont(u8g_font_osb21);

  u8g.setColorIndex(1);                   // Instructs the display to draw with a pixel on.
}

void loop() {
  unsigned char i = 0;
 for (i=0; i<36; i++){
    u8g.firstPage();
    do {
      fill(i);
      draw();
    } while( u8g.nextPage() );
 }
}

void draw(){
 //int i;
  //u8g.setFont(u8g_font_micro);
  u8g.setFont(u8g_font_5x7);
  // upper frame ===============================================================
  u8g.drawFrame(73,5,8,8);
  u8g.drawStr( 73, 20, "Bo");
  u8g.drawFrame(86,5,8,8);
  u8g.drawStr( 86, 20, "Ca");
  u8g.drawFrame(99,5,8,8);
  u8g.drawStr( 99, 20, "Fr");
  u8g.drawFrame(112,5,8,8);
  u8g.drawStr( 112, 20, "Ca");
  // lower frame =============================================================
  u8g.setFont(u8g_font_5x7);
  //u8g.setFont(u8g_font_micro);
  u8g.drawFrame(9,51,8,8);
  u8g.drawStr( 11, 58, "R");
  u8g.drawFrame(22,51,8,8);

  u8g.drawFrame(35,51,8,8);
  u8g.drawFrame(48,51,8,8);
  // level circle ============================================================
  u8g.drawCircle(88, 42, 18);
  u8g.setFont(u8g_font_5x8);
  u8g.drawStr(105,30, "100%");

  // Auto ====================================================================
  u8g.setFont(u8g_font_5x8);
  u8g.drawStr(105,60, "Auto");
  // clocks ==================================================================
  u8g.drawCircle(10, 10, 5);
  u8g.drawLine(10, 10, 13, 10);
  u8g.drawLine(10, 10, 10, 7);
  u8g.drawCircle(10, 25, 5);
  u8g.drawLine(10, 25, 10, 22);
  u8g.drawLine(10, 25, 13, 25);
  // Times oo ================================================================
  u8g.drawCircle(20, 7, 2);
  u8g.drawCircle(20, 13, 2);
  u8g.drawCircle(20, 22, 2);
  u8g.drawCircle(20, 28, 2);
  // °C ======================================================================
  u8g.drawCircle(54, 30, 1);
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(57,36, "C");
  // Cte =====================================================================
  u8g.setFont(u8g_font_5x8);
  u8g.drawStr(54,47, "Ct");
  // Time ====================================================================
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(27,18, "14:07");
  // Temperature =============================================================
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(27,47, "24");

  // DS18B20 section ===========================================================
  sensors.requestTemperatures();

  Serial.print("temperatura: ");
  //float tempC = sensors.getTempC(Probe_01);
  float tempC = DHT_sens.readTemperature();
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
  dtostrf(tempC, 2, 1, temp_string);
  //u8g.drawStr(27,45, "temp_string");
  //u8g.drawStr(70,27, "C");

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
}
