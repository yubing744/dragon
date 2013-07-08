#pragma once

#include "dg_config.h"

#if !defined(DG_LOG)
#define DG_LOG

#include <string>
using namespace std;

class DGLog
{
public:
    DGLog(void);
    DGLog(const char* tagName);
    virtual ~DGLog(void);

public:
    virtual void info(const char *formatStr, ...);
    virtual void debug(const char *formatStr, ...);
    virtual void error(const char *formatStr, ...);

private:
    string tagName;
};

#endif

