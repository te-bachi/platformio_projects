#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
}

typedef union {
    float f;
    byte b[4];
} float_char_t;

typedef struct {
    float_char_t f1;
    float_char_t f2;
    float_char_t f3;
    float_char_t f4;
} float_char_array_t;

void
convertFloat(float_char_t f, char *b)
{
    memcpy(b, f.b, 4);
}

void
array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}

void
printFloat(float f)
{
    float_char_t fc;
    fc.f = f;
    char buffer[5];
    array_to_string(fc.b, 4, buffer);

    Serial.println(buffer);
    //Serial.println('\n');
}


void loop()
{
    /*
    float f1 = 15.6;
    float f2 = 0.0;
    float f3 = 1.0;
    float f4 = 10000;
    printFloat(f1);
    printFloat(f2);
    printFloat(f3);
    printFloat(f4);
    */
   
    float f1 = 1234.5678;
    float f2 = 9876.5432;
    float f3 = 11.22;
    float f4 = 33.55;

    float_char_array_t arr;
    arr.f1.f = f1;
    arr.f2.f = f2;
    arr.f3.f = f3;
    arr.f4.f = f4;

    //printFloat(f1);
    //printFloat(arr.f1.f);
    /*
    printFloat(arr.f1.f);
    printFloat(arr.f2.f);
    printFloat(arr.f3.f);
    printFloat(arr.f4.f);
    */
    unsigned char start[] = {0xff, 0xff, 0xff, 0xff};
    
    
    //int a = sizeof(arr.f1.b);
    //Serial.println(a);
    
    Serial.write(start, sizeof(start));
    Serial.write(arr.f1.b, sizeof(arr.f1.b));
    Serial.write(arr.f2.b, sizeof(arr.f2.b));
    Serial.write(arr.f3.b, sizeof(arr.f3.b));
    Serial.write(arr.f4.b, sizeof(arr.f4.b));
    
    delay(1000);
}