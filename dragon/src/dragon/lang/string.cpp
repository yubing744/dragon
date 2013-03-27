#include "String.h"
#include <ctype.h>

Import ProjectName::lang;
Import ProjectName::util::regex;

String::String(){}

String::~String()
{
	if(mstr!=L"")
	{
		mstr.clear();
	}

}

String::String(const Char* value)
{
	if(value!=null)
	{
		mstr=TString(value);
	}
}

String::String(TString value):mstr(value){}

String::String(const String& value)
{
	mstr=value.mstr;
}

String::String(const Char* value, int offset, int count)
{
	int len=String::valueOf(value).length();
	if(offset<0 || offset>=len || offset+count>=len)
	{
		throw IndexOutOfBoundsException();
	}
	mstr=TString(value,offset,count);
}


void String::operator = (const Char*  str)
{
	mstr=TString(str);
}


String& String::operator+(const String& str)
{
	mstr.append(str.mstr);
	return *this;
}

String& String::operator+=(const String& str)
{
	mstr.append(str.mstr);
	return *this;
}

bool String::operator==(const Char* str)
{
	if(this->mstr==str)
	{
		return true;
	}

	return false;
}

bool String::operator==(const String& str)
{
	if(this->mstr==str.mstr)
	{
		return true;
	}

	return false;

}

String::operator TString()
{
	return mstr;
}

String::operator const Char*()
{
	return mstr.c_str();
}


String::operator size_t()
{
	return this->hashCode();
}

size_t String::operator()(const String& str)
{
	int n=str.mstr.size();
	int hc=0;

	for(int i=0;i<n;i++)
	{
		hc+=(str.mstr[i]*(int)Math::pow(31.0,n-i+1));
	}

	return hc;

}

bool String::equals(const Char* str)
{
	return mstr==str;
}

bool String::startsWith(const Char* prefix)
{
	TString temp(prefix);

	if(mstr.substr(0,temp.length())==temp)
	{
		return true;
	}

	return false;
}

bool String::startsWith(const Char* prefix,int toffset)
{
	TString temp(prefix);

	if(mstr.substr(toffset,temp.length())==temp)
	{
		return true;
	}

	return false;
}

bool String::endsWith(String& suffix)
{
	int mlen=mstr.length();
	int slen=suffix.mstr.length();
	
	if(mlen<slen)
	{
		return false;
	}

	if(mstr.substr(mlen-slen,slen)==suffix.mstr)
	{
		return true;
	}

	return false;
}

int String::hashCode()
{
	int n=mstr.length();
	int hc=0;

	for(int i=0;i<n;i++)
	{
		hc+=(mstr[i]*(int)Math::pow(31.0,n-i+1));
	}

	return hc;
}

int String::indexOf(Char ch)
{
	return mstr.find_first_of(ch,0);
}

int String::indexOf(Char ch,int fromIndex)
{
	return mstr.find_first_of(ch,fromIndex);
}

int String::indexOf(const Char* str)
{
	return mstr.find_first_of(str,0);
}

int String::indexOf(CharSequence* s,int fromIndex)
{
	int mlen=this->length();
	int slen=s->length();

	for(int i=fromIndex;i<mlen;i++)
	{
		if(this->charAt(i)==s->charAt(0))
		{
			bool isEque=true;
			for(int j=0;j<slen;j++)
			{
				if(this->charAt(i+j)!=s->charAt(j))
				{
					isEque=false;
					break;
				}
			}

			if(isEque)
			{
				return i;
			}
		}
	}

	return -1;
}
int String::indexOf(CharSequence* s)
{
	return this->indexOf(s,0);
}


int String::indexOf(String& str,int fromIndex)
{
	return mstr.find_first_of(str.mstr,fromIndex);
}

int String::lastIndexOf(Char ch)
{
	return mstr.find_last_of(ch,0);
}

int String::lastIndexOf(Char ch,int fromIndex)
{
	return mstr.find_last_of(ch,fromIndex);
}

int String::lastIndexOf(const Char* str)
{
	return mstr.find_last_of(str,mstr.size());
}

int String::lastIndexOf(const Char* str,int fromIndex)
{
	return mstr.find_last_of(str,fromIndex);
}

String String::substring(int beginIndex)
{
	int len=mstr.length();
	
	if(beginIndex<0 || beginIndex>=len)
	{
		throw IndexOutOfBoundsException();
	}

	return String(mstr.substr(beginIndex,len-beginIndex));
}

