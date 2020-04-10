
#ifdef ANDREAS

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

int ledPin = 2;

#define TFT_BL 17
#define XPT2046_CS 33

TFT_eSPI tft = TFT_eSPI();

XPT2046_Touchscreen ts(XPT2046_CS); // Chip Select pin


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  //Serial.begin(38400);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  ts.begin();
  ts.setRotation(1);
  //while (!Serial && (millis() <= 1000));
}

boolean wastouched = true;

void loop() {
  boolean istouched = ts.touched();
  if (istouched) {
    TS_Point p = ts.getPoint();
    if (!wastouched) {
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_YELLOW);
      tft.setCursor(60, 80);
      tft.print("Touch");
    }
    tft.fillRect(100, 150, 140, 60, TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(100, 150);
    tft.print("X = ");
    tft.print(p.x);
    tft.setCursor(100, 180);
    tft.print("Y = ");
    tft.print(p.y);
    /*
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.println(p.y);
    */
  } else {
    if (wastouched) {
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_RED);
      tft.setCursor(120, 50);
      tft.print("No");
      tft.setCursor(80, 120);
      tft.print("Touch");
    }
    //Serial.println("no touch");
  }
  wastouched = istouched;
  delay(100);
}

#endif