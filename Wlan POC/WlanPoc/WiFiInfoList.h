#pragma once
#include "common.h"

class CWiFiInfoList
{
public:
	CWiFiInfoList();
public:
	~CWiFiInfoList(void);
	NetworkInfoList GetNetworkInfoList();
	void Wrap(NetworkInfoList networklist);

private:
	NetworkInfoList m_networkList;
};
