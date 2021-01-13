#include <Arduino.h>
#include <Wire.h>
#include <MCP45HVX1.h>

MCP45HVX1 digiPotOffset(0x3C);
MCP45HVX1 digiPotAmplitude(0x3D);

int sinus_wave[] = {
    0x7f, 0x80, 0x81, 0x81, 0x82, 0x83, 0x84, 0x85, 0x85, 0x86, 0x87, 0x88, 0x89, 0x89, 0x8a, 0x8b,
    0x8c, 0x8d, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x91, 0x92, 0x93, 0x94, 0x95, 0x95, 0x96, 0x97, 0x98,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9c, 0x9d, 0x9e, 0x9f, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa3, 0xa4,
    0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa9, 0xa9, 0xaa, 0xab, 0xac, 0xac, 0xad, 0xae, 0xaf, 0xaf, 0xb0,
    0xb1, 0xb2, 0xb2, 0xb3, 0xb4, 0xb5, 0xb5, 0xb6, 0xb7, 0xb7, 0xb8, 0xb9, 0xba, 0xba, 0xbb, 0xbc,
    0xbc, 0xbd, 0xbe, 0xbf, 0xbf, 0xc0, 0xc1, 0xc1, 0xc2, 0xc3, 0xc3, 0xc4, 0xc5, 0xc5, 0xc6, 0xc7,
    0xc7, 0xc8, 0xc9, 0xc9, 0xca, 0xcb, 0xcb, 0xcc, 0xcd, 0xcd, 0xce, 0xce, 0xcf, 0xd0, 0xd0, 0xd1,
    0xd1, 0xd2, 0xd3, 0xd3, 0xd4, 0xd5, 0xd5, 0xd6, 0xd6, 0xd7, 0xd7, 0xd8, 0xd9, 0xd9, 0xda, 0xda,
    0xdb, 0xdb, 0xdc, 0xdc, 0xdd, 0xde, 0xde, 0xdf, 0xdf, 0xe0, 0xe0, 0xe1, 0xe1, 0xe2, 0xe2, 0xe3,
    0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe6, 0xe6, 0xe7, 0xe7, 0xe8, 0xe8, 0xe8, 0xe9, 0xe9, 0xea, 0xea,
    0xeb, 0xeb, 0xec, 0xec, 0xec, 0xed, 0xed, 0xee, 0xee, 0xee, 0xef, 0xef, 0xef, 0xf0, 0xf0, 0xf1,
    0xf1, 0xf1, 0xf2, 0xf2, 0xf2, 0xf3, 0xf3, 0xf3, 0xf4, 0xf4, 0xf4, 0xf5, 0xf5, 0xf5, 0xf6, 0xf6,
    0xf6, 0xf6, 0xf7, 0xf7, 0xf7, 0xf7, 0xf8, 0xf8, 0xf8, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xfa, 0xfa,
    0xfa, 0xfa, 0xfa, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfd, 0xfd,
    0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
    0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
    0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfd, 0xfd,
    0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfb, 0xfb, 0xfb,
    0xfb, 0xfb, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf8, 0xf8, 0xf8, 0xf7,
    0xf7, 0xf7, 0xf7, 0xf6, 0xf6, 0xf6, 0xf6, 0xf5, 0xf5, 0xf5, 0xf4, 0xf4, 0xf4, 0xf3, 0xf3, 0xf3,
    0xf2, 0xf2, 0xf2, 0xf1, 0xf1, 0xf1, 0xf0, 0xf0, 0xef, 0xef, 0xef, 0xee, 0xee, 0xee, 0xed, 0xed,
    0xec, 0xec, 0xec, 0xeb, 0xeb, 0xea, 0xea, 0xe9, 0xe9, 0xe8, 0xe8, 0xe8, 0xe7, 0xe7, 0xe6, 0xe6,
    0xe5, 0xe5, 0xe4, 0xe4, 0xe3, 0xe3, 0xe2, 0xe2, 0xe1, 0xe1, 0xe0, 0xe0, 0xdf, 0xdf, 0xde, 0xde,
    0xdd, 0xdc, 0xdc, 0xdb, 0xdb, 0xda, 0xda, 0xd9, 0xd9, 0xd8, 0xd7, 0xd7, 0xd6, 0xd6, 0xd5, 0xd5,
    0xd4, 0xd3, 0xd3, 0xd2, 0xd1, 0xd1, 0xd0, 0xd0, 0xcf, 0xce, 0xce, 0xcd, 0xcd, 0xcc, 0xcb, 0xcb,
    0xca, 0xc9, 0xc9, 0xc8, 0xc7, 0xc7, 0xc6, 0xc5, 0xc5, 0xc4, 0xc3, 0xc3, 0xc2, 0xc1, 0xc1, 0xc0,
    0xbf, 0xbf, 0xbe, 0xbd, 0xbc, 0xbc, 0xbb, 0xba, 0xba, 0xb9, 0xb8, 0xb7, 0xb7, 0xb6, 0xb5, 0xb5,
    0xb4, 0xb3, 0xb2, 0xb2, 0xb1, 0xb0, 0xaf, 0xaf, 0xae, 0xad, 0xac, 0xac, 0xab, 0xaa, 0xa9, 0xa9,
    0xa8, 0xa7, 0xa6, 0xa6, 0xa5, 0xa4, 0xa3, 0xa3, 0xa2, 0xa1, 0xa0, 0x9f, 0x9f, 0x9e, 0x9d, 0x9c,
    0x9c, 0x9b, 0x9a, 0x99, 0x98, 0x98, 0x97, 0x96, 0x95, 0x95, 0x94, 0x93, 0x92, 0x91, 0x91, 0x90,
    0x8f, 0x8e, 0x8d, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x89, 0x88, 0x87, 0x86, 0x85, 0x85, 0x84, 0x83,
    0x82, 0x81, 0x81, 0x80, 0x7f, 0x7e, 0x7d, 0x7d, 0x7c, 0x7b, 0x7a, 0x79, 0x79, 0x78, 0x77, 0x76,
    0x75, 0x75, 0x74, 0x73, 0x72, 0x71, 0x71, 0x70, 0x6f, 0x6e, 0x6d, 0x6d, 0x6c, 0x6b, 0x6a, 0x69,
    0x69, 0x68, 0x67, 0x66, 0x66, 0x65, 0x64, 0x63, 0x62, 0x62, 0x61, 0x60, 0x5f, 0x5f, 0x5e, 0x5d,
    0x5c, 0x5b, 0x5b, 0x5a, 0x59, 0x58, 0x58, 0x57, 0x56, 0x55, 0x55, 0x54, 0x53, 0x52, 0x52, 0x51,
    0x50, 0x4f, 0x4f, 0x4e, 0x4d, 0x4c, 0x4c, 0x4b, 0x4a, 0x49, 0x49, 0x48, 0x47, 0x47, 0x46, 0x45,
    0x44, 0x44, 0x43, 0x42, 0x42, 0x41, 0x40, 0x3f, 0x3f, 0x3e, 0x3d, 0x3d, 0x3c, 0x3b, 0x3b, 0x3a,
    0x39, 0x39, 0x38, 0x37, 0x37, 0x36, 0x35, 0x35, 0x34, 0x33, 0x33, 0x32, 0x31, 0x31, 0x30, 0x30,
    0x2f, 0x2e, 0x2e, 0x2d, 0x2d, 0x2c, 0x2b, 0x2b, 0x2a, 0x29, 0x29, 0x28, 0x28, 0x27, 0x27, 0x26,
    0x25, 0x25, 0x24, 0x24, 0x23, 0x23, 0x22, 0x22, 0x21, 0x20, 0x20, 0x1f, 0x1f, 0x1e, 0x1e, 0x1d,
    0x1d, 0x1c, 0x1c, 0x1b, 0x1b, 0x1a, 0x1a, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x16, 0x16, 0x16,
    0x15, 0x15, 0x14, 0x14, 0x13, 0x13, 0x12, 0x12, 0x12, 0x11, 0x11, 0x10, 0x10, 0x10, 0x0f, 0x0f,
    0x0f, 0x0e, 0x0e, 0x0d, 0x0d, 0x0d, 0x0c, 0x0c, 0x0c, 0x0b, 0x0b, 0x0b, 0x0a, 0x0a, 0x0a, 0x09,
    0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x0a, 0x0a,
    0x0a, 0x0b, 0x0b, 0x0b, 0x0c, 0x0c, 0x0c, 0x0d, 0x0d, 0x0d, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x10,
    0x10, 0x10, 0x11, 0x11, 0x12, 0x12, 0x12, 0x13, 0x13, 0x14, 0x14, 0x15, 0x15, 0x16, 0x16, 0x16,
    0x17, 0x17, 0x18, 0x18, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b, 0x1c, 0x1c, 0x1d, 0x1d, 0x1e, 0x1e,
    0x1f, 0x1f, 0x20, 0x20, 0x21, 0x22, 0x22, 0x23, 0x23, 0x24, 0x24, 0x25, 0x25, 0x26, 0x27, 0x27,
    0x28, 0x28, 0x29, 0x29, 0x2a, 0x2b, 0x2b, 0x2c, 0x2d, 0x2d, 0x2e, 0x2e, 0x2f, 0x30, 0x30, 0x31,
    0x31, 0x32, 0x33, 0x33, 0x34, 0x35, 0x35, 0x36, 0x37, 0x37, 0x38, 0x39, 0x39, 0x3a, 0x3b, 0x3b,
    0x3c, 0x3d, 0x3d, 0x3e, 0x3f, 0x3f, 0x40, 0x41, 0x42, 0x42, 0x43, 0x44, 0x44, 0x45, 0x46, 0x47,
    0x47, 0x48, 0x49, 0x49, 0x4a, 0x4b, 0x4c, 0x4c, 0x4d, 0x4e, 0x4f, 0x4f, 0x50, 0x51, 0x52, 0x52,
    0x53, 0x54, 0x55, 0x55, 0x56, 0x57, 0x58, 0x58, 0x59, 0x5a, 0x5b, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
    0x5f, 0x60, 0x61, 0x62, 0x62, 0x63, 0x64, 0x65, 0x66, 0x66, 0x67, 0x68, 0x69, 0x69, 0x6a, 0x6b,
    0x6c, 0x6d, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x71, 0x72, 0x73, 0x74, 0x75, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7d, 0x7e 
};

