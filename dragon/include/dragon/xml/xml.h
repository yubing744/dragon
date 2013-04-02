#ifndef XML_H
#define XML_H

#include "../config/config.h"

#define BeginPackageXml BeginPackage2(ProjectName,xml)
#define EndPackageXml EndPackage2
#define Xml ProjectName::xml

#define _XMLUNICODE
#include "xmlParser.h"

#endif