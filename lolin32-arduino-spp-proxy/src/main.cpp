#include <Arduino.h>

#include "pins_arduino.h"
#include "HardwareSerial.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#else
BluetoothSerial SerialBT;
#endif


#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
//HardwareSerial Serial1(1);
#else
// Already defined 
#endif
    
void setup() {
    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1, 5, 4);
}

void loop() {
    String str;
    //Serial1.println("hello");
    if (Serial1.available() > 0) {
        int c = Serial1.read();
        Serial.println("!");
        Serial1.print("*");
    }
    //delay(1000);
}