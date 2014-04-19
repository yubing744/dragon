#include "dg_log.h"
#include "dg_android.h"

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

    va_start(params, formatStr);
	__android_log_vprint(ANDROID_LOG_INFO, this->tagName.data(), formatStr, params);
    va_end(params);
}

void DGLog::debug(const char *formatStr, ...){
	va_list params;

    va_start(params, formatStr);
    __android_log_vprint(ANDROID_LOG_DEBUG, this->tagName.data(), formatStr, params);
    va_end(params);
}

void DGLog::error(const char *formatStr, ...){
	va_list params;

    va_start(params, formatStr);
    __android_log_vprint(ANDROID_LOG_ERROR, this->tagName.data(), formatStr, params);
    va_end(params);
}
