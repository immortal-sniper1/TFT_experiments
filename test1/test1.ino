#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;     // make iteration of the class and name it tft
//#include <Adafruit_TFTLCD.h>
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);



// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// functions

/*

  void drawStar( int16_t x, int16_t y, int16_t radious, int16_t inner_full_center, uint16_t points, uint16_t k, uint16_t colour)
  {
  // radious - distance from center to the star pointy tips
  // inner_full_center - distance from the center to the inner angles/corners of a star
  // x y - origin point of the star
  // points - number of points that a star has (min 3) , PS it is symetrical star
  // k - rotation offset
  int16_t i, angle;
  if ( points < 3)
  {
    points = 3;
  }
  i = 0;
  angle = 2 * PI / points;
  for ( i = 0; i < points; i++)
  {
    // draws a petal at a time
    tft.drawCircle( x, y, 20 , WHITE);
    tft.fillTriangle( x , y , x + radious * sin( i * angle  ) , y + radious * cos( i * angle  ) , x + inner_full_center * sin( i * angle + angle / 2 ) , y + inner_full_center * cos( i * angle + angle / 2  ) , colour);
    tft.fillTriangle( x , y , x + radious * sin( i * angle  ) , y + radious * cos( i * angle  ) , x + inner_full_center * sin( i * angle - angle / 2 ) , y + inner_full_center * cos( i * angle - angle / 2  ) , BLUE);
  }




  }

*/


void drawStar( int16_t x, int16_t y, int16_t radious, int16_t inner_full_center, uint16_t n, uint16_t k, uint16_t colour)
{
  // radious - distance from center to the star pointy tips
  // inner_full_center - distance from the center to the inner angles/corners of a star
  // x y - origin point of the star
  // n - number of points that a star has (min 3) , PS it is symetrical star
  // k - rotation offset
  int16_t i, j;
  if ( n < 3)
  {
    n = 3;
  }
  int16_t ext_point[n][2];
  int16_t int_point[n][2];


  float alfa = 2 * PI / n;

  // outer points coordonates
  for ( i = 0; i < n; i++)
  {
    ext_point[i][0] = x + radious * sin( i * alfa );
    ext_point[i][1] = y + radious * cos( i * alfa );
  }
    // inner points coordonates
  for ( i = 0; i < n; i++)
  {
    int_point[i][0] = x + inner_full_center * sin( i * alfa + alfa / 2);
    int_point[i][1] = y + inner_full_center * cos( i * alfa + alfa / 2);
  }

  tft.fillTriangle( x, y, ext_point[i][0], ext_point[i][1], int_point[j][0], int_point[j][1], colour);



}





//  +++ some functions from examples

/*
  void windowScroll(int16_t x, int16_t y, int16_t wid, int16_t ht, int16_t dx, int16_t dy, uint16_t *buf)
  {
  if (dx) for (int16_t row = 0; row < ht; row++) {
      READGRAM(x, y + row, buf, wid, 1);
      tft.setAddrWindow(x, y + row, x + wid - 1, y + row);
      tft.pushColors(buf + dx, wid - dx, 1);
      tft.pushColors(buf + 0, dx, 0);
    }
  if (dy) for (int16_t col = 0; col < wid; col++) {
      READGRAM(x + col, y, buf, 1, ht);
      tft.setAddrWindow(x + col, y, x + col, y + ht - 1);
      tft.pushColors(buf + dy, ht - dy, 1);
      tft.pushColors(buf + 0, dy, 0);
    }
  }


*/
void printmsg(int row, const char *msg)
{
  tft.setTextColor(YELLOW, BLACK);
  tft.setCursor(0, row);
  tft.println(msg);
}




//////////////////////////////////////////////////////////////////////
//main loops

void setup() {
  // put your setup code here, to run once:


  Serial.begin(9600);

  // +++some unknown stuff under
  uint32_t when = millis();
  //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
  if (!Serial) delay(5000);           //allow some time for Leonardo
  Serial.println("Serial took " + String((millis() - when)) + "ms to start");
  //    tft.reset();                 //hardware reset

  //-----------------------------------------
  uint16_t ID = tft.readID(); // +++read some ID ?
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield
  //    ID = 0x9329;                             // force ID
  tft.begin(ID);

}


// +++more unknown
#if defined(MCUFRIEND_KBV_H_)
uint16_t scrollbuf[320];    // my biggest screen is 320x480
#define READGRAM(x, y, buf, w, h)  tft.readGRAM(x, y, buf, w, h)   // +++ saw something abut some constructor like this in adafruit lib
#else
uint16_t scrollbuf[320];    // Adafruit only does 240x320
// Adafruit can read a block by one pixel at a time
int16_t  READGRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h)
{
  uint16_t *p;
  for (int row = 0; row < h; row++) {
    p = block + row * w;
    for (int col = 0; col < w; col++) {
      *p++ = tft.readPixel(x + col, y + row);
    }
  }
}
#endif



void loop() {
  // put your main code here, to run repeatedly:

  tft.setRotation(1);

  tft.fillScreen(RED);   // +++this function seems to set the background and when called again it purges the screen
  tft.setTextColor( 0xA186);
  printmsg( 20, "                 axa X" );
  printmsg( 60, "      axa Y" );
  tft.writeFillRect( 10, 10, 300, 10, GREEN);
  tft.writeFillRect( 10, 10, 10, 210, BLUE);
  delay(5000);


  delay(1500);
  drawStar( 100, 100, 100, 50, 3, 0, CYAN);
  delay(5000);

  printmsg( 115, "ppppppppppppppp" );
  tft.writeFillRect( 20, 20, 80, 120, CYAN);
  delay(5000);

  printmsg( 215, "ceva aici" );
  delay(5000);
  tft.writeFillRect( 50, 50, 100, 100, GREEN);
  printmsg( 127, "HUSARS" );
  printmsg( 124, "HUSARS" );
  printmsg( 110, "HUSARS" );
  printmsg( 120, "                     HUSARS" );
  delay(5000);

  tft.setTextSize(3);
  tft.fillCircle( 150, 200, 50 , WHITE);
  printmsg( 150, "full circle" );
  delay(5000);
  tft.setTextSize( 6, 6);
  tft.drawCircle( 50, 50, 50 , WHITE);

  printmsg( 10, "draw  Circle" );
  delay(5000);
  tft.fillTriangle( 50, 50, 180, 180, 50, 180, BLUE );
  tft.setCursor( 150, 150);
  delay(5000);
  tft.fillScreen(RED);




  delay(15000);
}








