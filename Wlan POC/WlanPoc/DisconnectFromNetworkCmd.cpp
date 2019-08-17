#include "StdAfx.h"
#include "DisconnectFromNetworkCmd.h"
#include "common.h"

CDisconnectFromNetworkCmd::CDisconnectFromNetworkCmd(void)
{
	m_pListener = NULL;
	m_pWifiNetwork = NULL;
	m_pTempNetworkInfo = NULL;
}
CDisconnectFromNetworkCmd::CDisconnectFromNetworkCmd(IWlanAdapter* pWlanNetwork)
{
	m_pListener = NULL;
	m_pWifiNetwork = pWlanNetwork;
	m_pTempNetworkInfo = NULL;
}

CDisconnectFromNetworkCmd::~CDisconnectFromNetworkCmd(void)
{
}

void CDisconnectFromNetworkCmd::SetCmdParameter(void* pData)
{
	if(pData)
	{
		m_pTempNetworkInfo = (CWiFiNetworkInfo*)pData;
	}
}

BOOL CDisconnectFromNetworkCmd::Execute(IListener *pListener)
{
	if(pListener)
	{
		m_pListener = pListener;
	}
	try
	{
		if(m_pTempNetworkInfo == NULL)
		{
			throw std::exception("Invalid network info");
		}
		HANDLE hDisconnectThread = CreateThread(NULL,
					NULL,
					(LPTHREAD_START_ROUTINE)DisconnectThreadProc,
					this,
					CREATE_SUSPENDED,
					NULL);

		if(NULL == hDisconnectThread)
		{
			throw std::exception("thread creation failed!!");
		}

		if(ResumeThread(hDisconnectThread) == 0xFFFFFFFF)
		{
			throw std::exception("Couldn't start thread for disconnect operation");
		}
	}
	catch(std::exception& e)
	{
		return FALSE;
	}


	return TRUE;
}

LRESULT CDisconnectFromNetworkCmd::DisconnectThreadProc(LPVOID pParam)
{
	CDisconnectFromNetworkCmd *pThis = (CDisconnectFromNetworkCmd*)pParam;

	if(pThis->m_pTempNetworkInfo)
	{
		BOOL bRet = pThis->m_pWifiNetwork->DisconnectFromNetwork(pThis->m_pTempNetworkInfo->GetInterfaceGUID());

		if(pThis->m_pListener)
		{
			if(bRet)
			{
				pThis->m_pListener->Notify(NOTIFY_ID_DISCONNECT_SUCCESS, NULL);
			}
			else
			{
				pThis->m_pListener->Notify(NOTIFY_ID_DISCONNECT_FAILED, NULL);
			}
		}
	}

	return 1l;

}