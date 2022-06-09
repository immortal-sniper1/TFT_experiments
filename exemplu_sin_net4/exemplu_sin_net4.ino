// source  https://create.arduino.cc/projecthub/MisterBotBreak/how-to-create-a-data-displaying-system-with-a-tft-screen-2-7dfca7


#include "TouchScreen.h"
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define WHITE    0xFFFF
#define DARKCYAN 0x03EF
#define GRAY     0x8410
#define ORANGE   0xFA60
#define YELLOW   0xFFE0
#define LIME     0x07FF
#define AQUA     0x04FF
#define MAGENTA  0xF81F

#define YP A2
#define XM A3
#define YM 8
#define XP 9

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 400);
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int a = 0;
int y;
int pin = 0;
int x = 30;
int xa = 1;
int xb = 1;
int returntograph = 0;
int yinfos = 0;
int varyinfo = 0;
int scale = 0;
int scale2 = 5;
int scale3 = 10;
int xb1 = 20;
int xb2 = 175;

int settingsbuttons1 = 0;
int settingsbuttons2 = 0;
int settingsbuttons3 = 0;
int settingsbuttons4 = 0;

int redgreen1 = 0;
int redgreen2 = 0;
int redgreen3 = 0;
int redgreen4 = 0;


void setup() {
  tft.reset();
  tft.begin(0x9341);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  tft.setCursor(30, 110);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.println("Data Monitoring System");
  delay(1000);


  tft.fillScreen(BLACK);

  tft.drawRoundRect(100, 25, 120, 40, 4, WHITE);
  tft.drawRoundRect(100, 75, 120, 40, 4, WHITE);
  tft.drawRoundRect(100, 125, 120, 40, 4, WHITE);
  tft.drawRoundRect(100, 175, 120, 40, 4, WHITE);
  tft.drawRoundRect(230, 25, 80, 190, 4, WHITE);

  tft.setCursor(146, 38);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.println("A10");
  tft.setCursor(146, 88);
  tft.setTextColor(YELLOW);
  tft.println("A11");
  tft.setCursor(146, 138);
  tft.setTextColor(GREEN);
  tft.println("A12");
  tft.setCursor(146, 188);
  tft.setTextColor(BLUE);
  tft.println("A13");
  tft.setCursor(253, 98);
  tft.setTextColor(ORANGE);
  tft.println("ALL");
  tft.setCursor(247, 118);
  tft.println("PINS");

  tft.setCursor(5, 104);
  tft.setTextColor(GRAY);
  tft.setTextSize(1);
  tft.println("Charts are less");
  tft.setCursor(5, 114);
  tft.println("detailed if all");
  tft.setCursor(5, 124);
  tft.println("pins values are");
  tft.setCursor(5, 134);
  tft.println("screened.");
  tft.setCursor(5, 94);
  tft.println("NOTE :");
}


void resetgraph() {
  tft.fillRect(25, 10, 290, 196, BLACK);

  tft.drawLine(30, 10, 30, 200, WHITE);
  tft.drawLine(30, 200, 300, 200, WHITE);

  tft.drawLine(25, 10, 30, 10, WHITE);
  tft.drawLine(25, 105, 30, 105, WHITE);
  tft.drawLine(30, 200, 25, 205, WHITE);

  tft.drawLine(45, 200, 45, 205, WHITE);
  tft.drawLine(60, 200, 60, 205, WHITE);
  tft.drawLine(75, 200, 75, 205, WHITE);
  tft.drawLine(90, 200, 90, 205, WHITE);
  tft.drawLine(105, 200, 105, 205, WHITE);
  tft.drawLine(120, 200, 120, 205, WHITE);
  tft.drawLine(135, 200, 135, 205, WHITE);
  tft.drawLine(150, 200, 150, 205, WHITE);
  tft.drawLine(165, 200, 165, 205, WHITE);
  tft.drawLine(180, 200, 180, 205, WHITE);
  tft.drawLine(195, 200, 195, 205, WHITE);
  tft.drawLine(210, 200, 210, 205, WHITE);
  tft.drawLine(225, 200, 225, 205, WHITE);
  tft.drawLine(240, 200, 240, 205, WHITE);
  tft.drawLine(255, 200, 255, 205, WHITE);
  tft.drawLine(270, 200, 270, 205, WHITE);
  tft.drawLine(285, 200, 285, 205, WHITE);
  tft.drawLine(300, 200, 300, 205, WHITE);

}


