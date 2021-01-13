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
// Also already defined?!
// HardwareSerial Serial1(1);
#else
// Already defined 
#endif


bool ready = false;

void btLoop(void * arg);
void ledLoop(void * arg);

void setup() {
    pinMode(13, OUTPUT);

    Serial.begin(115200);
    Serial.println("Serial done!");
    
    Serial1.begin(230400, SERIAL_8N1, 16, 17);
    Serial.println("Serial1 done!");
    if (!SerialBT.begin("Fluedema_3")) {
        Serial.println("Can't begin SerialBT!");
        return;
    }
    Serial.println("SerialBT done!");
    
    xTaskCreate(btLoop, "myBtLoop", 4096, NULL, 0, NULL);
    xTaskCreate(ledLoop, "myLedLoop", 4096, NULL, 0, NULL);
    
    Serial.println("Done!");
    ready = true;
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
    if (ready) {
        static bool valid = true;
        while (true) {
            if (SerialBT.hasClient()) {
                if (!valid) {
                    valid = true;
                    Serial.println("Ready!");
                }

                /* UART -> BT */
                if (Serial1.available() > 0) {
                    int c = Serial1.read();
                    SerialBT.write(c);
                    //Serial.print(".");
                }

                /* BT -> UART */
                if (SerialBT.available() > 0) {
                    int c = SerialBT.read();
                    Serial1.write(c);
                    //Serial.print("-");
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
}

void
ledLoop(void * arg)
{
    while (true) {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
        //Serial.println("LED!");
    }
}