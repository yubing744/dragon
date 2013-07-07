#include "dg_log.h"

DGLog::DGLog(void){
	this->tagName = string("dragon_game");
}

DGLog::DGLog(const char* tagName){
	this->tagName = string(tagName);
}

DGLog::~DGLog(void){

}

void DGLog::info(const char *formatStr, ...) {
    va_list params;
    char buf[BUFSIZ];

    va_start(params, formatStr);
    vsprintf(buf, formatStr, params);
    printf("%s: %s\r\n", this->tagName.data(), buf);
    va_end(params);
}

void DGLog::debug(const char *formatStr, ...){
    va_list params;
    char buf[BUFSIZ];

    va_start(params, formatStr);
    vsprintf(buf, formatStr, params);
    printf("%s: %s\r\n", this->tagName.data(), buf);
    va_end(params);
}

void DGLog::error(const char *formatStr, ...){
    va_list params;
    char buf[BUFSIZ];

    va_start(params, formatStr);
    vsprintf(buf, formatStr, params);
    printf("%s: %s\r\n", this->tagName.data(), buf);
    va_end(params);
}