void graph() {
  tft.fillScreen(BLACK);
  tft.drawLine(30, 10, 30, 200, WHITE);
  tft.drawLine(30, 200, 300, 200, WHITE);

  tft.drawLine(25, 10, 30, 10, WHITE);
  tft.drawLine(25, 105, 30, 105, WHITE);
  tft.drawLine(30, 200, 25, 205, WHITE);

  tft.setCursor(1, 6);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.println("1024");
  tft.setCursor(1, 102);
  tft.println("512");
  tft.setCursor(14, 206);
  tft.println("0");
  tft.setCursor(103, 207);
  tft.println("5");
  tft.setCursor(175, 207);
  tft.println("10");

  tft.setCursor(182, 220);
  tft.setTextColor(GRAY);
  tft.setTextSize(1);
  tft.println("PRESS (don't simply");
  tft.setCursor(182, 230);
  tft.println("click) the button");

  tft.drawLine(45, 200, 45, 205, WHITE);
  tft.drawLine(60, 200, 60, 205, WHITE);
  tft.drawLine(75, 200, 75, 205, WHITE);
  tft.drawLine(90, 200, 90, 205, WHITE);
  tft.drawLine(105, 200, 105, 205, WHITE);
  tft.drawLine(120, 200, 120, 205, WHITE);
  tft.drawLine(135, 200, 135, 205, WHITE);
  tft.drawLine(150, 200, 150, 205, WHITE);
  tft.drawLine(165, 200, 165, 205, WHITE);
  tft.drawLine(180, 200, 180, 205, WHITE);
  tft.drawLine(195, 200, 195, 205, WHITE);
  tft.drawLine(210, 200, 210, 205, WHITE);
  tft.drawLine(225, 200, 225, 205, WHITE);
  tft.drawLine(240, 200, 240, 205, WHITE);
  tft.drawLine(255, 200, 255, 205, WHITE);
  tft.drawLine(270, 200, 270, 205, WHITE);
  tft.drawLine(285, 200, 285, 205, WHITE);
  tft.drawLine(300, 200, 300, 205, WHITE);

  tft.setCursor(240, 207);
  tft.setTextColor(WHITE);
  tft.println("(in seconds)");

  tft.drawRoundRect(75, 216, 100, 24, 4, WHITE);
  tft.setCursor(100, 223);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.println("Settings");
}

void graph2() {
  tft.fillScreen(BLACK);
  tft.drawLine(20, 105, 145, 105, WHITE);
  tft.drawLine(20, 10, 20, 105, WHITE);
  tft.drawLine(175, 105, 300, 105, WHITE);
  tft.drawLine(175, 10, 175, 105, WHITE);

  tft.drawLine(20, 220, 145, 220, WHITE);
  tft.drawLine(20, 125, 20, 220, WHITE);
  tft.drawLine(175, 220, 300, 220, WHITE);
  tft.drawLine(175, 125, 175, 220, WHITE);


  tft.drawLine(20, 10, 15, 10, WHITE);
  tft.drawLine(20, 105, 15, 105, WHITE);
  tft.drawLine(170, 10, 175, 10, WHITE);
  tft.drawLine(170, 105, 175, 105, WHITE);

  tft.drawLine(20, 125, 15, 125, WHITE);
  tft.drawLine(20, 220, 15, 220, WHITE);
  tft.drawLine(170, 125, 175, 125, WHITE);
  tft.drawLine(170, 220, 175, 220, WHITE);

  tft.drawLine(20, 57, 15, 57, WHITE);
  tft.drawLine(170, 57, 175, 57, WHITE);
  tft.drawLine(20, 172, 15, 172, WHITE);
  tft.drawLine(170, 172, 175, 172, WHITE);

}


