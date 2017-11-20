/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

 #include "Leishman.h"

 CLI                     cli;

 Leishman::Leishman()
 {
     //
 }

 Leishman::~Leishman()
 {
     //
 }

 static void countdown()
 {
     for (int i = PHYSIOTRAIN_COUNTDOWN; i > 0; i--) {
         Serial.println(i);
         delay(1000);
     }
 }

 void Leishman::begin()
 {
     Serial.begin(SERIAL_BAUD_RATE);

     countdown();

     cli.begin();
 }
