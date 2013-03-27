#include "Manifest.h"

Import OSGIInternal;

Manifest::Manifest()
{
	this->entries = new HashMap<String,String>();
}

Manifest::Manifest(P<File> file)
{
	this->entries = new HashMap<String,String>();
	this->setFile(file);

}

void Manifest::setFile(P<File> file)
{
	this->file = file;
	parseFile();
}

void Manifest::parseFile()
{
	P<Reader> reader = new FileReader(this->file);

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

void Manifest::addEnity(String entity)
{
	int pos = entity.indexOf(L':');
	if( pos > 0 && pos < entity.length()-1 )
	{
		this->entries->put(entity.substring(0,pos),entity.substring(pos+1,entity.length()).trim());
	}
	else if (pos == entity.length()-1)
	{
		this->entries->put(entity.substring(0,pos),String(L""));
	}
}

P<Map<String,String>> Manifest::getEntries()
{
	return this->entries;
}