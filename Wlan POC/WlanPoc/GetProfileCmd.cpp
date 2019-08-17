#include "StdAfx.h"
#include "GetProfileCmd.h"

CGetProfileCmd::CGetProfileCmd(void)
{
}
CGetProfileCmd::CGetProfileCmd(IWlanAdapter* pWlanNetwork)
{
	m_pWifiNetwork = pWlanNetwork;
	m_pListener = NULL;
	m_pData = NULL;
}

CGetProfileCmd::~CGetProfileCmd(void)
{
}

BOOL CGetProfileCmd::Execute(IListener *pListener)
{
	if(pListener)
	{
		m_pListener = pListener;
	}
	try
	{
		//1. Site survey thread
		HANDLE hGetProfileThread = CreateThread(NULL, 
									NULL,
									(LPTHREAD_START_ROUTINE )&GetProfileThreadProc,
									this,
									CREATE_SUSPENDED,
									NULL);

		if(hGetProfileThread)
		{
			if(ResumeThread(hGetProfileThread) == 0xFFFFFFFF)
			{
				AfxMessageBox("resume thread failed");
				throw std::exception("resume GetProfileThread failed!!!");
			}
		}
		else
		{
			throw std::exception("GetProfileThread Thread creation failed!!!");
		}
	}
	catch(std::exception& e)
	{
		return FALSE;
	}

	return TRUE;
}
void CGetProfileCmd::SetCmdParameter(void* pData)
{
	if(pData)
	{
		m_pTempNetworkInfo = (CWiFiNetworkInfo*)pData;
	}

}

LRESULT CGetProfileCmd::GetProfileThreadProc(LPVOID pParam)
{
	CGetProfileCmd *pThis = (CGetProfileCmd*)pParam;
	CString strProfileXML;

	BOOL bSuccess = pThis->m_pWifiNetwork->GetProfile(pThis->m_pTempNetworkInfo->GetNetwork(),
		                           pThis->m_pTempNetworkInfo->GetInterfaceGUID(),
								   strProfileXML);

	if(bSuccess)
	{
		int ProfileLen = strProfileXML.GetLength() + 1;
		pThis->m_pData = (char*)malloc(sizeof(char)*ProfileLen);
		memset(pThis->m_pData, 0, ProfileLen);

		memcpy((void*)pThis->m_pData, (void*)strProfileXML.GetBuffer(),ProfileLen);

		//pThis->m_pData = (void*)strProfileXML.GetBuffer();
		pThis->m_pListener->Notify(NOTIFY_ID_GETPROFILE_SUCCESS, pThis->m_pData );
	}
	else
	{
		pThis->m_pListener->Notify(NOTIFY_ID_GETPROFILE_FAILED, NULL);
	}
	return 1;
}
