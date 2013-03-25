#include "Properties.h"

Import Util;

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