#include <dragon/lang/Arrays.h>

Import dragon::lang;
Char* Arrays::copyOf(const Char* src, int length){
	return Arrays::copyOf(src, length, 1);
}

Char* Arrays::copyOf(const Char* src, int length, int perOffset){
	Char* result = new Char[length];

	for (int i=0; i<length; i+=perOffset){
		result[i] = src[i];
	}

	return result;
}

