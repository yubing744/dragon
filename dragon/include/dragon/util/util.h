#if !defined(Util_H)
#define Util_H

#include "../config/config.h"

#define BeginPackageUtil BeginPackage2(ProjectName,util)
#define EndPackageUtil EndPackage2
#define Util ProjectName::util

BeginPackageUtil

	template<class E>
	interface Iterable;

	template<class E>
	interface Iterator;

	template<class E>
	interface Collection;

	template<class K,class V>
	interface Map;

	template<class K,class V>
	class HashMap;

	template<class E>
	interface List;

	template<class E>
	class ArrayList;

	template<class E>
	class LinkedList;

	template<class E>
	class Stack;

	template<class E>
	class Queue;

	template<class E>
	class PriorityQueue;
	

	template<class E>
	interface Set;

	template<class E>
	class HashSet;

	class TemplateType;
	class Properties;

EndPackageUtil

#include "../lang/lang.h"
#include "../io/io.h"

Import ProjectName::lang;
Import ProjectName::io;

#include "Iterable.h"
#include "Iterator.h"

#include "Collection.h"

#include "Map.h"
#include "HashMap.h"

#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

#include "Set.h"
#include "HashSet.h"

#include "TemplateType.h"
#include "Properties.h"

#endif