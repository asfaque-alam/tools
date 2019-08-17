#pragma once
#include "common.h"

class COSVersion
{
public:
	COSVersion(void);
public:
	~COSVersion(void);
public:
	static OS_VERSION GetOSVersion();
};
