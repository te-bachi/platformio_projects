/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#include "Leishman.h"

void zcd_isr();

uint32_t i;

const byte interruptPin = 2;

void
setup() {
    i = 0;
    attachInterrupt(digitalPinToInterrupt(interruptPin), zcd_isr, RISING);
    Leishman::begin();
    Serial.println("Done!");
}

void
loop() {
    //int k;

    cli.check();
    delay(1000);

    String s = "i = " + String(i);
    Serial.println(s);
}

void
zcd_isr() {
    i++;
}
