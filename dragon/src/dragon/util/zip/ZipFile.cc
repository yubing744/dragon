#include "ZipFile.h"

Import Zip;


ZipFile::ZipFile(String name, String password, int mode)
{
	this->password = password;
	this->pathName = name;

	if (mode == 1)
	{
		this->hZip = OpenZip(this->pathName,this->password.toMultiByte());
	}
	else
	{
		this->hZip = CreateZip(this->pathName,this->password.toMultiByte());
	}
}

P<ZipFile> ZipFile::Create(String name)
{
	return new ZipFile(name, L"", 0);
}

P<ZipFile> ZipFile::Open(String name)
{
	return new ZipFile(name, L"", 1);
}

P<ZipFile> ZipFile::Create(String name, String password)
{
	return new ZipFile(name, password, 0);
}

P<ZipFile> ZipFile::Open(String name, String password)
{
	return new ZipFile(name, password, 1);
}

void ZipFile::setUnzipBaseDir(String dir)
{
	SetUnzipBaseDir(this->hZip , dir);
}

void ZipFile::addFile(String path, String file)
{
	P<File> theFile = new File(file);

	if (theFile->isDirectory())
	{
		P<Array<P<File>>> files = theFile->listFiles();
		int fileNum = files->size();

		for ( int i = 0; i < fileNum; ++i )
		{	
			P<File> innerFile = files->get(i);

			String zipDir = String(path) +String(L"/") + innerFile->getName();
			addFile( zipDir, innerFile->getAbsolutePath() );
		}
	}
	else
	{
		ZipAdd(this->hZip,path, file);
	}
}


void ZipFile::unZip(P<ZipEntry> entry, String position)
{
	UnzipItem(this->hZip, entry->getIndex(), position);
}

void ZipFile::unZipTo(String position)
{
	this->setUnzipBaseDir(position);

	P<List<P<ZipEntry>>> zipEntrys = this->entries();

	for ( int i = 0; i < zipEntrys->size(); ++i )
	{
		P<ZipEntry> zipEntry = zipEntrys->get(i);
		this->unZip(zipEntry, zipEntry->getName());
	}
}

P<ZipEntry> ZipFile::getEntry(String name)
{
	P<ZipEntry> zipEntry = null;

	ZIPENTRY ze;
	int index = -1;
	ZRESULT result = FindZipItem(this->hZip,name,true,&index,&ze); 

	if (result == ZR_OK && index != -1)
	{
		zipEntry = new ZipEntry(ze);
	}

	return zipEntry;
}

P<InputStream> ZipFile::getInputStream(P<ZipEntry> entry) throw(IOException)
{
	int index = entry->getIndex();

	UnzipItem(this->hZip, index, entry->getName());
	return null;
}

String ZipFile::getName()
{
	return String(pathName);
t }

P<List<P<ZipEntry>>> ZipFile::entries()
{
	P<List<P<ZipEntry>>> zipEntrys = new ArrayList<P<ZipEntry>>();

	P<ZipEntry> zipEntry = null;
	int numitems = size();

	for (int zi=0; zi<numitems; zi++)
	{
		ZIPENTRY ze; 

		if (GetZipItem(this->hZip,zi,&ze) == ZR_OK)
		{
			zipEntry = new ZipEntry(ze);
			zipEntrys->add(zipEntry);
		}
	}

	return zipEntrys;
}

int ZipFile::size()
{
	ZIPENTRY ze; 
	GetZipItem(this->hZip,-1,&ze); 
	return ze.index;
}

void ZipFile::close() throw(IOException)
{
	CloseZip(this->hZip);
}