#include "ZipEntry.h"

Import Zip;

ZipEntry::ZipEntry(){}

ZipEntry::ZipEntry(ZIPENTRY _zipEntry)
{
	this->m_zipEntry = _zipEntry;
}

String ZipEntry::getName()
{
	return String(m_zipEntry.name);
}

long ZipEntry::getSize()
{
	return m_zipEntry.comp_size;
}

bool ZipEntry::isDirectory()
{
	if (m_zipEntry.attr & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}

	return false;
}

int ZipEntry::getIndex()
{
	return m_zipEntry.index;
}
