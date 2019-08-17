#pragma once
#include "StdAfx.h"
#include "ConnectToNetworkCmd.h"

CConnectToNetworkCmd::CConnectToNetworkCmd(void)
{
}

CConnectToNetworkCmd::CConnectToNetworkCmd(IWlanAdapter* pWlanNetwork)
{
	m_pListener = NULL;
	m_pTempNetworkInfo = NULL;
	m_pWifiNetwork = pWlanNetwork;
	m_hConnectToNetworkThread = NULL;
}
CConnectToNetworkCmd::~CConnectToNetworkCmd(void)
{
}

void CConnectToNetworkCmd::SetCmdParameter(void* pData)
{
	if(pData)
	{
		m_pTempNetworkInfo = (CWiFiNetworkInfo*)pData;
	}
}

BOOL CConnectToNetworkCmd::Execute(IListener* pListener)
{
	if(pListener)
	{
		m_pListener = pListener;
	}
	try
	{
		if(NULL == m_pTempNetworkInfo)
		{
			throw std::exception("Invalid network info!!");
		}

		m_hConnectToNetworkThread = CreateThread(NULL,
											NULL,
											(LPTHREAD_START_ROUTINE)&ConnectToNetworkThreadProc,
											this,
											CREATE_SUSPENDED,
											NULL);

		if(m_hConnectToNetworkThread)
		{
			if(ResumeThread(m_hConnectToNetworkThread)== 0xFFFFFFFF)
			{
				throw std::exception("Thread not started successfully: m_hConnectToNetworkThread!!");
			}
		}
		else
		{
			throw std::exception("Thread not created: m_hConnectToNetworkThread!!");
		}
	}
	catch(std::exception& e)
	{
		return FALSE;
	}
	return TRUE;
}

LRESULT CConnectToNetworkCmd::ConnectToNetworkThreadProc(LPVOID pParam)
{
	CConnectToNetworkCmd *pThis = (CConnectToNetworkCmd*)pParam;

	BOOL bSuccess = pThis->m_pWifiNetwork->ConnectToNetwork(pThis->m_pTempNetworkInfo->GetNetwork(), 
								pThis->m_pTempNetworkInfo->GetInterfaceGUID());


	if(pThis->m_pListener)
	{
		if(bSuccess)
		{
			pThis->m_pListener->Notify(NOTIFY_ID_CONNECT_SUCCESS, NULL);
		}
		else
		{
			pThis->m_pListener->Notify(NOTIFY_ID_CONNECT_FAILED, NULL);
		}
	}
	return 1;
}

