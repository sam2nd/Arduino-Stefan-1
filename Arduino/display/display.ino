
// Grafiktest 1.8 Zoll TFT-Farb-Display (QDTech)

#define CS   10   
#define DC   9   
#define RST  8  

#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_QDTech.h> // modifizierte Adafruit-Bibliothek
#include <SPI.h>

Adafruit_QDTech tft = Adafruit_QDTech(CS, DC, RST);  // Display-Bibliothek Setup

void setup(void) {
  
  tft.init();   		// Display-Chip initialisieren
  
  tft.setRotation(0);	// Display steht laut Schaltplan auf dem Kopf, also anpassen
}

void loop() {

  
  // Bildschirm mit Farbe fuellen
  // fillScreen(farbe);
  tft.fillScreen(QDTech_BLACK);

  delay(2000); // 2 Sekunden warten
  
  // Fontgroesse setzen
  // setTextSize(groesse);
  tft.setTextSize(2);
  
  // Schrift umbrechen?
  // setTextWrap(true);   true=Ja, false=Nein
  tft.setTextWrap(true); 
  
  // Textposition setzen
  // setCursor(x,y);
  tft.setCursor(24,4);
 
  // Textfarbe setzen
  // setTextColor(farbe);
  tft.setTextColor(QDTech_WHITE);
  
  // Text ausgeben
  // print(text);
  tft.print("Hallo !");

  delay(2000); // 2 Sekunden warten
  
  // Linie zeichnen
  // drawLine(x_start,y_start,x_ende,y_ende,farbe);
  tft.drawLine(10,24,118,24,QDTech_GREEN);

  delay(2000); // 2 Sekunden warten
    
  // Ein Rechteck zeichnen 
  // drawRect(x_oben_links,y_oben_links,weite,hoehe,farbe);
  tft.drawRect(4,35,120,20,QDTech_RED); 
  
  delay(2000); // 2 Sekunden warten

  // Ein gefuelltes Rechteck zeichnen
  // drawRect(x_oben_links,y_oben_links,weite,hoehe,farbe);
  tft.fillRect(10,40,108,10,QDTech_YELLOW);

  delay(2000); // 2 Sekunden warten

  // Ein Rechteck mit abgerundeten Ecken zeichnen 
  // drawRoundRect(x_oben_links,y_oben_links,weite,hoehe,rundung,farbe);
  tft.drawRoundRect(4,65,120,20,5,QDTech_MAGENTA); 

  // Ein gefuelltes Rechteck mit abgerundeten Ecken zeichnen 
  // fillRoundRect(x_oben_links,y_oben_links,weite,hoehe,rundung,farbe);
  tft.fillRoundRect(10,70,108,10,5,QDTech_GREY);
  
  delay(2000);
  
  // Einen Kreis zeichnen 
  // drawCircle(x_oben_links,y_oben_links,radius,farbe);
  tft.drawCircle(64,115, 20, QDTech_CYAN);
  
  delay(2000); // 2 Sekunden warten
  
  // Einen gefuellten Kreis zeichnen 
  // fillCircle(x_oben_links,y_oben_links,radius,farbe);
  tft.fillCircle(64,115, 10, QDTech_BLUE);
  
  delay(2000); // 2 Sekunden warten

  // Neue Fontgroesse setzen
  // setTextSize(groesse);
  tft.setTextSize(1);
  
  // Neue Textfarbe setzen
  // setTextColor(farbe);
  tft.setTextColor(QDTech_GREEN);
  
  // Neue Textposition setzen
  // setCursor(x,y);
  tft.setCursor(14,147);
  
  // Text ausgeben
  // print(text);
  tft.print("blog.simtronyx.de");
  
  delay(8000); // 8 Sekunden warten
  
  // Gesamtes Display invertieren?
  // invertDisplay(true);   true=Ja, false=Nein
  tft.invertDisplay(true);
  
  delay(1000); // 1 Sekunde warten
  
  // Gesamtes Display invertieren?
  // invertDisplay(false);   true=Ja, false=Nein
  tft.invertDisplay(false);

  delay(1000); // 1 Sekunde warten
}



