Installation Instructions µGFX V2.8 Arduino IDE
===============================================

1) Copy the gfx directory from the zip archive to your Arduino library directory <Documents>/Arduino/libraries/gfx

2) Create a subdirectory under "gfx" called "ugfx" and copy the entire µgfx system to that directory.

3) In your Arduino sketch directory, create a new subfolder "ugfx_test" and copy ugfx_test.ino to it.

4) Open <Documents>/Arduino/libraries/gfx/board_ILI9341.h and adjust the pin settings as you need. The board file uses hardware SPI by default. If you don't know the pins, just Serial.println(MOSI) and Serial.println(SCK).

5) Optional: If you want to use more than one ILI9341 display: Change the function "init_board" in <Documents>/Arduino/libraries/gfx/board_ILI9341.cpp.

7) When using ESP32: In <Documents>\Arduino\libraries\gfx\ugfx\src\gos\gos_freertos.h, you need to change the include paths to make µGFX compile:
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/semphr.h"
#include "freertos/task.h"   

8) Compile the example sketch. You will get an error that there is a "duplicate 'const'" in gdriver.h. 

9) Open "gdriver.h" and change the mentioned line to "typedef const struct GDriverVMT GDriverVMTList[1];"

10) Compile again and enjoy!

