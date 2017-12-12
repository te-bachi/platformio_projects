/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __HTTP_PATH_HANDLERS_H__
#define __HTTP_PATH_HANDLERS_H__

#include "HttpServer.h"

namespace PA17_bmat_6 {
    void rootHandler(HttpRequest* pRequest, HttpResponse* pResponse);
    void intensityDebugHandler(HttpRequest* pRequest, HttpResponse* pResponse);
    void helloWorldHandler(HttpRequest* pRequest, HttpResponse* pResponse);
    void jqueryJsHandler(HttpRequest* pRequest, HttpResponse* pResponse);
    void jqueryTestHandler(HttpRequest* pRequest, HttpResponse* pResponse);
};

#endif
