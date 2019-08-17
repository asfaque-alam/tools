#pragma once
#include "stdafx.h"

class IListener
{
public:
	virtual ~IListener(){}
	virtual void Notify(CString NotifyID, void* pData) = 0;

};