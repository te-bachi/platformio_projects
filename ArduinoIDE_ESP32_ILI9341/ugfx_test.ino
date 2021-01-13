#include <gfx.h>

void setup() {
  coord_t		width, height;
  coord_t		i, j;

  Serial.begin(115200);
  
  // Initialize and clear the display
  gfxInit();

  // Get the screen size
  width = gdispGetWidth();
  height = gdispGetHeight();

  // Draw something
  gdispDrawBox(10, 10, width / 2, height / 2, Yellow);
  gdispFillArea(width / 2, height / 2, width / 2 - 10, height / 2 - 10, Blue);
  gdispDrawLine(5, 30, width - 50, height - 40, Red);
  gdispDrawBox(10, 10, width / 2, height /2, Yellow);
 
  for (i = 5, j = 0; i < width && j < height; i += 7, j += i / 20)
    gdispDrawPixel(i, j, White);
}

void loop() {
  delay(1000);
}

