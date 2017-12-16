
#include <sstream>

#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>

#include "EEPROMUtil.h"
#include "Console.h"
#include "HttpServer.h"
#include "SPIFFS.h"

#include "Parameters.h"
#include "FlashFileSystem.h"
#include "I2CScan.h"
#include "HttpPathHandlers.h"
#include "PushButton.h"
#include "PushButtonHandler.h"

#define BMAT6_TIME_DEBOUNCING_DELAY_MS  30

using namespace PA17_bmat_6;

HttpServer      httpServer;
Display         display;
Dimmer          dimmer(Wire, NANO_I2C_ADDRESS);
MLX90614        thermopile;
Shell           shell;
PushButtonTask  pushButtonTask(BMAT6_TIME_DEBOUNCING_DELAY_MS);
PushButton      modeButton(33, modeHandler);
PushButton      selectButton(32, selectHandler);

/* Duration in seconds (saved in EEPROM) */
DurationType    duration;

/* Temperature in Celsius (saved in EEPROM) */
TemperatureType temperature;

/* Dimmer Intensity Debug */
IntensityType   intensityDebug  = 0;

bool            bootInit        = false;

const char *    ssid            = "PA17_bmat_6";
const char *    password        = "PA17_bmat_6";

IPAddress       myIP;

void
setup()
{
    /*** SERIAL ***************************************************************/
    Serial.begin(115200 /* baud rate */);

    /*** PUSH BUTTONS *********************************************************/
    pushButtonTask.addPushButton(&modeButton);
    pushButtonTask.addPushButton(&selectButton);
    pushButtonTask.start();

    /*** SHELL ****************************************************************/
    shell.setPrompt("> ");
    shell.begin(Serial, 5);

    /*** EEPROM ***************************************************************/
    if (!EEPROM.begin(EEPROM_SIZE /* size */)) {
      Serial.println("EEPROM failed to initialise");
      return;
    }
    EEPROMConfig config = EEPROMUtil::readConfig();
    duration    = config.duration;
    temperature = config.temperature;

    /*** SPIFFS ***************************************************************/
    if (!SPIFFS.begin()) {
      Serial.println("SPIFFS mount failed");
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
        Serial.println("WiFi AP failed to initialise");
        return;
    }

    myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    /*** I2C ******************************************************************/
    Wire.begin(21 /*SDA */, 22 /* SCL */);
    scanI2C();

    /*** DISPLAY **************************************************************/
    display.begin();

    /*** DIMMER ***************************************************************/
    dimmer.setStep(Dimmer::OFF);

    /*** THERMOPILE ***********************************************************/
    thermopile.begin();

    /*** HTTP SERVER **********************************************************/
    Serial.println("httpServer.start(80)");
    httpServer.start(80);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_GET,  "/", rootHandler);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_POST, "/", rootHandler);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_GET,  "/intensityDebug", intensityDebugHandler);
    httpServer.addPathHandler(HttpRequest::HTTP_METHOD_POST, "/intensityDebug", intensityDebugHandler);
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

    display.getCurrentMenu()->loop();
}
