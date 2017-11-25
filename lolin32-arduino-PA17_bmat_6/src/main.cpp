
#include <sstream>

#include <Arduino.h>
#include <WiFi.h>

#include "Console.h"
#include "HttpServer.h"
#include "SSD1306.h"
#include "MLX90614.h"
#include "SPIFFS.h"

#include "Parameters.h"
#include "FlashFileSystem.h"
#include "I2CScan.h"
#include "HttpPathHandlers.h"

#define BMAT6_DISPLAY_YELLOW_WIDTH      DISPLAY_WIDTH
#define BMAT6_DISPLAY_YELLOW_HEIGHT     16

HttpServer      httpServer;
SSD1306         display(0x3C, 21, 22);
MLX90614        thermopile;
Shell           shell;

/* Duration in seconds */
int duration = 30;

/* Temperature in Celsius */
int temperature = 50;

//PushButton      modeButton();

bool bootInit = false;
const char *ssid = "ABCTEST";
const char *password = "test1234567";

void
setup()
{
    /*** SERIAL ***************************************************************/
    Serial.begin(115200);

    /*** SHELL ****************************************************************/
    shell.setPrompt("> ");
    shell.begin(Serial, 5);

    /*** SPIFFS ***************************************************************/
    if (!SPIFFS.begin()) {
      Serial.println("SPIFFS Mount Failed");
      return;
    }
    //listDir(SPIFFS, "/", 0);
    //readFile(SPIFFS, "/index.html");
    //writeFile(SPIFFS, "/welt.txt", "aaaa\n");
    //appendFile(SPIFFS, "/welt.txt", "bbbb\n");
    //appendFile(SPIFFS, "/welt.txt", "cccccc\n");
    //listDir(SPIFFS, "/", 0);
    //readFile(SPIFFS, "/welt.txt");

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
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_GET,  "/", rootHandler);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_POST, "/", rootHandler);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_GET,  "/helloWorld", helloWorldHandler);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_GET,  "/jquery-3.2.1.min.js", jqueryJsHandler);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_GET, " /jqueryTest", jqueryTestHandler);

    Serial.println("Done!");
    bootInit = true;
}

void
loop()
{
    if (!bootInit) {
        return;
    }

    shell.loop();

/*
    double temp = thermopile.readObjectTempC();
    String tempStr = String(temp);

    //Serial.println("Loop");
    display.clear();
    for (int i = 0, k = 2; i < 16; i++, k++) {
        display.drawLine(0, i, 2*k, i);
    }
*/
    //display.drawProgressBar(0, 0, uint16_t width, uint16_t height, uint8_t progress);

/*
    std::ostringstream os;
    os << "hello " << 12 << "world!";
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, String(os.str().c_str()));
*/

/*
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, tempStr);
    display.display();
*/

    //delay(1000);

}
