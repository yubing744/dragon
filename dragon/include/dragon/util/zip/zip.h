#ifndef Dragon_Util_Zip_H
#define Dragon_Util_Zip_H

#include <dragon/config.h>

#define BeginPackageZip BeginPackage3(dragon,util,zip)
#define EndPackageZip EndPackage3
#define Zip dragon::util::zip

BeginPackageZip

	class ZipEntry;
	class ZipFile;

EndPackageZip

#include "../../lang/lang.h"
#include "../util.h"

#include "ZipEntry.h"
#include "ZipFile.h"


#endif
