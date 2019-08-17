#pragma once
#include "IListener.h"

class ICmd
{
public:
	virtual ~ICmd(){}
	virtual void SetCmdParameter(void* pData) = 0;
	virtual BOOL Execute(IListener *pListener = NULL) = 0;
};