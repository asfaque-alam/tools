#pragma once
#include "IWlanAdapter.h"
#include "ICmd.h"
#include "common.h"
#include "WiFiInfoList.h"
#include "IListener.h"

class CSiteSurveyCmd : public ICmd
{
public:
	CSiteSurveyCmd(void);
	CSiteSurveyCmd(IWlanAdapter* pAdaptor);
	~CSiteSurveyCmd(void);
	BOOL Execute(IListener *pListener = NULL);
	void SetCmdParameter(void* pData);

private:
	static LRESULT SiteSurveyThread(LPVOID pParam);
private:
	IWlanAdapter *m_pWifiNetwork;
	NetworkInfoList m_NetworkInfoList;
	HANDLE m_hSitesurveyThread;
	CWiFiInfoList *m_pWifiInfoList;
	IListener *m_pListener;
	void* m_pCmdData;
};
