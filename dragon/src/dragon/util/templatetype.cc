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
 * Description: TemplateType
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/03/31
 **********************************************************************/

#include <dragon/util/TemplateType.h>

Import dragon::util;

TemplateType::TemplateType()
{
	this->argTypes=new ArrayList<P<TemplateType>>();
}

TemplateType::TemplateType(String typeText)
{
	this->argTypes=new ArrayList<P<TemplateType>>();
	this->parser(typeText);
}

void TemplateType::parser(String typeText)
{
	this->rawType=typeText;
	this->argTypes->clear();
	int length=typeText.length();

	int posBegin=0;
	int posEnd=length;
	int posCurrent=posBegin;
	int posComma=-1;

	posCurrent=typeText.indexOf(L'<',posBegin);
	posEnd=typeText.lastIndexOf(L'>',length);

	if(posCurrent<0)
	{
		this->mainType=typeText;
		return;
	}

	this->mainType=typeText.substring(posBegin,posCurrent);

	posBegin=posCurrent+1;

	this->findArg(typeText,posBegin,posCurrent,posComma,posEnd);
}


void TemplateType::findArg(String& typeText,int posBegin,int posCurrent,int posComma,int posEnd)
{
	posCurrent=typeText.indexOf(L'<',posBegin);
	posComma=typeText.indexOf(L',',posBegin);

	if(posComma<0)
	{
		String arg=typeText.substring(posBegin,posEnd);
		this->argTypes->add(new TemplateType(arg));
	}
	else if(posCurrent<0 || posCurrent>posComma)
	{
		String arg=typeText.substring(posBegin,posComma);
		this->argTypes->add(new TemplateType(arg));	

		posBegin=posComma+1;

		this->findArg(typeText,posBegin,posCurrent,posComma,posEnd);
	}
	else
	{
		posCurrent=this->getNextPos(typeText,posCurrent+1,posEnd);
		posComma=typeText.indexOf(L',',posCurrent);

		if(posComma<0)
		{
			String arg=typeText.substring(posBegin,posEnd);
			this->argTypes->add(new TemplateType(arg));		
		}
		else
		{
			String arg=typeText.substring(posBegin,posComma);
			this->argTypes->add(new TemplateType(arg));		

			posBegin=posComma+1;

			this->findArg(typeText,posBegin,posCurrent,posComma,posEnd);
		}
	}
	
}

int TemplateType::getNextPos(String& typeText,int posBegin,int posEnd)
{
	int level=-1;
	int posCurrent=posBegin;
	for(int i=posBegin;i<posEnd;i++)
	{
		Char ch=typeText.charAt(i);
		if(ch==L'<')
		{
			level--;
		}
		else if(ch==L'>')
		{
			level++;
		}
	
		if(level==0)
		{
			posCurrent=i;
			break;
		}
	}

	return posCurrent;
}

String TemplateType::getMainType()
{
	return this->mainType;
}

String TemplateType::getRawType()
{
	return this->rawType;
}

int TemplateType::getArgsCount()
{
	return this->argTypes->size();
}

P<TemplateType> TemplateType::getArgType(int index)
{
	return this->argTypes->get(index);
}