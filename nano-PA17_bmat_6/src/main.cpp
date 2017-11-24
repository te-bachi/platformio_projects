/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#include <Arduino.h>
#include <Wire.h>
#include "Leishman.h"

void receiveEvent(int numBytes);
void zcd_isr();

uint32_t i;

const byte interruptPin = 2;


void
setup()
{
    i = 0;
    attachInterrupt(digitalPinToInterrupt(interruptPin), zcd_isr, RISING);
    Leishman::begin();

    Wire.begin(8);
    Wire.onReceive(receiveEvent);

    Serial.println("Done!");
}

void
loop()
{
    //int k;

    cli.check();
    delay(1000);

    String s = "i = " + String(i);
    Serial.println(s);
}

void
receiveEvent(int numBytes) {
    Serial.print("I2C (bytes=");
    Serial.print(numBytes);
    Serial.print(") ");
    while (1 < Wire.available()) {
        char c = Wire.read();
        Serial.print(c);
    }
    byte x = Wire.read();
    Serial.println(x);
}

void
zcd_isr() {
    i++;
}
