#include "StdAfx.h"
#include "SiteSurveyCmd.h"

CSiteSurveyCmd::CSiteSurveyCmd(void)
{
}

CSiteSurveyCmd::CSiteSurveyCmd(IWlanAdapter* pWlanNetwork)
{
	m_pCmdData = NULL;
	m_pWifiNetwork = pWlanNetwork;
	m_hSitesurveyThread = NULL;
	m_pWifiInfoList = new CWiFiInfoList();
}

CSiteSurveyCmd::~CSiteSurveyCmd(void)
{
	NetworkInfoList::iterator itr;

	for(itr = m_NetworkInfoList.begin(); itr != m_NetworkInfoList.end(); itr++)
	{
		CWiFiNetworkInfo *pNetworkInfo = *itr;
		
		if(pNetworkInfo)
		{
			delete pNetworkInfo;
			pNetworkInfo = NULL;
		}
	}

	m_NetworkInfoList.clear();

	if(m_pWifiInfoList)
	{
		delete m_pWifiInfoList;
		m_pWifiInfoList = NULL;
	}
}

void CSiteSurveyCmd::SetCmdParameter(void* pData)
{
	if(pData)
	{
		m_pCmdData = pData;
	}
}
BOOL CSiteSurveyCmd::Execute(IListener* pListener)
{
	if(pListener)
	{
		m_pListener = pListener;
	}
	try
	{
		//1. Site survey thread
		m_hSitesurveyThread = CreateThread(NULL, 
									NULL,
									(LPTHREAD_START_ROUTINE )&SiteSurveyThread,
									this,
									CREATE_SUSPENDED,
									NULL);

		if(m_hSitesurveyThread)
		{
			if(ResumeThread(m_hSitesurveyThread) == 0xFFFFFFFF)
			{
				AfxMessageBox("resume thread failed");
				throw std::exception("resume SiteSurveyThread failed!!!");

			}
		}
		else
		{
			throw std::exception("SiteSurveyThread Thread creation failed!!!");
		}
	}
	catch(std::exception& e)
	{
		return FALSE;
	}

	return TRUE;
}

LRESULT CSiteSurveyCmd::SiteSurveyThread(LPVOID pParam)
{
	CSiteSurveyCmd *pThis = (CSiteSurveyCmd*)pParam;
	BOOL bSuccess = true;

	try
	{

		PWLAN_INTERFACE_INFO_LIST pInterfaceList = pThis->m_pWifiNetwork->GetNICsList();

		if(pInterfaceList == NULL)
		{
			throw std::exception("No Network adapter found");
		}

		if(pInterfaceList->dwNumberOfItems <= 0)
		{
			throw std::exception("No Network adapter found");
		}

		for(DWORD nNICList = 0; pInterfaceList->dwNumberOfItems > nNICList; nNICList++)
		{
			
			GUID interfaceGuid = pInterfaceList->InterfaceInfo[nNICList].InterfaceGuid;

			PWLAN_AVAILABLE_NETWORK_LIST pAvailableNetwork = pThis->m_pWifiNetwork->SiteSurvey(interfaceGuid);

			if(NULL == pAvailableNetwork)
			{
				throw std::exception("No available found");
			}

			for(DWORD index = 0; pAvailableNetwork->dwNumberOfItems > index; index++)
			{
				CWiFiNetworkInfo *pNetworkInfo = new CWiFiNetworkInfo(&pAvailableNetwork->Network[index]);
				pNetworkInfo->SetInterfaceGUID(interfaceGuid);
				pThis->m_NetworkInfoList.push_back(pNetworkInfo);
			}
		}
	}
	catch(std::exception& e)
	{
		bSuccess = false;
	}

	if(pThis->m_pWifiInfoList)
	{
		pThis->m_pWifiInfoList->Wrap(pThis->m_NetworkInfoList);
	}

	if(bSuccess)
	{
		pThis->m_pListener->Notify(NOTIFY_ID_SITESURVEY_SUCCESS, (void*)pThis->m_pWifiInfoList);
	}
	else
	{
		pThis->m_pListener->Notify(NOTIFY_ID_SITESURVEY_FAILED, NULL);
	}

	return 1;
}


