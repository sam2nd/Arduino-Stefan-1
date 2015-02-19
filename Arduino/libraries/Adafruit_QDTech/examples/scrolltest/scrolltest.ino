/* 
 Test hardware vertical scroll for Samsung S6D02A1 TFT driver chip. 
 vScroll rolls the frame by changing the Start Address of the vertical scroll area in the frame buffer. 
 */


#define sclk 13  // Don't change
#define mosi 11  // Don't change
#define cs   9
#define dc   8
#define rst  7  // you can also connect this to the Arduino reset

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_QDTech.h> // Hardware-specific library
#include <SPI.h>

Adafruit_QDTech tft = Adafruit_QDTech(cs, dc, rst);  // Invoke custom library


void setup(void) {
  tft.init();

  tft.setRotation(0);	// 0 - Portrait, 1 - Lanscape
  tft.fillScreen(QDTech_BLACK);
  tft.setTextWrap(true);

  delay(500);


  tft.setTextColor(QDTech_WHITE);

  tft.setCursor (0,0);
  tft.print ("Hardware VScroll example\n\n Written By Mel.\n\n22 August 2014\n\n\nFor the QDTech TFT180A with Samsung S6D02A1 display driver chip\n\n Using a version of the Adafruit TFT Library modified by Gilchrist with Vertical Scroll support added by me");

  delay(5000);
  tft.setTextWrap(false);  //

#define FONTHEIGHT 8

#define TFA  21  //Top Fixed Area (height)
#define BFA  11  // Bottom Fixed Area - best leave a multiple of font height for scroll area to avoid blank lines.


#define TOPOFBOTTOM (QDTech_TFTHEIGHT - BFA)

  tft.fillRect (0, 0, QDTech_TFTWIDTH, TFA, QDTech_BLUE);
  tft.fillRect (0, TOPOFBOTTOM , QDTech_TFTWIDTH, TFA, QDTech_GREY);

  tft.setTextColor(QDTech_WHITE);

  tft.setCursor(0, 4);
  tft.print("     Scroll Test    "); 

  tft.drawFastHLine(0, TFA - 1, tft.width(), QDTech_GREEN);   // botttom of top fixed 


  // enable scroll

  int vsh = tft.setScrollWindow(TFA,BFA);

  tft.drawFastHLine(0, TOPOFBOTTOM, tft.width(), QDTech_BLUE);   //BFA  

  tft.setCursor(0, TOPOFBOTTOM + 3);
  tft.setTextColor(QDTech_MAGENTA,QDTech_GREY);

  tft.print("  vsp = "); 

  int vsp= 0;

  unsigned int colour = 0;

  delay(3000);

  while(1){

    int y = vsp -1;  //y =bottom line of scroll area 
    if (y<0) y+=vsh; 

    tft.drawFastHLine(0, TFA + y, QDTech_TFTWIDTH, QDTech_BLACK);   //erase what will be bottom line


    if((vsp%FONTHEIGHT) ==0) {  //have we scrolled enough to fit a line of text yet

      colour+= 0b0010001001000101;      


      int y = vsp - FONTHEIGHT;  //offset for new line of text
      if (y<0) y += vsh;

      if ( (y += TFA) + 8 <= TOPOFBOTTOM) { //make sure we are not goint to overprint the bottom fixed area

        tft.setCursor(0, y); //set cursor position and print something.

        tft.setTextColor(colour);
        tft.print(millis());
        tft.setTextColor(QDTech_WHITE);


        tft.print(" y = ");
        tft.print(y);
        tft.print(" vsp=");
        tft.print(vsp);

      }
    }


    tft.vScroll(vsp + TFA);    //roll frame.

    //lets print something in the bottom fixed area

    tft.setCursor(45, TOPOFBOTTOM + 3);
    tft.setTextColor(QDTech_MAGENTA,QDTech_GREY);

    tft.print(vsp);
    tft.print("  ");
    
    delay(16);    // 

    vsp++; 

    if(vsp >= vsh) vsp-=vsh;

  }

  tft.exitScrollMode();   //return to normal mode - or would do if we ever got here

}    
void loop(){    

} 


