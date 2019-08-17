#pragma once
#include "common.h"
#include "IWlanAdapter.h"

class CDeleteProfileCmd : public ICmd
{
public:
	CDeleteProfileCmd(void);
	CDeleteProfileCmd(IWlanAdapter* pWlanNetwork);
	~CDeleteProfileCmd(void);

	BOOL Execute(IListener *pListener = NULL);
	void SetCmdParameter(void* pData);

private:
	static LRESULT DeleteProfileThreadProc(LPVOID pParam);

private:
	IWlanAdapter* m_pWifiNetwork;
	CWiFiNetworkInfo *m_pTempNetworkInfo;
	IListener *m_pListener;
};
