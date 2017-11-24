#include <Arduino.h>
#include <Wire.h>

int ledPin = 5;
int sclPin = 22;
int sdaPin = 21;
int tstPin = 4;

byte x = 0;

void setup()
{
    pinMode(ledPin, OUTPUT);
    //pinMode(sclPin, OUTPUT);
    //pinMode(sdaPin, OUTPUT);
    pinMode(tstPin, OUTPUT);
    Serial.begin(115200);
    Wire.begin();
}

void loop()
{
    Serial.println("Hello, world!");
    digitalWrite(ledPin, HIGH);
    //digitalWrite(sclPin, HIGH);
    //digitalWrite(sdaPin, HIGH);
    digitalWrite(tstPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    //digitalWrite(sclPin, LOW);
    //digitalWrite(sdaPin, LOW);
    digitalWrite(tstPin, LOW);
    delay(50);

    Wire.beginTransmission(8);
    Wire.write("x is ");
    Wire.write(x);
    Wire.endTransmission();

    x++;
}
