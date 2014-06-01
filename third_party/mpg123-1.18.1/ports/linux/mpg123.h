/* Since we are not actually running the whole configuration
* build process, this fills the need for mpg123.h, which
* would normally be built from mpg123.h.in
*/

#ifndef MPG123_LINUX_H
#define MPG123_LINUX_H

#include <stdlib.h>
#include <sys/types.h>

#define MPG123_NO_CONFIGURE
#include "../../src/libmpg123/mpg123.h.in"

#endif