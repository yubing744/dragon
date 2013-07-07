/*
* Copyright 2013 the original author or authors.
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

/**********************************************************************
 * File:        TemplateType.cc
 * Description: like java Properties class
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/03/31
 **********************************************************************/

#include <dragon/util/Properties.h>

Import dragon::util;

Properties::Properties()
{
	this->props = new HashMap<String,String>();
}

String Properties::getProperty(String key)
{
	return this->props->get(key);
}

P<List<String>> Properties::propertyNames()
{
	P<List<String>> propNames = new ArrayList<String>();

	P<Iterator<P<Map<String,String>::Entry>>> it=props->iterator();

	while(it->hasNext())
	{
		P<Map<String,String>::Entry> entry=it->next();
		String propName=entry->getKey();

		propNames->add(propName);
	}

	return propNames;
}

void Properties::load(P<Reader> reader) throw(IOException)
{
	Char buf[256];
	String content;
	int readNum = 0;

	while((readNum = reader->read(buf,256)) > 0)
	{
		content.append(new String(buf,0,readNum));
	}
	
	reader->close();

	Array<String> strArrays = content.split(L"\n");

	String entity;
	bool newOne = false;

	for(int i = 0; i < strArrays.size(); ++i)
	{
		if(strArrays.get(i).equals(L"")) continue;

		newOne = !strArrays.get(i).startsWith(L" ");
		String temp = strArrays.get(i).trim();
		
		if(temp.length() > 0 && !newOne)
		{
			entity.append(temp);
			newOne = true;
		}
		else
		{
			if(entity.length()>0)
			{
				addEnity(entity);
			}
			
			entity = temp;
		}
	}

	if(entity.length()>0)
	{
		addEnity(entity);
	}
}

void Properties::addEnity(String entity)
{
	int pos = entity.indexOf(L'=');

	if( pos > 0 )
	{
		String key = entity.substring(0,pos).trim();

		String value = L"";

		try
		{
			value = entity.substring(pos+1,entity.length()).trim();
		}
		catch(...)
		{
			value = L"";
		}

		this->props->put(key, value);
	}
}