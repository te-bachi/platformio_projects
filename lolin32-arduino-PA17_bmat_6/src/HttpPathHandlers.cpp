/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include <Arduino.h>
#include <FS.h>
#include <EEPROM.h>
#include <Wire.h>

/* unbedingt nachdem Arduino.h included wurde, sonst gibt
   es Probleme mit IPADDR_NONE in lwip/ip4_addr.h */
#include "HttpPathHandlers.h"

#include <string>

#include "EEPROMUtil.h"
#include "SPIFFS.h"
#include "Parameters.h"

using namespace PA17_bmat_6;

static bool
is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void
PA17_bmat_6::rootHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    std::ostringstream buffer;
    bool error = false;

    if (pRequest->getMethod() == HttpRequest::HTTP_METHOD_POST) {
        std::map<std::string, std::string> map = pRequest->parseForm();
        std::string d_str = map["duration"];
        std::string t_str = map["temperature"];

        Serial.println("Try to convert strings to numbers");
        if (is_digits(d_str) && is_digits(t_str)) {
            DurationType    d = std::stoi(d_str);
            TemperatureType t = std::stoi(t_str);
            Serial.print("duration ");
            Serial.print(duration);
            Serial.print(" -> ");
            Serial.print(d);
            Serial.print(" temperature ");
            Serial.print(temperature);
            Serial.print(" -> ");
            Serial.println(t);
            duration    = d;
            temperature = t;

            EEPROMConfig config;
            config.duration    = d;
            config.temperature = t;
            EEPROMUtil::writeConfig(config);
        } else {
            Serial.print("Error in converstion: ");
            Serial.print("duration = ");
            Serial.print(d_str.c_str());
            Serial.print(" temperature = ");
            Serial.println(t_str.c_str());
            error = true;
        }
    }

    buffer << "<!doctype html>\n";
    buffer << "<html lang=\"en\">\n";
    buffer << "    <head>\n";
    buffer << "        <title>Cutaneous Leishmaniasis Control Panel</title>\n";
    buffer << "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">\n";
    buffer << "    </head>\n";
    buffer << "    <body>\n";
    if (error) {
        buffer << "        <div>Error in conversion!</div>\n";
    }
    buffer << "        <form id=\"control-panel\" method=\"POST\">\n";
    buffer << "            <table>\n";
    buffer << "                <tr>\n";
    buffer << "                    <td colspan=\"2\"><label form=\"control-panel\">Cutaneous Leishmaniasis Control Panel</label></td>\n";
    buffer << "                </tr>\n";
    buffer << "                <tr>\n";
    buffer << "                    <td><label for=\"duration\">Duration:</label></td>\n";
    buffer << "                    <td><input type=\"text\" name=\"duration\" id=\"duration\" maxlength=\"3\" value=\"" << duration << "\"></td>\n";
    buffer << "                </tr>\n";
    buffer << "                <tr>\n";
    buffer << "                    <td><label for=\"temperature\">Temperature:</label></td>\n";
    buffer << "                    <td><input type=\"text\" name=\"temperature\" id=\"temperature\" maxlength=\"3\" value=\"" << temperature << "\"></td>\n";
    buffer << "                </tr>\n";
    buffer << "                <tr>\n";
    buffer << "                    <td>&nbsp;</td>\n";
    buffer << "                    <td><button type=\"submit\">Submit</button></td>\n";
    buffer << "                </tr>\n";
    buffer << "            </table>\n";
    buffer << "        </form>\n";
    buffer << "    </body>\n";
    buffer << "</html>\n";

    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/html");
    pResponse->sendData(buffer.str());
    pResponse->close();
}

void
PA17_bmat_6::intensityDebugHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    std::ostringstream buffer;
    bool error = false;

    if (pRequest->getMethod() == HttpRequest::HTTP_METHOD_POST) {
        std::map<std::string, std::string> map = pRequest->parseForm();
        std::string i_str = map["intensity"];

        Serial.println("Try to convert strings to numbers");
        if (is_digits(i_str)) {
            IntensityType i = std::stoi(i_str);
            Serial.print("intensity ");
            Serial.print(intensityDebug);
            Serial.print(" -> ");
            Serial.println(i);
            intensityDebug = i;

            Wire.beginTransmission(NANO_I2C_ADDRESS);
            Wire.write(intensityDebug);
            Wire.endTransmission();
        } else {
            Serial.print("Error in converstion: ");
            Serial.print("intensity = ");
            Serial.println(i_str.c_str());
            error = true;
        }
    }

    buffer << "<!doctype html>\n";
    buffer << "<html lang=\"en\">\n";
    buffer << "    <head>\n";
    buffer << "        <title>Cutaneous Leishmaniasis Control Panel - Intensity Debug</title>\n";
    buffer << "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">\n";
    buffer << "    </head>\n";
    buffer << "    <body>\n";
    if (error) {
        buffer << "        <div>Error in conversion!</div>\n";
    }
    buffer << "        <form id=\"intensity-debug\" method=\"POST\">\n";
    buffer << "            <table>\n";
    buffer << "                <tr>\n";
    buffer << "                    <td colspan=\"2\"><label form=\"intensity-debug\">Cutaneous Leishmaniasis Control Panel - Intensity Debug</label></td>\n";
    buffer << "                </tr>\n";
    buffer << "                <tr>\n";
    buffer << "                    <td><label for=\"intensity\">Intensity:</label></td>\n";
    buffer << "                    <td><input type=\"text\" name=\"intensity\" id=\"intensity\" maxlength=\"3\" value=\"" << std::to_string(intensityDebug) << "\"></td>\n";
    buffer << "                </tr>\n";
    buffer << "                <tr>\n";
    buffer << "                    <td>&nbsp;</td>\n";
    buffer << "                    <td><button type=\"submit\">Submit</button></td>\n";
    buffer << "                </tr>\n";
    buffer << "            </table>\n";
    buffer << "        </form>\n";
    buffer << "    </body>\n";
    buffer << "</html>\n";

    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/html");
    pResponse->sendData(buffer.str());
    pResponse->close();
}

void
PA17_bmat_6::helloWorldHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Hello back");
    pResponse->close();
}

void
PA17_bmat_6::jqueryJsHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    std::ostringstream buffer;

    File file = SPIFFS.open("/jquery.js");
    if (!file) {
      Serial.println("=== Failed to open file for reading");
      return;
    }

/*
    Serial.print("=== Read from file: ");
    while (file.available()) {
      buffer << file.read();
    }
*/
    while(file.available()){
        Serial.write(file.read());
    }

    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/javascript");
    //pResponse->sendData(buffer.str());
    pResponse->sendData("");
    pResponse->close();
}

void
PA17_bmat_6::jqueryTestHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    std::ostringstream buffer;
    buffer << "<!DOCTYPE html>\n";
    buffer << "<html lang=\"de\">\n";
    buffer << "  <head>\n";
    buffer << "    <title>jQuery Beispiel: einbinden und erster Befehl</title>\n";
    buffer << "    <script src=\"jquery-3.2.1.min.js\"></script>\n";
    buffer << "    <script>\n";
    buffer << "$(document).ready(function(){\n";
    buffer << "    /* Hier der jQuery-Code */\n";
    buffer << "    alert('Hallo Welt');\n";
    buffer << "});\n";
    buffer << "    </script>\n";
    buffer << "  </head>\n";
    buffer << "  <body>\n";
    buffer << "    <h1>jQuery Beispiel: einbinden und erster Befehl</h1>\n";
    buffer << "  </body>\n";
    buffer << "</html>\n";

    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/html");
    pResponse->sendData(buffer.str());
    pResponse->close();
}
