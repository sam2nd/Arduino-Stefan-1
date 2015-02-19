#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_QDTech.h> // Hardware-specific library
#include <SPI.h>
#include <Wire.h> // I2C für Uhr

//LCD DISPLAY PORTS:
#define sclk 13  // Don't change
#define mosi 11  // Don't change
#define cs   10
#define dc   9
#define rst  8  // you can also connect this to the Arduino reset

//initiate DISPLAY
Adafruit_QDTech tft = Adafruit_QDTech(cs, dc, rst);  // Invoke custom library
//Start Tempsensor an D3
OneWire  ds(3);
//the I2C address of Tiny RTC
#define DS1307_I2C_ADDRESS 0x68  
//DeviceAdressen der einzelnen ds1820 Temperatursensoren angeben. (loop anpassen)
DeviceAddress sensor1 = {0x10, 0xC8, 0x85, 0xDB, 0x02, 0x08, 0x00, 0x70};
//DeviceAddress sensor2 = { 0x10, 0x16, 0x2E, 0x57, 0x2, 0x8, 0x0, 0x2F };
//DeviceAddress sensor3 = { 0x10, 0x11, 0x40, 0xC0, 0x1, 0x8, 0x0, 0x9A };
//DeviceAddress sensor4 = { 0x10, 0x77, 0x38, 0x57, 0x2, 0x8, 0x0, 0x3B };
 
char sensor1Name[] = "Wohnzimmer: ";
//char sensor2Name[] = "Wohnzimmer: ";
//char sensor3Name[] = "Heizkeller: ";
//char sensor4Name[] = "Aquarium: ";

//Time  
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
 return ( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
 return ( (val/16*10) + (val%16) );
}

//Temperature
float max_T=0;
float min_T=0;
int i = 0;

void setup(void) 
{
  Wire.begin();
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);	// 0 - Portrait, 1 - Lanscape
  tft.fillScreen(QDTech_BLACK);
  tft.setTextWrap(true);
}
// Function to gets the date and time from the ds1307 and prints result

void getDateDs1307()
{
 // Reset the register pointer
 Wire.beginTransmission(DS1307_I2C_ADDRESS);
 Wire.write(decToBcd(0));
 Wire.endTransmission();
 Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
 second     = bcdToDec(Wire.read() & 0x7f);
 minute     = bcdToDec(Wire.read());
 hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
 dayOfWeek  = bcdToDec(Wire.read());
 dayOfMonth = bcdToDec(Wire.read());
 month      = bcdToDec(Wire.read());
 year       = bcdToDec(Wire.read());  
 Serial.print(hour, DEC);
 Serial.print(":");
 Serial.print(minute, DEC);
 Serial.print(":");
 Serial.print(second, DEC);
 Serial.print("  ");
 Serial.print(month, DEC);
 Serial.print("/");
 Serial.print(dayOfMonth, DEC);
 Serial.print("/");
 Serial.print(year,DEC);
 Serial.print("  ");
 Serial.println();
 //Serial.print("Day of week:");
} 
void min_max(float temp, int a)
{
 
 Serial.print(temp);
 Serial.println(a);
  if (a==1){
    Serial.print("EVENT");
   min_T=temp;
   max_T=temp;
         }
 else {
    if (temp >= max_T){
    max_T = temp;}
    if (temp < min_T){
    min_T = temp;}
    else {
    ;
    }
    
 tft.setCursor(2,80);
 tft.setTextSize (2);
 tft.fillRect (0, 78, 160, 20, QDTech_RED);
 
 tft.print("MAX: ");
 tft.print(max_T);
 tft.print(" C");
 tft.setCursor(2,100);
 tft.setTextSize (2);
 tft.fillRect (0, 98, 160, 20, QDTech_BLUE);
 tft.print("MIN: ");

 //tft.fillRect (0, 0, 160, 128, QDTech_RED);
 tft.print(min_T);
 tft.print(" C"); 
}
}
    
    
void writeTimeToScratchpad(byte* address)
{
  //reset the bus
  ds.reset();
  //select our sensor
  ds.select(address);
  //CONVERT T function call (44h) which puts the temperature into the scratchpad
  ds.write(0x44,1);
  //sleep a second for the write to take place
  delay(1000);
}
 
void readTimeFromScratchpad(byte* address, byte* data)
{
  //reset the bus
  ds.reset();
  //select our sensor
  ds.select(address);
  //read the scratchpad (BEh)
  ds.write(0xBE);
  for (byte i=0;i<9;i++){
    data[i] = ds.read();
  }
}
 
float getTemperature(byte* address)
{
  int tr;
  byte data[12];
 
  writeTimeToScratchpad(address);
 
  readTimeFromScratchpad(address,data);
 
  //put in temp all the 8 bits of LSB (least significant byte)
  tr = data[0];
 
  //check for negative temperature
  if (data[1] > 0x80)
  {
    tr = !tr + 1; //two's complement adjustment
    tr = tr * -1; //flip value negative.
  }
 
  //COUNT PER Celsius degree (10h)
  int cpc = data[7];
  //COUNT REMAIN (0Ch)
  int cr = data[6];
 
  //drop bit 0
  tr = tr >> 1;
 
  return tr - (float)0.25 + (cpc - cr)/(float)cpc;
}
 
void loop(void) 
{
i=i+1;

float temp1 = getTemperature(sensor1);
//  float temp2 = getTemperature(sensor2);
//  float temp3 = getTemperature(sensor3);
//  float temp4 = getTemperature(sensor4);

  Serial.print(i);
  Serial.print(sensor1Name);
  Serial.print(temp1);
  Serial.println(" Celsius");
  
  getDateDs1307();
 //TFT-Ausgabe 
  tft.setCursor(2,0);
  tft.setTextSize(1);
  tft.setTextColor(QDTech_WHITE);
  //tft.print(sensor1Name);
  tft.fillRect (0, 0, 160, 10, QDTech_BLACK);
  tft.print(hour, DEC);
  tft.print(":");
  tft.print(minute, DEC);
  tft.print(":");
  tft.print(second, DEC);
  tft.setTextColor(QDTech_WHITE);
  tft.setCursor(7,25);
  tft.setTextSize (5);
 
  tft.fillRect (0, 25, 160, 40, QDTech_BLACK);
  tft.print(temp1);
  //tft.println(" Celsius");
  min_max(temp1,i);
  
  delay(1000);
// }
//   
//   else { 
//  tft.setCursor(2,60);
//  tft.setTextSize (2);
//  tft.fillRect (0, 0, 160, 128, QDTech_BLUE);
//  tft.print(temp1);
//  tft.println(" Celsius");
//  delay(1000);
//}
  //tft.fillScreen(QDTech_BLACK);

   
//  Serial.print(sensor2Name);
//  Serial.print(temp2);
//  Serial.println(" Celsius");
// 
//  Serial.print(sensor3Name);
//  Serial.print(temp3);
//  Serial.println(" Celsius");
// 
//  Serial.print(sensor4Name);
//  Serial.print(temp4);
//  Serial.println(" Celsius");
// 
//  Serial.println();

}