String String::substring(int beginIndex,int endIndex)
{
	int len=mstr.length();

	if (endIndex == beginIndex) return String(L"");

	if(beginIndex<0 || beginIndex>=len || beginIndex>endIndex || endIndex<0 || endIndex>len)
	{
		throw IndexOutOfBoundsException();
	}

	return String(mstr.substr(beginIndex,endIndex-beginIndex));
}

String String::subString(int beginIndex)
{
	return substring(beginIndex);
}
String String::subString(int beginIndex,int endIndex)
{
	return substring(beginIndex,endIndex);
}

String& String::concat(String& str)
{
	mstr.append(str.mstr);
	return *this;
}

String& String::append(const Char* str)
{
	mstr.append(str);
	return *this;
}

String& String::append(CharSequence* s)
{
	int slen=s->length();
	Char* temp=new Char[slen+1];

	for(int i=0;i<slen;i++)
	{
		temp[i]=s->charAt(i);
	}

	temp[slen]=0;
	mstr.append(temp);
	delete[] temp;

	return *this;
}

String& String::replace(Char oldChar,Char newChar)
{
	int len=mstr.length();
	for(int i=0;i<len;i++)
	{
		if(mstr[i]==oldChar)
		{
			mstr[i]=newChar;
		}
	}

	return *this;
}

int String::compareTo(String& o)
{
	return mstr.compare(o.mstr);
}

Char String::charAt(int index)
{
	return mstr.at(index);
}

int String::length()
{
	return mstr.length();
}

CharSequence* String::subSequence(int start,int end)
{
	return &this->substring(start,end);
}

String String::toString()
{
	return String(mstr);
}

const Char* String::toCharArray()
{
	//int len=mstr.length();
	//Char* buf=new Char[len+1];

	//for(int i=0;i<len;i++)
	//{
	//	buf[i]=mstr[i];
	//}
	//buf[len]=0;

	//return buf;

	return mstr.c_str();
}

bool String::matches(String regex)
{
	Regexp tempReg(regex);
	MatchResult result = tempReg.MatchExact(this->mstr.c_str());
	return result.IsMatched()!=0;
}

bool String::contains(CharSequence* s)
{
	if(s==null)
	{
		throw NullPointerException();
	}

	int mlen=this->length();
	int slen=s->length();

	for(int i=0;i<mlen;i++)
	{
		if(this->charAt(i)==s->charAt(0))
		{
			bool isEque=true;
			for(int j=0;j<slen;j++)
			{
				if(this->charAt(i+j)!=s->charAt(j))
				{
					isEque=false;
					break;
				}
			}

			if(isEque)
			{
				return true;
			}
		}
	}

	return false;
}

bool String::contains(String s)
{
	int pos=this->mstr.find(s.mstr,0);

	return pos>0?true:false;
}

String& String::replace(CharSequence* target,CharSequence* replacement)
{
	String* temp=new String();
	
	int index1=0,index2=0;
	int len=this->length();
	int tlen=target->length();

	for(;;)
	{
		index2=this->indexOf(target,index1);
		if(index2==-1)
		{
			break;
		}

		temp->append(this->subSequence(index1,index2));
		temp->append(replacement);
		index1=index2+tlen;
		index2=index1;
	}

	temp->append(this->subSequence(index1,len));

	return *temp;
}

String& String::replaceFirst(String& regex,String& replacement)
{
	Regexp tempReg(regex);
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement.mstr.c_str(),-1,1);
	return *new String(result);
}

String& String::replaceFirst(String& regex,const Char* replacement)
{
	Regexp tempReg(regex);
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement,-1,1);
	return *new String(result);
}

String& String::replaceAll(String& regex,String& replacement)
{
	Regexp tempReg(regex);
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement.mstr.c_str(),-1,-1);
	return *new String(result);
}

String& String::replaceAll(String& regex,const Char* replacement)
{
	Regexp tempReg(regex);
	Char* result = tempReg.Replace(this->mstr.c_str(),replacement,-1,-1);
	return *new String(result);
}

Array<String>& String::split(Char ch)
{
	int npart=1;

	int index=0;
	for(;;)
	{
		index=this->indexOf(ch,index);
		if(index==-1)
		{	
			break;
		}
		index++;
		npart++;
	}

	Array<String>& arr=*new Array<String>(npart);

	int index1=0,index2=0;

	for(int i=0;;i++)
	{
		index2=this->indexOf(ch,index1);
		if(index2==-1)
		{	
			arr[npart-1]=this->substring(index1,this->length());
			break;
		}
		
		arr[i]=this->substring(index1,index2);

		index1=index2+1;
		index2=index1;
	}

	return arr;
}

