#include "System.h"

Import ProjectName::lang;

System::System(){}


void System::load(String filename)
{
	LM::GetInstance()->load(filename);
}

