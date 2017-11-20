
#include <sstream>

#include <Arduino.h>
#include <WiFi.h>

#include "HttpServer.h"
#include "SSD1306.h"
#include "MLX90614.h"

#define BMAT6_DISPLAY_YELLOW_WIDTH      DISPLAY_WIDTH
#define BMAT6_DISPLAY_YELLOW_HEIGHT     16

HttpServer      httpServer;
SSD1306         display(0x3C, 21, 22);
MLX90614        thermopile;


const char *ssid = "ABCTEST";
const char *password = "test1234567";

static void
helloWorldHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Hello back");
    pResponse->close();
}

static void
scanI2C()
{
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.print(address,HEX);
            Serial.println("  !");

            nDevices++;
        } else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address<16) {
                Serial.print("0");
            }
            Serial.println(address,HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
    } else {
        Serial.println("done\n");
    }
}


void
setup()
{
    /*** SERIAL ***************************************************************/
    Serial.begin(115200);

    /*** WIFI AP **************************************************************/
    if (!WiFi.softAP(ssid, password)) {
        Serial.println("WiFi.softAP() failed!!");
        return;
    }

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    /*** OLED *****************************************************************/
    Wire.begin(21, 22);
    scanI2C();

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);

    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
    display.display();

    /*** THERMOPILE ***********************************************************/
    thermopile.begin();

    /*** HTTP SERVER **********************************************************/
    Serial.println("httpServer.start(80)");
    httpServer.start(80);
    httpServer.addPathHandler(
        HttpRequest::HTTP_METHOD_GET,
        "/helloWorld",
        helloWorldHandler);

    Serial.println("Done!");
}

void
loop()
{
    double temp = thermopile.readObjectTempC();
    String tempStr = String(temp);

    //Serial.println("Loop");
    display.clear();
    for (int i = 0, k = 2; i < 16; i++, k++) {
        display.drawLine(0, i, 2*k, i);
    }

    //display.drawProgressBar(0, 0, uint16_t width, uint16_t height, uint8_t progress);

/*
    std::ostringstream os;
    os << "hello " << 12 << "world!";
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, String(os.str().c_str()));
*/

    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, tempStr);
    display.display();

    delay(1000);

}