Array<String>& String::split(String reg)
{
	Regexp regexp(reg);

	CContext * pContext = regexp.PrepareMatch(this->mstr.c_str());


	int npart=1;

    MatchResult result = regexp.Match(pContext);

    while( result.IsMatched() )
    {
		npart++;
        result = regexp.Match(pContext);
    }

	Array<String>& arr=*new Array<String>(npart);

	pContext = regexp.PrepareMatch(this->mstr.c_str());
	result = regexp.Match(pContext);

	int index1=0,index2=0;
	int i=0;
    while(result.IsMatched())
    {
		index2=result.GetStart();
		arr[i]=this->substring(index1,index2);
		index1=result.GetEnd();

        result = regexp.Match(pContext);
		i++;
    }

	arr[npart-1]=this->substring(index1,this->length());

    regexp.ReleaseContext(pContext);

	return arr;
}

String& String::toLowerCase()
{
	int len=this->length();

	for(int i=0;i<len;i++)
	{
		mstr[i]=tolower(mstr[i]);
	}

	return *this;
}

String& String::toUpperCase()
{
	int len=this->length();

	for(int i=0;i<len;i++)
	{
		mstr[i]=toupper(mstr[i]);
	}

	return *this;
}

String String::trim()
{
	int start=0;
	int end=this->length();

	if(end <= start) return String(mstr);

	for(int i=0;i<end;i++)
	{
		if(mstr[i]>0x20)
		{
			start=i;
			break;
		}
	}

	for(int i=end-1;i>start;i--)
	{
		if(mstr[i]>0x20)
		{
			end=i+1;
			break;
		}
	}

	return this->substring(start,end);
}


char* String::toMultiByte()
{
	int len=mstr.length();
	char* pMBBuf=new char[len+1];
	pMBBuf[len]=null;
	size_t out;
	wcstombs_s(&out,pMBBuf,len+1,mstr.c_str(),len);
	return pMBBuf;
}

String& String::copyValueOf(const Char* data)
{
	return *new String(data);
}

String& String::copyValueOf(const Char* data,int offset,int count)
{
	return *new String(data,offset,count);
}

String String::format(const Char* format,...)
{
	Char text[256];
	va_list ap;

	va_start(ap, format);
	    vstprintf_s(text,256,format, ap);
	va_end(ap);	

	return String::valueOf(text);
}

String String::format(String& format,...)
{
	Char text[256];
	va_list ap;

	const Char* fmt=format.mstr.c_str();

	va_start(ap, fmt);
	    vstprintf_s(text,256,fmt, ap);
	va_end(ap);	

	return String::valueOf(text);
}

String String::format(const char* format,...)
{
	char text[256];
	va_list ap;

	va_start(ap, format);
	    vsprintf_s(text,256,format, ap);
	va_end(ap);	

	return String::valueOf(text);
}

String String::valueOf(bool b)
{
	if(b)
	{
		return String::valueOf(L"true");
	}

	return String::valueOf(L"false");
}

String String::valueOf(Char c)
{
	return *new String(&c);
}

String String::valueOf(int i)
{
	Char buf[30];
	_ltot_s(i,buf,30,10);
	return String::valueOf(buf);
}

String String::valueOf(long l)
{
	Char buf[30];
	_ltot_s(l,buf,30,10);
	return String::valueOf(buf);
}

String String::valueOf(float f)
{
	return String::valueOf((double)f);
}

String String::valueOf(double d)
{
	Char buf[30];
	char tbuf[60];
	_gcvt_s(tbuf,30,d,8);
	MultiByteToWideChar(CP_ACP, 0, tbuf, -1, buf, 30); 

	return String::valueOf(buf);
}

String String::valueOf(const Char* data)
{
	return String(data);
}

String String::valueOf(const Char* data,int offset,int count)
{
	return String(data,offset,count);
}

String String::valueOf(const char* value)
{
	int len = MultiByteToWideChar(CP_ACP, 0, value, -1, NULL, 0);
	if (len!=0)
	{
		Char* buf=new Char[len];
		MultiByteToWideChar(CP_ACP, 0, value, -1,buf, len);
		String tempStr=String::valueOf(buf);
		delete [] buf;
		return tempStr;
	}

	return String();
}

