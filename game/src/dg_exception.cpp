#include "dg_exception.h"


DGException::DGException(void)
{
}

DGException::DGException(char* msg){
	this->message = msg;
}

DGException::~DGException(void)
{
}
