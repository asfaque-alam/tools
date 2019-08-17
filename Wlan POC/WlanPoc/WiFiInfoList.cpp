#include "StdAfx.h"
#include "WiFiInfoList.h"

CWiFiInfoList::CWiFiInfoList()
{

}

CWiFiInfoList::~CWiFiInfoList(void)
{
}

NetworkInfoList CWiFiInfoList::GetNetworkInfoList()
{
	return m_networkList;
}

void CWiFiInfoList::Wrap(NetworkInfoList networklist)
{
	m_networkList = networklist;
}
