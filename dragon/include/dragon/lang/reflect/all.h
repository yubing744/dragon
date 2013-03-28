#ifndef Lang_Reflect_H
#define Lang_Reflect_H

#include "../../config/config.h"
#include "../gc/gc.h"

#define BeginPackageReflect BeginPackage3(ProjectName,lang,reflect)
#define EndPackageReflect EndPackage3
#define Reflect ProjectName::lang::reflect

Import ProjectName::lang;
Import ProjectName::lang::gc;

BeginPackageReflect

	interface Constructor;
	class Method;
	class Field;
	class Property;
	class Library;
	class DllLibrary;
	class LibraryManager;

EndPackageReflect


#include "../../util/util.h"
#include "../../io/io.h"

Import ProjectName::lang;
Import ProjectName::io;
Import ProjectName::util;

#include "Method.h"
#include "Field.h"
#include "Property.h"
#include "Constructor.h"
#include "Library.h"
#include "DllLibrary.h"
#include "LibraryManager.h"

#define ImplRuntimeGetClass(Type) Class<Object>* getClass(){return (Class<Object>*)new Class<Type>();}
#define ImplGetClassSize(Type)  int getClassSize(){return sizeof(Type);}

#endif