#include "File.h"
#include <io.h>
#include <direct.h>
#include <sys/stat.h>


Import ProjectName::lang;
Import ProjectName::io;

File::File(const Char* pathname)
{
	mpPathName=new String(pathname);
}

File::File(P<String> pathname)
{
	mpPathName=pathname;
}

bool File::mkdir()
{
	if(_wmkdir(mpPathName->toCharArray())==0)
	{
		return true;
	}

	return false;
}

bool File::mkdirs()
{
    int index=0;

	bool isBackslash=false;

	index=mpPathName->indexOf(L'/',index);
	if(index>0)
	{
		isBackslash=true;
	}

	index=0;

    while(true)
	{
		if(isBackslash)
		{
			index=mpPathName->indexOf(L'/',index);
		}
		else
		{
			index=mpPathName->indexOf(new String(L"\\"),index);
		}

		if(index>0)
		{
			_wmkdir(mpPathName->substring(0,index).toCharArray());
		}
		else
		{
			break;
		}

		index++;
    }

	return true;
}

bool File::exists()
{
	struct _stat buf;
	int result;
	result=_wstat(mpPathName->toCharArray(),&buf);

	if(result==0)
	{
		return true;
	}

	return false;
}

bool File::isDirectory()
{
	struct _stat buf;
	int result;
	result=_wstat(mpPathName->toCharArray(),&buf);

	if(result!=0)
	{
		return false;
	}

	return ((buf.st_mode & S_IFDIR)!=0);
}

bool File::isHidden()
{
	return false;
}

bool File::del()
{
	if(_wrmdir(mpPathName->toCharArray())==0)
	{
		return true;
	}

	return false;
}

bool File::remove()
{
	if(_wrmdir(mpPathName->toCharArray())==0)
	{
		return true;
	}

	return false;
}

bool File::isFile() throw(SecurityException)
{
	if(exists())
	{
		return false;
	}

	if(isDirectory())
	{
		return false;
	}

	return true;
}

Long File::length()
{
	struct _stat buf;
	int result;
	result=_wstat(mpPathName->toCharArray(),&buf);

	if(result==0)
	{
		return buf.st_size;
	}

	return 0;
}

bool File::canExecute()
{
	struct _stat buf;
	int result;
	result=_wstat(mpPathName->toCharArray(),&buf);

	if(result!=0)
	{
		return false;
	}

	return ((buf.st_mode & S_IEXEC)!=0);
}

bool File::canRead()
{

	struct _stat buf;
	int result;
	result=_wstat(mpPathName->toCharArray(),&buf);

	if(result!=0)
	{
		return false;
	}

	return ((buf.st_mode & S_IREAD)!=0);
}

bool File::canWrite()
{
	struct _stat buf;
	int result;
	result=_wstat(mpPathName->toCharArray(),&buf);

	if(result!=0)
	{
		return false;
	}

	return ((buf.st_mode & S_IWRITE)!=0);
}

void File::deleteOnExit()
{

}

bool File::createNewFile()
{
	if(!mkdirs())
	{
		return false;
	}

	FILE *file;

	if(_wfopen_s(&file,mpPathName->toCharArray(), L"w")!=0)
	{
		return false;
	}

	if (file)
	{
        if(fclose(file)!=0)
		{
			return false;
		}
	}

	return true;
}

bool File::renameTo(File& dest)
{
	if(_wrename(mpPathName->toCharArray(),dest.mpPathName->toCharArray())==0)
	{
		return true;
	}

	return false;
}