const static unsigned int sinus_wave_len = sizeof(sinus_wave)/sizeof(int);

volatile unsigned int i = 0;
volatile int wiperOffset;
volatile int wiperAmplitute;
volatile int periodMicro;
HardwareTimer *MyTim;

void Update_IT_callback(void)
{
    if (i >= sinus_wave_len) {
        //Serial.print("break ");
        //Serial.println(i);
        i = 0;
    }
    analogWrite(PA4, sinus_wave[i]);
    i++;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Booting...");
    //Wire.setSDA(PB9);
    //Wire.setSCL(PB8);
    Wire.setSDA(PB7);
    Wire.setSCL(PB6);
    Wire.begin();

    pinMode(PB14, OUTPUT);
    pinMode(PB13, OUTPUT);
    pinMode(PB1, OUTPUT);


  MyTim = new HardwareTimer(TIM1);
  periodMicro = 1*sinus_wave_len; // 1 Hz
  MyTim->setOverflow(periodMicro, MICROSEC_FORMAT);
  MyTim->attachInterrupt(Update_IT_callback);
  MyTim->resume();

    //pinMode(PA5, OUTPUT);

    Serial.println("\nI2C Scanner");

    {
        byte error, address;
        int nDevices;

        Serial.println("Scanning...");

        nDevices = 0;
        for(address = 1; address < 127; address++ ) {
            // The i2c_scanner uses the return value of
            // the Write.endTransmisstion to see if
            // a device did acknowledge to the address.
            Wire.beginTransmission(address);
            error = Wire.endTransmission();

            if (error == 0) {
                Serial.print("I2C device found at address 0x");
                if (address<16)
                Serial.print("0");
                Serial.print(address,HEX);
                Serial.println("  !");

                nDevices++;
            } else if (error==4) {
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
    

    digiPotOffset.begin();
    digiPotAmplitude.begin();

    wiperOffset = 198;
    wiperAmplitute = 128;

    Serial.println("\n----- Offset Wiper Register ----");
    Serial.print("readWiper: ");
    Serial.println(digiPotOffset.readWiper());

    Serial.print("writeWiper: ");
    digiPotOffset.writeWiper(wiperOffset);
    Serial.println(digiPotOffset.readWiper());

    delay(100);

    Serial.println("\n----- Amplitude Wiper Register ----");
    Serial.print("readWiper: ");
    Serial.println(digiPotAmplitude.readWiper());

    Serial.print("writeWiper: ");
    digiPotAmplitude.writeWiper(wiperAmplitute);
    Serial.println(digiPotAmplitude.readWiper());


    Serial.print("Sinus length: ");
    Serial.println(sizeof(sinus_wave)/sizeof(int));
}


bool out1 = false;
bool out2 = false;
bool out3 = false;

/*
 * +14V / -14V: O: 198 A: 223
 * +5V / -5V: O: 198 A: 128
 * +3.3V / -3.3V: O: 198 A: 88
 * +3.3V / 0V: O: 3 A: 43
 * +5.0V / 0V: O: 0 A: 67
 * +14V / 0V: O: 5 A: 162
 */

void loop() {
    /*
    Serial.println("Loop");
    digitalWrite(PA5, 1);
    delay(500);
    digitalWrite(PA5, 0);
    delay(500);
    */

    int recv;
    bool potOffset = false;
    bool potAmp = false;
    bool period = false;
    while (Serial.available() > 0)
    {
        recv = Serial.read();

        /* offset */
        if (recv == 'a') {
            wiperOffset += 1;
            potOffset = true;
        } else if (recv == 'b') {
            wiperOffset -= 1;
            potOffset = true;

        /* amplitute */
        } else if (recv == 'u') {
            wiperAmplitute += 1;
            potAmp = true;
        } else if (recv == 'd') {
            wiperAmplitute -= 1;
            potAmp = true;

        /* frequency */
        } else if (recv == 'q') {
            periodMicro /= 2;
            period = true;
        } else if (recv == 'w') {
            periodMicro *= 2;
            period = true;
        }

        if (potOffset) {
            digiPotOffset.writeWiper(wiperOffset);
        } else if (potAmp) {
            digiPotAmplitude.writeWiper(wiperAmplitute);
        } else if (period) {
            MyTim->setOverflow(periodMicro, MICROSEC_FORMAT);
        }

        Serial.print("O: ");
        Serial.print(digiPotOffset.readWiper());
        Serial.print(" A: ");
        Serial.print(digiPotAmplitude.readWiper());
        Serial.print(" F: ");
        Serial.println(periodMicro);
    }
   //Serial.print("test!\n");
   //delay(100);

    out1 = !out1;
    out2 = !out2;
    out3 = !out3;

    digitalWrite(PB14, out1);
    digitalWrite(PB13, out1);
    digitalWrite(PB1, out1);
}