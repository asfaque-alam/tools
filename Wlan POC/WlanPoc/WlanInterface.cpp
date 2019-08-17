#include "StdAfx.h"
#include "WlanInterface.h"
#include <string>
#include "WlanForXP.h"
#include "WlanForVista.h"
#include "OSVersion.h"
#include "ConnectToNetworkCmd.h"
#include "SiteSurveyCmd.h"
#include "DisconnectFromNetworkCmd.h"
#include "GetProfileCmd.h"
#include "DeleteProfileCmd.h"
#include "CreateProfileFromXML.h"


CWlanInterface* CWlanInterface::m_pWlanInterface = NULL;
CWlanInterface::CWlanInterface(void)
{
	m_pWifiNetwork = NULL;
}

CWlanInterface::~CWlanInterface(void)
{

	if(m_pWifiNetwork)
	{
		delete m_pWifiNetwork;
		m_pWifiNetwork = NULL;
	}

	m_ListenerList.clear();


	CmdMap::iterator itr;
	for(itr = m_cmdMap.begin(); itr != m_cmdMap.end(); itr++)
	{
		ICmd *pCmd = itr->second;

		if(pCmd)
		{
			delete pCmd;
			pCmd = NULL;
		}
	}
	m_cmdMap.clear();

}
//Singleton Instance
CWlanInterface* CWlanInterface::GetInstance(void)
{
	if(m_pWlanInterface == NULL)
	{
		m_pWlanInterface = new CWlanInterface();
	}

	return m_pWlanInterface;
}

void CWlanInterface::DestroyInstance()
{
	if(m_pWlanInterface)
	{
		delete m_pWlanInterface;
		m_pWlanInterface = NULL;
	}
	
}

BOOL CWlanInterface::Initialize(void)
{
	try
	{
		if(COSVersion::GetOSVersion() == WINDOWS_XP)
		{
			m_pWifiNetwork = new CWlanForXP();
		}
		else if(COSVersion::GetOSVersion() == WINDOWS_VISTA)
		{
			m_pWifiNetwork = new CWlanForVista();
		}

		if(!m_pWifiNetwork->OpenHandle())
		{
			throw std::exception("Open handle failed");
		}
		if(!m_pWifiNetwork->EnumInterfaces())
		{
			throw std::exception("No NICs Found");
		}
	}
	catch(std::exception& e)
	{
		AfxMessageBox(e.what());
		return false;
	}
	return true;
}

void CWlanInterface::RegisterListener(IListener* pListener)
{
	m_ListenerList.push_back(pListener);
}


ICmd* CWlanInterface::GetCmd(CString csCmdID)
{
	CmdMap::iterator itr = m_cmdMap.find(csCmdID.GetBuffer());
	if(itr != m_cmdMap.end())
	{
		ICmd *pCmdAlready = itr->second;
		delete pCmdAlready;
		pCmdAlready = NULL;

		m_cmdMap.erase(itr);
	}

	ICmd *pCmd = NULL;
	if(csCmdID == CMD_SITESURVEY)
	{
		pCmd = new CSiteSurveyCmd(m_pWifiNetwork);
	}
	else if(csCmdID == CMD_CONNECT)
	{
		pCmd = new CConnectToNetworkCmd(m_pWifiNetwork);
	}
	else if(csCmdID == CMD_DISCONNECT)
	{
		pCmd = new CDisconnectFromNetworkCmd(m_pWifiNetwork);
	}
	else if(csCmdID == CMD_GETPROFILE)
	{
		pCmd = new CGetProfileCmd(m_pWifiNetwork);
	}
	else if(csCmdID == CMD_DELETEPROFILE)
	{
		pCmd = new CDeleteProfileCmd(m_pWifiNetwork);
	}
	else if(csCmdID == CMD_CREATE_PROFILE)
	{
		pCmd = new CCreateProfileFromXML(m_pWifiNetwork);
	}

	m_cmdMap[csCmdID.GetBuffer()] = pCmd;

	return pCmd;
}


BOOL CWlanInterface::IsNICAvailable(void)
{
	return false;
}

void CWlanInterface::UnInitialize()
{

}

void CWlanInterface::ClearNetworkList()
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
}