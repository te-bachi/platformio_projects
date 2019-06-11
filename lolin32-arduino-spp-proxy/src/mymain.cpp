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
    
void btLoop(void * arg);

void setup() {
    Serial.begin(115200);
    Serial.println("Serial done!");
    Serial1.begin(230400, SERIAL_8N1, 5, 4);
    Serial.println("Serial1 done!");
    SerialBT.begin("Fluedema_1");
    Serial.println("SerialBT done!");

    xTaskCreate(btLoop, "myBtLoop", 4096, NULL, 2, NULL);
    
    Serial.println("Done!");
}

void loop() {
    delay(1000);
}


/**
 * btLoop task must have a delay so that
 * the OS can switch to the setup task
 */
void
btLoop(void * arg)
{
    static bool valid = true;
    while (true) {
        if (SerialBT.hasClient()) {
            if (!valid) {
                valid = true;
                Serial.println("Ready!");
            }
            if (Serial1.available() > 0) {
                int c = Serial1.read();
                SerialBT.write(c);
            }
        } else {
            if (valid) {
                valid = false;
                Serial.println("Not ready!");
            }
        }
        taskYIELD();
    }
}