#include <Arduino.h>

int ledPin = 2;
int count = 0;

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    Serial.print("Hello, world ");
    Serial.print(count);
    Serial.println("!");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(250);
    count++;
}
