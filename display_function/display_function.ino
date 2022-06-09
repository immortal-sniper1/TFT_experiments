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





void Graph(Adafruit_GFX &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw)
{

  /*
    function to draw a cartesian coordinate system and plot whatever data you want
    just pass x and y and the graph will be drawn
    huge arguement list
    &d name of your display object
    x = x data point
    y = y datapont
    gx = x graph location (lower left)
    gy = y graph location (lower left)
    w = width of graph
    h = height of graph
    xlo = lower bound of x axis
    xhi = upper bound of x asis
    xinc = division of x axis (distance not count)
    ylo = lower bound of y axis
    yhi = upper bound of y asis
    yinc = division of y axis (distance not count)
    title = title of graph
    xlabel = x asis label
    ylabel = y asis label
    gcolor = graph line colors
    acolor = axi ine colors
    pcolor = color of your plotted data
    tcolor = text color
    bcolor = background color
    &redraw = flag to redraw graph on fist call only
  */
  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;


  if (redraw == true)
  {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc)
    {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0)
      {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else
      {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc)
    {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0)
      {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else
      {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }

    //now draw the labels
    d.setTextSize(2);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}

/*
  End of graphing functioin
*/









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
  tft.fillScreen(BLACK);   // +++this function seems to set the background and when called again it purges the screen


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
  int  i, n, x;
  bool u = true;
  double ox, oy;
  float vall;
  for ( i = 0; i < 500; i++)
  {
    vall = sin(i / 360 * 2 * PI);
    Serial.print("x=");
    Serial.print(i);
    Serial.print(" degrees       ");
    Serial.print("sin=");
    Serial.println(vall);

    Graph( tft , i, vall, 50, 50, 200, 200, 0,
           5, 1, -1.5, 1.5, 0.2, "sinul", "X",
           "Y", CYAN, CYAN, CYAN,
           RED, WHITE, u);
  }



}




