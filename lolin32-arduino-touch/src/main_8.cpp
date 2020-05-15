


#ifdef ANDREAS

#include <Arduino.h>

#include <HardwareSerial.h>

#define LED_PIN 2
#define RS485_DIR 26

//HardwareSerial rs485(1);
#define rs485 Serial1


void readLoop(void * arg);
void writeLoop(void * arg);
void ledLoop(void * arg);

void send(String cmd)
{    
    int i;
    digitalWrite(RS485_DIR, HIGH);
    for (i = 0; i < cmd.length(); i++) {
        rs485.write(cmd[i]);
        Serial.print(cmd[i]);
    }
    delayMicroseconds(650);
    digitalWrite(RS485_DIR, LOW);
}

String recv()
{    
    String s;
    
    /* Wait */
    //while (!rs485.available()) {
        //Serial.print(".");
    //}
    //Serial.println(".");

    /* Read */
    while (rs485.available()) {
        char inChar = (char) rs485.read();
        Serial.print(inChar);
        //s += inChar;
    }

    return s;
}

double getDouble(String cmd)
{
    String answer;

    /* Write */
    send(cmd);

    /* Read */
    answer = recv();

    return answer.toDouble();
}

void getTemp()
{
    send("99 GT2\n");
    String answer = recv();
    //double temp = getDouble("99 GT2\n");
    
    double temp = answer.toDouble();
    Serial.print("T2=");
    Serial.println(temp);
}

void enable()
{
    send("99 SEN\n");
    String answer = recv();
    //Serial.println(answer);
}

void disable() 
{
    send("99 SDI\n");
    String answer = recv();
    //Serial.println(answer);
}

void
setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    pinMode(RS485_DIR, OUTPUT);
    digitalWrite(RS485_DIR, LOW);

    Serial.begin(115200);
    Serial.println("Serial done!");

    rs485.begin(115200, SERIAL_8N1, 4, 5);
    Serial.println("RS485 done!");

    //xTaskCreate(readLoop, "myReadLoop", 4096, NULL, 0, NULL);
    xTaskCreate(writeLoop, "myWriteLoop", 4096, NULL, 0, NULL);
    xTaskCreate(ledLoop, "myLedLoop", 4096, NULL, 0, NULL);
}

void
loop()
{
    //yield();
    delay(1000);
}

void
readLoop(void * arg)
{

    Serial.w
    while (true) {
        if (rs485.available()) {
            int i = rs485.read();
            char c = (char) i;
            Serial.print(c);
            rs485.write("w");
        } else {
            Serial.print(".");
        }
        delay(100);
    }
}

void
writeLoop(void * arg)
{
    //int i;
    //String s = "GT1";
    //String s = "99 GST\n";
    //String s1 = ;
    //String s2 = ;

/*
    delay(2000);
    enable();
    delay(2000);
    disable();
    delay(200);
    getTemp();
*/

    while (true) { 
        /*  
        for (i = 0; i < s1.length(); i++) {
            rs485.write(s1[i]);
        }
        delay(1000);

        for (i = 0; i < s2.length(); i++) {
            rs485.write(s2[i]);
        }
        delay(1000);
        */
       //delay(100);

       
        enable();
        delay(1000);

        disable();
        delay(1000);
    }
}

void
ledLoop(void * arg)
{
    while (true) {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
    }
}

#endif
