// Grafiktest 1.8 Zoll TFT-Farb-Display (HY-1.8 SPI)

#define sclk 13  // Don't change
#define mosi 11  // Don't change
#define cs   10
#define dc   9
#define rst  8  // you can also connect this to the Arduino reset

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_QDTech.h> // Hardware-specific library
#include <SPI.h>

Adafruit_QDTech tft = Adafruit_QDTech(cs, dc, rst);  // Invoke custom library
float p = 3.1415926;
 
void setup(void) {
  tft.init();

  uint16_t time = millis();
  tft.setRotation(0);	// 0 - Portrait, 1 - Lanscape
  tft.fillScreen(QDTech_BLACK);
  tft.setTextWrap(true);
  
  tft.fillRect (0, 0, 63, 18, QDTech_GREEN);
  tft.setTextColor (QDTech_BLACK);
  tft.setCursor(4,6);
  tft.print("LOW:15,5");
  
  tft.setTextColor (QDTech_BLACK);
  tft.fillRect (65,0,62,18,QDTech_RED);
  tft.setCursor(68,6);
  tft.print("High:50,8");
  
  tft.fillRect (0, 20, 64, 18, QDTech_RED);
  tft.fillRect (64, 20, 64, 18, QDTech_GREEN);
  delay(6000);

//tft.setTextColor(QDTech_GREEN);
//  tft.setCursor (0, 2);
//  tft.println ("START:");
//
//  tft.setTextColor (QDTech_BLACK);
//  tft.setTextSize (2);
//  for (int i=3; i>=0; i--) {
//     tft.setCursor (2, 12);
//     tft.fillRect (0, 10, 128, 18, QDTech_GREEN);
//     tft.print (i);
//     tft.print (" seconds");
//     delay(1000);
// }
//  tft.fillScreen(QDTech_BLACK);
  //delay(500);

  // large block of text
  //tft.fillScreen (QDTech_BLACK);
//  tft.fillRect (0, 0, 128, 16, QDTech_GREY);
//  tft.fillRect (0, 24, 128, 16 ,QDTech_BLUE);
  //testdrawtext ("         111111111222123456789012345678901\nScreen is 21 x 20\ncharacters in size.\n", QDTech_WHITE);

  
//  tft.setTextColor(QDTech_RED);
//  tft.setTextSize (1);
//  tft.setCursor (0, 134);
//  tft.println ("Countdown:");
//
//  tft.setTextColor (QDTech_BLACK);
//  tft.setTextSize (2);
//  for (int i=3; i>=0; i--) {
//     tft.setCursor (2, 144);
//     tft.fillRect (0, 142, 128, 18, QDTech_RED);
//     tft.print (i);
//     tft.print (" seconds");
//     delay(1000);
//  }
//  tft.setTextSize(1);
//tft.fillScreen(QDTech_BLACK);
//  delay(500);
//  
//  tft.setCursor (1, 55);
//  tft.setTextColor(QDTech_WHITE);
//  tft.println ("Das ist ein Test und dieser Text mach keinen Sinn, es geht nur darum zu schauen was am ende auf dem Monitor erscheint");




//  testroundrects();
//  delay(500);

//  testmultifillcircles(60);
//  delay(500);

//  testtriangles();
//  delay(500);

//  mediabuttons();
//  delay(500);
}

void loop() {
//tft.invertDisplay(true);
//delay(500);
//tft.invertDisplay(false);
//delay(500);

}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}


