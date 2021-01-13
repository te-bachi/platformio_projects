
#include <Arduino.h>
#include <Wire.h>
#include "MCP45HVX1.h"

MCP45HVX1 digiPot(0x3C);


int wiper;

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");

  {
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.print(address,HEX);
        Serial.println("  !");

        nDevices++;
      }
      else if (error==4)
      {
        Serial.print("Unknown error at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.println(address,HEX);
      }
    }
    if (nDevices == 0)
      Serial.println("No I2C devices found\n");
    else
      Serial.println("done\n");
  }

  digiPot.begin();

  Serial.println("\n----- Wiper Register ----");
  Serial.print("readWiper: ");
  Serial.println(digiPot.readWiper());

  Serial.print("writeWiper: ");
  wiper = 128;
  digiPot.writeWiper(wiper);
  Serial.println(digiPot.readWiper());
}

void loop()
{
  int recv;

  while (Serial.available() > 0)
  {
    recv = Serial.read();
    if (recv == 'u') {
      wiper += 5;
    } else if (recv == 'd') {
      wiper -= 5;
    }
    digiPot.writeWiper(wiper);
  }
}