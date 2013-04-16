/*
* Copyright 2010 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef IO_H
#define IO_H

#include <dragon/config.h>

#define BeginPackageIO BeginPackage2(ProjectName,io)
#define EndPackageIO EndPackage2
#define IO ProjectName::io

BeginPackageIO

	class IOException;
	class FileNotFoundException;
	class UnsupportedEncodingException;

	class File;

	class InputStream;
	class FileInputStream;
	class OutputStream;
	class FileOutputStream;

	class Writer;
	class OutputStreamWriter;
	class FileWriter;
	class Reader;
	class InputStreamReader;
	class FileReader;

EndPackageIO

#include "../lang/gc/gc.h"
#include "../lang/lang.h"

Import dragon::lang::gc;
Import dragon::lang;


#include "IOException.h"
#include "FileNotFoundException.h"
#include "UnsupportedEncodingException.h"

#include "File.h"

#include "InputStream.h"
#include "FileInputStream.h"

#include "OutputStream.h"
#include "FileOutputStream.h"

#include "Writer.h"
#include "OutputStreamWriter.h"
#include "FileWriter.h"

#include "Reader.h"
#include "InputStreamReader.h"
#include "FileReader.h"

#endif
