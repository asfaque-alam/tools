#pragma once
#include "IWlanAdapter.h"
#include "ICmd.h"
#include "IListener.h"
#include "common.h"
#include <string>

class CConnectToNetworkCmd : public ICmd 
{
public:
	CConnectToNetworkCmd(void);
	CConnectToNetworkCmd(IWlanAdapter* pAdaptor);
	~CConnectToNetworkCmd(void);
	BOOL Execute(IListener *pListener = NULL);
	void SetCmdParameter(void* pData);
private:
	static LRESULT ConnectToNetworkThreadProc(LPVOID pParam);

private:
	IWlanAdapter *m_pWifiNetwork;
	CWiFiNetworkInfo* m_pTempNetworkInfo;
	IListener *m_pListener;
	HANDLE m_hConnectToNetworkThread;

	
};
