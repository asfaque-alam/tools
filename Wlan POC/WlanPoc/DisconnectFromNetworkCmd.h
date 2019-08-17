#pragma once
#include "ICmd.h"
#include "IWlanAdapter.h"
#include "WiFiNetworkInfo.h"

class CDisconnectFromNetworkCmd : public ICmd
{
public:
	CDisconnectFromNetworkCmd(void);
	CDisconnectFromNetworkCmd(IWlanAdapter* pAdaptor);
public:
	~CDisconnectFromNetworkCmd(void);

	 void SetCmdParameter(void* pData);
	 BOOL Execute(IListener *pListener = NULL);

private:
	static LRESULT DisconnectThreadProc(LPVOID pParam);


private:
	IListener *m_pListener;
	IWlanAdapter* m_pWifiNetwork;
	CWiFiNetworkInfo *m_pTempNetworkInfo;
};
