#include "StdAfx.h"
#include "DeleteProfileCmd.h"

CDeleteProfileCmd::CDeleteProfileCmd(void)
{
}

CDeleteProfileCmd::~CDeleteProfileCmd(void)
{
}
CDeleteProfileCmd::CDeleteProfileCmd(IWlanAdapter* pWlanNetwork)
{
	m_pWifiNetwork = pWlanNetwork;
	m_pListener = NULL;
}

BOOL CDeleteProfileCmd::Execute(IListener *pListener)
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
									(LPTHREAD_START_ROUTINE )&DeleteProfileThreadProc,
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
void CDeleteProfileCmd::SetCmdParameter(void* pData)
{
	if(pData)
	{
		m_pTempNetworkInfo = (CWiFiNetworkInfo*)pData;
	}

}

LRESULT CDeleteProfileCmd::DeleteProfileThreadProc(LPVOID pParam)
{
	CDeleteProfileCmd *pThis = (CDeleteProfileCmd*)pParam;

	BOOL bSuccess = pThis->m_pWifiNetwork->DeleteProfile(pThis->m_pTempNetworkInfo->GetNetwork(),
								pThis->m_pTempNetworkInfo->GetInterfaceGUID());

	if(pThis->m_pListener)
	{
		if(bSuccess)
		{
			pThis->m_pListener->Notify(NOTIFY_ID_DELETEPROFILE_SUCCESS, NULL);
		}
		else
		{
			pThis->m_pListener->Notify(NOTIFY_ID_DELETEPROFILE_FAILED, NULL);
		}
	}


	return 1;
}

