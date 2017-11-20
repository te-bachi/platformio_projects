
#include "HttpServer.h"

extern "C" void app_main()
{
    printf("hello world!");

    HttpServer httpServer;
    httpServer.start(80);

    printf("done!");

    while (true) {
        
    }
}