P<Array<String>> File::list(String filter)
{
	P<String> dirPath=new String();

	if(this->isDirectory())
	{
		dirPath->append(mpPathName->toCharArray());
	}
	else
	{
		dirPath->append(this->getParent());
	}

	dirPath->append(L"\\");
	dirPath->append(filter);

	struct _wfinddata64i32_t fdata;
	intptr_t hFile;

	int fileCount=0;

	if((hFile=_wfindfirst(dirPath->toCharArray(),&fdata))==-1)
	{
		return new Array<String>();
	}

	do
	{
		if(wcscmp(fdata.name,L".")==0 || wcscmp(fdata.name,L"..")==0)
		{
			continue;
		}

		fileCount++;
	}
	while(_wfindnext( hFile,&fdata) == 0);

	_findclose(hFile);

	P<Array<String>> fileList=new Array<String>(fileCount);
	fileCount=0;

	if((hFile=_wfindfirst(dirPath->toCharArray(),&fdata))==-1)
	{
		return new Array<String>();
	}

	do
	{	
		if(wcscmp(fdata.name,L".")==0 || wcscmp(fdata.name,L"..")==0)
		{
			continue;
		}

		fileList->set(fileCount,fdata.name);
		fileCount++;
	}
	while(_wfindnext( hFile,&fdata) == 0);

	_findclose(hFile);

	return fileList;
}

P<Array<String>> File::list()
{
	return list(L"*.*");
}


P<Array<P<File>>> File::listFiles(String filter)
{
	P<Array<String>> fl=this->list(filter);
	int len=fl->size();

	P<Array<P<File>>> afl=new Array<P<File>>(len);

	
	String dirPath;
	if(this->isDirectory())
	{
		dirPath.append(mpPathName->toCharArray());
	}
	else
	{
		dirPath.append(this->getParent());
	}

	for(int i=0;i<len;i++)
	{
		String temp(dirPath);
		temp.append(L"\\");
		temp.append(fl->get(i));
		afl->set(i,new File(temp));
	}

	return afl;

}


P<Array<P<File>>> File::listFiles()
{
	return listFiles(L"*.*");
}

String File::getName()
{
	int index=0;
	int lastPos=mpPathName->length();

	index=mpPathName->lastIndexOf(L"\\",lastPos);

	if(index>0)
	{
		return mpPathName->substring(index+1,lastPos);
	}

	index=0;
	index=mpPathName->lastIndexOf(L"/",lastPos);
	
	if(index>0)
	{
		return mpPathName->substring(index+1,lastPos);
	}

	return String(*mpPathName);
}

String File::getPath()
{
	return *mpPathName;
}

String File::getParent()
{
	int index=0;
	int lastPos=mpPathName->length();

	index=mpPathName->lastIndexOf(L"\\",lastPos);

	if(index>0)
	{
		return mpPathName->substring(0,index);
	}

	index=0;
	index=mpPathName->lastIndexOf(L"/",lastPos);
	
	if(index>0)
	{
		return mpPathName->substring(0,index);
	}

	return String();
}

P<File> File::getParentFile()
{
	return new File(this->getParent());
}

bool File::isAbsolute()
{
	if(mpPathName->substring(2).startsWith(L"\\") || mpPathName->startsWith(L"\\"))
	{
		return true;
	}

	if(mpPathName->substring(2).startsWith(L"\\\\") || mpPathName->startsWith(L"\\\\"))
	{
		return true;
	}

	if(mpPathName->substring(2).startsWith(L"/") || mpPathName->startsWith(L"/"))
	{
		return true;
	}

	if(mpPathName->substring(2).startsWith(L"//") || mpPathName->startsWith(L"//"))
	{
		return true;
	}

	return false;
}

String File::getAbsolutePath()
{
	if(isAbsolute())
	{
		return String(mpPathName->toCharArray());
	}

	Char* pResult=_wgetcwd(NULL,0);

	if(pResult!=null)
	{
		P<String> path=new String(pResult);
		path->append(L"\\").append(mpPathName->toCharArray());
		return String(*path);
	}

	return String();
}

P<File> File::getAbsoluteFile()
{
	return new File(this->getAbsolutePath());
}

String File::getCanonicalPath()
{
	DWORD retval=0;
	Char buffer[4096]=L""; 
    Char* lpPart[4096]={NULL};

	retval = GetFullPathName(getAbsolutePath().toCharArray(),4096,buffer,lpPart);
	
	if(retval!=0)
	{
		return String(buffer);
	}

	return String();
}