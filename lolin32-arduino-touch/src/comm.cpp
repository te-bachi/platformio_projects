
#include "comm.h"

#include <Arduino.h>
#include <HardwareSerial.h>

#define rs485 Serial1
#define RS485_DIR 26

static void send(String cmd);
static String recv();

void
comm_power_on()
{
    send("99 SEN\n");
    String answer = recv();
}

void
comm_power_off()
{
    send("99 SDI\n");
    String answer = recv();
}

float
comm_temp_current_get()
{
    float temp;
    int idxLeft;
    int idxRight;
    
    send("99 GT2\n");
    String answer = recv();

    /* 99 TEMP2=21.53 C */
    idxLeft = answer.indexOf('=') + 1;
    answer.remove(0, idxLeft);

    /* 21.53 C */
    idxRight = answer.indexOf(' ');
    answer.remove(idxRight, answer.length() - idxRight);

    /*  21.53 */
    //Serial.print(answer);
    temp = answer.toFloat();

    return temp;
}

void
comm_temp_target_set(int temp)
{

}


static void send(String cmd)
{    
    int i;
    digitalWrite(RS485_DIR, HIGH);
    for (i = 0; i < cmd.length(); i++) {
        rs485.write(cmd[i]);
        Serial.print(cmd[i]);
    }
    /* wait until TX buffer is sent out */
    rs485.flush();
    //rs485.waitTxDone();
    //delayMicroseconds(650);
    
    digitalWrite(RS485_DIR, LOW);
}

static String recv()
{    
    String s;

    /* Wait until data is received */
    while (!rs485.available());

    /* Read */
    do {
        char inChar = (char) rs485.read();
        Serial.print(inChar);
        s += inChar;
    } while (rs485.available());

    return s;
}