void settings() {
  tft.fillScreen(BLACK);
  tft.drawRoundRect(20, 20, 30, 30, 4, WHITE);
  tft.drawRoundRect(20, 60, 30, 30, 4, WHITE);
  tft.drawRoundRect(20, 100, 30, 30, 4, WHITE);
  tft.drawRoundRect(20, 140, 30, 30, 4, WHITE);

  tft.fillRoundRect(21, 21, 28, 28, 4, RED);
  tft.fillRoundRect(21, 61, 28, 28, 4, RED);
  tft.fillRoundRect(21, 101, 28, 28, 4, RED);
  tft.fillRoundRect(21, 141, 28, 28, 4, RED);

  tft.setCursor(60, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.println("Display analog values (between 0 and 1024)");
  tft.setCursor(60, 70);
  tft.println("Display a percentage");
  tft.setCursor(60, 110);
  tft.println("Display a voltage (between 0V and 5V)");
  tft.setCursor(60, 150);
  tft.println("Display a growth between (in percent)");

  tft.drawRoundRect(20, 192, 130, 36, 4, WHITE);
  tft.setTextSize(1);
  tft.setCursor(32, 206);
  tft.println("Back to the graph");
}



void loop() {


  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > ts.pressureThreshhold) {


    if (p.x > 350 && p.x < 700 && p.y < 350 && a == 0) {
      graph();
      a = 1;
      pin = 1;
      returntograph = 1;
    }
    else if (p.x > 350 && p.x < 700 && p.y < 525 && p.y > 350 && a == 0) {
      graph();
      a = 1;
      pin = 2;
      returntograph = 1;

    }
    else if (p.x > 350 && p.x < 700 && p.y > 525 && p.y < 700 && a == 0) {
      graph();
      a = 1;
      pin = 3;
      returntograph = 1;

    }
    else if (p.x > 350 && p.x < 700 && p.y > 700 && a == 0) {
      graph();
      a = 1;
      pin = 4;
      returntograph = 1;

    }
    else if (p.x > 700 && a == 0) {
      graph2();
      a = 3;
    }

    if (p.y > 830 && a == 1 && returntograph == 1) {
      settings();
      a = 2;
      p.y = 0;
      returntograph = 0;
    }


    if (p.y < 300 && a == 2 && returntograph == 0 && redgreen1 == 1) {
      tft.fillRoundRect(21, 21, 28, 28, 4, RED);
      settingsbuttons1 = 0;
      redgreen1 = 0;
      delay(100);
    }
    else if (p.y < 300 && a == 2 && returntograph == 0 && redgreen1 == 0) {
      tft.fillRoundRect(21, 21, 28, 28, 4, GREEN);
      settingsbuttons1 = 1;
      redgreen1 = 1;
      delay(100);
    }

    if (p.y < 430 && p.y > 300 && a == 2 && returntograph == 0 && redgreen2 == 1) {
      tft.fillRoundRect(21, 61, 28, 28, 4, RED);
      settingsbuttons2 = 0;
      redgreen2 = 0;
      delay(100);
    }
    else if (p.y < 430 && p.y > 300 && a == 2 && returntograph == 0 && redgreen2 == 0) {
      tft.fillRoundRect(21, 61, 28, 28, 4, GREEN);
      settingsbuttons2 = 1;
      redgreen2 = 1;
      delay(100);
    }

    if (p.y < 570 && p.y > 430 && a == 2 && returntograph == 0 && redgreen3 == 1) {
      tft.fillRoundRect(21, 101, 28, 28, 4, RED);
      settingsbuttons3 = 0;
      redgreen3 = 0;
      delay(100);
    }
    else if (p.y < 570 && p.y > 430 && a == 2 && returntograph == 0 && redgreen3 == 0) {
      tft.fillRoundRect(21, 101, 28, 28, 4, GREEN);
      settingsbuttons3 = 1;
      redgreen3 = 1;
      delay(100);
    }

    if (p.y < 730 && p.y > 570 && a == 2 && returntograph == 0 && redgreen4 == 1) {
      tft.fillRoundRect(21, 141, 28, 28, 4, RED);
      settingsbuttons4 = 0;
      redgreen4 = 0;
      delay(100);
    }
    else if (p.y < 730 && p.y > 570 && a == 2 && returntograph == 0 && redgreen4 == 0) {
      tft.fillRoundRect(21, 141, 28, 28, 4, GREEN);
      settingsbuttons4 = 1;
      redgreen4 = 1;
      delay(100);
    }


    if (p.x < 530 && p.y > 750 && a == 2 && returntograph == 0) {
      graph();
      a = 1;
      returntograph = 1;
    }
    delay(20);
  }


  if (p.z < ts.pressureThreshhold && pin == 1 && a == 1 && returntograph == 1) {
    int yplus = map(y, 0, 1024, 0, 100);
    int oldy = map(y, 0, 1024, 200, 10);
    int oldx = x;

    y = analogRead(A10);

    int percentage = map(y, 0, 1024, 0, 100);
    int ypixel = map(y, 0, 1024, 200, 10);

    xa++;
    x = xa * 15;

    if (oldx - x >= 100) {
      goto skipA0;
    }
    tft.drawLine(x, ypixel, oldx, oldy, RED);
skipA0 :
    tft.fillCircle(x, ypixel, 3, RED);
    if (x <= 45) {
      goto skipA1;
    }

    tft.fillRect(oldx - 7, oldy - 61, 20, 38, BLACK);
    tft.fillRect(oldx - 12, oldy - 61, 20, 10, BLACK);

    tft.drawLine(x, ypixel, oldx, oldy, RED);

skipA1 :
    if (x <= 45) {
      goto skipA2;
    }



    if (settingsbuttons4 == 1) {
      if (redgreen4 == 1) {
        int growth = percentage - yplus;

        tft.setCursor(x + 1, ypixel - 59);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        if (growth < 0) {
          tft.setCursor(x - 5, ypixel - 59);
        }
        if (growth < -9) {
          tft.setCursor(x - 12, ypixel - 59);
        }
        if (growth > 9) {
          tft.setCursor(x - 7, ypixel - 59);
        }
        else {
        }
        tft.println(growth);
        if (growth >= 0) {
          tft.setCursor(x - 5, ypixel - 59);
          if (growth > 9) {
            tft.setCursor(x - 12, ypixel - 59);
          }
          tft.println("+");
        }
        tft.setCursor(x + 7, ypixel - 59);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons1 == 1) {
      if (redgreen1 == 1) {
        tft.setCursor(x - 5, ypixel - 31);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(y);
      }
      else {
      }
    }



    if (settingsbuttons2 == 1) {
      if (redgreen2 == 1) {
        tft.setCursor(x - 5, ypixel - 41);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(percentage);
        tft.setCursor(x + 8, ypixel - 40);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons3 == 1) {
      if (redgreen3 == 1) {
        int voltage = map(y, 0, 1024, 0, 5);
        tft.setCursor(x - 1, ypixel - 50);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(voltage);
        tft.setCursor(x + 6, ypixel - 50);
        tft.println("V");
      }
      else {
      }
    }



skipA2 :
    delay(500);

    if (x == 300) {
      xa = 1;
      resetgraph();
      tft.fillRect(5, 206, 310, 8, BLACK);
      scale = scale + 18;
      scale2 = scale2 + 18;
      scale3 = scale3 + 18;
      tft.setCursor(14, 207);
      tft.println(scale);
      tft.setCursor(100, 207);
      tft.println(scale2);
      tft.setCursor(176, 207);
      tft.println(scale3);
    }
  }


  if (p.z < ts.pressureThreshhold && pin == 2 && a == 1 && returntograph == 1) {
    int yplus = map(y, 0, 1024, 0, 100);
    int oldy = map(y, 0, 1024, 200, 10);
    int oldx = x;

    y = analogRead(A11);

    int percentage = map(y, 0, 1024, 0, 100);
    int ypixel = map(y, 0, 1028, 200, 10);

    xa++;
    x = xa * 15;

    if (oldx - x >= 100) {
      goto skipB0;
    }
    tft.drawLine(x, ypixel, oldx, oldy, YELLOW);
skipB0 :
    tft.fillCircle(x, ypixel, 3, YELLOW);
    if (x <= 45) {
      goto skipB1;
    }

    tft.fillRect(oldx - 7, oldy - 61, 20, 38, BLACK);
    tft.fillRect(oldx - 12, oldy - 61, 20, 10, BLACK);

    tft.drawLine(x, ypixel, oldx, oldy, YELLOW);

skipB1 :
    if (x <= 45) {
      goto skipB2;
    }



    if (settingsbuttons4 == 1) {
      if (redgreen4 == 1) {
        int growth = percentage - yplus;

        tft.setCursor(x + 1, ypixel - 59);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        if (growth < 0) {
          tft.setCursor(x - 5, ypixel - 59);
        }
        if (growth < -9) {
          tft.setCursor(x - 12, ypixel - 59);
        }
        if (growth > 9) {
          tft.setCursor(x - 7, ypixel - 59);
        }
        else {
        }
        tft.println(growth);
        if (growth >= 0) {
          tft.setCursor(x - 5, ypixel - 59);
          if (growth > 9) {
            tft.setCursor(x - 12, ypixel - 59);
          }
          tft.println("+");
        }
        tft.setCursor(x + 7, ypixel - 59);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons1 == 1) {
      if (redgreen1 == 1) {
        tft.setCursor(x - 5, ypixel - 31);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(y);
      }
      else {
      }
    }



    if (settingsbuttons2 == 1) {
      if (redgreen2 == 1) {
        tft.setCursor(x - 5, ypixel - 41);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(percentage);
        tft.setCursor(x + 8, ypixel - 40);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons3 == 1) {
      if (redgreen3 == 1) {
        int voltage = map(y, 0, 1024, 0, 5);
        tft.setCursor(x - 1, ypixel - 50);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(voltage);
        tft.setCursor(x + 6, ypixel - 50);
        tft.println("V");
      }
      else {
      }
    }



skipB2 :
    delay(500);

    if (x == 300) {
      xa = 1;
      resetgraph();
      tft.fillRect(5, 206, 310, 8, BLACK);
      scale = scale + 18;
      scale2 = scale2 + 18;
      scale3 = scale3 + 18;
      tft.setCursor(14, 207);
      tft.println(scale);
      tft.setCursor(100, 207);
      tft.println(scale2);
      tft.setCursor(176, 207);
      tft.println(scale3);
    }
  }


  if (p.z < ts.pressureThreshhold && pin == 3 && a == 1 && returntograph == 1) {
    int yplus = map(y, 0, 1024, 0, 100);
    int oldy = map(y, 0, 1024, 200, 10);
    int oldx = x;

    y = analogRead(A12);

    int percentage = map(y, 0, 1024, 0, 100);
    int ypixel = map(y, 0, 1028, 200, 10);

    xa++;
    x = xa * 15;

    if (oldx - x >= 100) {
      goto skipC0;
    }
    tft.drawLine(x, ypixel, oldx, oldy, GREEN);
skipC0 :
    tft.fillCircle(x, ypixel, 3, GREEN);
    if (x <= 45) {
      goto skipC1;
    }

    tft.fillRect(oldx - 7, oldy - 61, 20, 38, BLACK);
    tft.fillRect(oldx - 12, oldy - 61, 20, 10, BLACK);

    tft.drawLine(x, ypixel, oldx, oldy, GREEN);

skipC1 :
    if (x <= 45) {
      goto skipC2;
    }



    if (settingsbuttons4 == 1) {
      if (redgreen4 == 1) {
        int growth = percentage - yplus;

        tft.setCursor(x + 1, ypixel - 59);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        if (growth < 0) {
          tft.setCursor(x - 5, ypixel - 59);
        }
        if (growth < -9) {
          tft.setCursor(x - 12, ypixel - 59);
        }
        if (growth > 9) {
          tft.setCursor(x - 7, ypixel - 59);
        }
        else {
        }
        tft.println(growth);
        if (growth >= 0) {
          tft.setCursor(x - 5, ypixel - 59);
          if (growth > 9) {
            tft.setCursor(x - 12, ypixel - 59);
          }
          tft.println("+");
        }
        tft.setCursor(x + 7, ypixel - 59);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons1 == 1) {
      if (redgreen1 == 1) {
        tft.setCursor(x - 5, ypixel - 31);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(y);
      }
      else {
      }
    }



    if (settingsbuttons2 == 1) {
      if (redgreen2 == 1) {
        tft.setCursor(x - 5, ypixel - 41);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(percentage);
        tft.setCursor(x + 8, ypixel - 40);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons3 == 1) {
      if (redgreen3 == 1) {
        int voltage = map(y, 0, 1024, 0, 5);
        tft.setCursor(x - 1, ypixel - 50);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(voltage);
        tft.setCursor(x + 6, ypixel - 50);
        tft.println("V");
      }
      else {
      }
    }



skipC2 :
    delay(500);

    if (x == 300) {
      xa = 1;
      resetgraph();
      tft.fillRect(5, 206, 310, 8, BLACK);
      scale = scale + 18;
      scale2 = scale2 + 18;
      scale3 = scale3 + 18;
      tft.setCursor(14, 207);
      tft.println(scale);
      tft.setCursor(100, 207);
      tft.println(scale2);
      tft.setCursor(176, 207);
      tft.println(scale3);
    }
  }



  if (p.z < ts.pressureThreshhold && pin == 4 && a == 1 && returntograph == 1) {
    int yplus = map(y, 0, 1024, 0, 100);
    int oldy = map(y, 0, 1024, 200, 10);
    int oldx = x;

    y = analogRead(A13);

    int percentage = map(y, 0, 1024, 0, 100);
    int ypixel = map(y, 0, 1028, 200, 10);

    xa++;
    x = xa * 15;

    if (oldx - x >= 100) {
      goto skipD0;
    }
    tft.drawLine(x, ypixel, oldx, oldy, BLUE);
skipD0 :
    tft.fillCircle(x, ypixel, 3, BLUE);
    if (x <= 45) {
      goto skipD1;
    }

    tft.fillRect(oldx - 7, oldy - 61, 20, 38, BLACK);
    tft.fillRect(oldx - 12, oldy - 61, 20, 10, BLACK);

    tft.drawLine(x, ypixel, oldx, oldy, BLUE);

skipD1 :
    if (x <= 45) {
      goto skipD2;
    }



    if (settingsbuttons4 == 1) {
      if (redgreen4 == 1) {
        int growth = percentage - yplus;

        tft.setCursor(x + 1, ypixel - 59);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        if (growth < 0) {
          tft.setCursor(x - 5, ypixel - 59);
        }
        if (growth < -9) {
          tft.setCursor(x - 12, ypixel - 59);
        }
        if (growth > 9) {
          tft.setCursor(x - 7, ypixel - 59);
        }
        else {
        }
        tft.println(growth);
        if (growth >= 0) {
          tft.setCursor(x - 5, ypixel - 59);
          if (growth > 9) {
            tft.setCursor(x - 12, ypixel - 59);
          }
          tft.println("+");
        }
        tft.setCursor(x + 7, ypixel - 59);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons1 == 1) {
      if (redgreen1 == 1) {
        tft.setCursor(x - 5, ypixel - 31);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(y);
      }
      else {
      }
    }



    if (settingsbuttons2 == 1) {
      if (redgreen2 == 1) {
        tft.setCursor(x - 5, ypixel - 41);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(percentage);
        tft.setCursor(x + 8, ypixel - 40);
        tft.println("%");
      }
      else {
      }
    }



    if (settingsbuttons3 == 1) {
      if (redgreen3 == 1) {
        int voltage = map(y, 0, 1024, 0, 5);
        tft.setCursor(x - 1, ypixel - 50);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.println(voltage);
        tft.setCursor(x + 6, ypixel - 50);
        tft.println("V");
      }
      else {
      }
    }



skipD2 :
    delay(500);

    if (x == 300) {
      xa = 1;
      resetgraph();
      tft.fillRect(5, 206, 310, 8, BLACK);
      scale = scale + 18;
      scale2 = scale2 + 18;
      scale3 = scale3 + 18;
      tft.setCursor(14, 207);
      tft.println(scale);
      tft.setCursor(100, 207);
      tft.println(scale2);
      tft.setCursor(176, 207);
      tft.println(scale3);
    }
  }

  if (p.z < ts.pressureThreshhold && a == 3) {

    int a10 = analogRead(A10);
    int a11 = analogRead(A11);
    int a12 = analogRead(A12);
    int a13 = analogRead(A13);

    int adapted1 = map(a10, 0, 1024, 103, 10);
    int adapted2 = map(a11, 0, 1024, 103, 10);
    int adapted3 = map(a12, 0, 1024, 218, 125);
    int adapted4 = map(a13, 0, 1024, 218, 125);

    xb1 = xb1 + 10;
    xb2 = xb2 + 10;

    tft.fillCircle(xb1, adapted1, 1, RED);
    tft.fillCircle(xb2, adapted2, 1, YELLOW);
    tft.fillCircle(xb1, adapted3, 1, GREEN);
    tft.fillCircle(xb2, adapted4, 1, BLUE);

    delay(500);

    if (xb1 == 140 || xb2 == 295) {
      xb1 = 20;
      xb2 = 175;
      tft.fillRect(21, 10, 125, 95, BLACK);
      tft.fillRect(176, 10, 126, 95, BLACK);
      tft.fillRect(21, 125, 126, 95, BLACK);
      tft.fillRect(176, 125, 125, 95, BLACK);

    }
  }
}

