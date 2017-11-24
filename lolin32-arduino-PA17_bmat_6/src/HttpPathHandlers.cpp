
#include <Arduino.h>
#include <FS.h>

#include "HttpPathHandlers.h"
#include "SPIFFS.h"

void
rootHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{

}

void
helloWorldHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Hello back");
    pResponse->close();
}

void
jqueryJsHandler(HttpRequest* pRequest, HttpResponse* pResponse)
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
jqueryTestHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    std::ostringstream buffer;
    buffer << "<!DOCTYPE html>\n";
    buffer << "<html lang=\"de\">\n";
    buffer << "<head>\n";
    buffer << "<title>jQuery Beispiel: einbinden und erster Befehl</title>\n";
    buffer << "<script src=\"jquery-3.2.1.min.js\"></script>\n";
    buffer << "<script>\n";
    buffer << "$(document).ready(function(){\n";
    buffer << "    /* Hier der jQuery-Code */\n";
    buffer << "    alert('Hallo Welt');\n";
    buffer << "});\n";
    buffer << "</script>\n";
    buffer << "</head>\n";
    buffer << "<body>\n";
    buffer << "<h1>jQuery Beispiel: einbinden und erster Befehl</h1>\n";
    buffer << "</body>\n";
    buffer << "</html>\n";

    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/html");
    pResponse->sendData(buffer.str());
    pResponse->close();
}
