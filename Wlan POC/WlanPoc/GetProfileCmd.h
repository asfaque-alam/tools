#pragma once
#include "common.h"
#include "IWlanAdapter.h"



class CGetProfileCmd : public ICmd
{
public:
	CGetProfileCmd(void);
	CGetProfileCmd(IWlanAdapter* pWlanNetwork);
	~CGetProfileCmd(void);

	BOOL Execute(IListener *pListener = NULL);
	void SetCmdParameter(void* pData);

private:
	static LRESULT GetProfileThreadProc(LPVOID pParam);

private:
	IWlanAdapter* m_pWifiNetwork;
	CWiFiNetworkInfo *m_pTempNetworkInfo;
	IListener *m_pListener;
	char* m_pData;
};
