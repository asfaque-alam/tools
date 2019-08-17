#include "StdAfx.h"
#include "WlanForVista.h"
#include <string>
#include "common.h"
#include "OSVersion.h"

CWlanForVista::CWlanForVista(void)
{
	m_hClientHandle = NULL;
	m_dwNegotiatedVersion = NULL;
	m_pInterfaceList = NULL;
	m_pAvailableNetworkList = NULL;
	m_hNotiifcationEvent = NULL;
}

CWlanForVista::~CWlanForVista(void)
{
	if(m_hClientHandle)
	{
		WlanCloseHandle(m_hClientHandle, NULL);
		m_hClientHandle = NULL;
	}
	m_dwNegotiatedVersion = NULL;
	m_pInterfaceList = NULL;
	m_pAvailableNetworkList = NULL;
}

void NotificationCallbackForVista(PWLAN_NOTIFICATION_DATA pNotificationdata, PVOID pContext)
{
	PWLAN_CONNECTION_NOTIFICATION_DATA pData = NULL;

	if(pNotificationdata->NotificationSource == WLAN_NOTIFICATION_SOURCE_ACM)
	{
		switch(pNotificationdata->NotificationCode)
		{
		case wlan_notification_acm_scan_complete:
			{
				SetEvent((HANDLE)pContext);
				break;
			}
		case wlan_notification_acm_scan_fail:
			{
				AfxMessageBox("Network scan failed");
				break;
			}
		case wlan_notification_acm_connection_complete:
			{
				SetEvent((HANDLE)pContext);
				pData = (PWLAN_CONNECTION_NOTIFICATION_DATA)pNotificationdata->pData;
				
				break;
			}
		case wlan_notification_acm_disconnected:
			{
				SetEvent((HANDLE)pContext);
				pData = (PWLAN_CONNECTION_NOTIFICATION_DATA)pNotificationdata->pData;
				break;
			}
		case wlan_notification_acm_connection_attempt_fail:
			{
				SetEvent((HANDLE)pContext);
				AfxMessageBox("Connection attempt failed");
				pData = (PWLAN_CONNECTION_NOTIFICATION_DATA)pNotificationdata->pData;
				break;
			}
		}
	}
}

PWLAN_AVAILABLE_NETWORK_LIST CWlanForVista::SiteSurvey(GUID InterfaceGUID)
{
	PWLAN_AVAILABLE_NETWORK_LIST pAvailableNetworkList = NULL;

	try
	{
		ResetEvent(m_hNotiifcationEvent);

		DWORD dwRet = WlanScan(m_hClientHandle,
				&InterfaceGUID,
				NULL,
				NULL,
				NULL);
		if(dwRet != ERROR_SUCCESS)
		{
			throw std::exception("Wlan scan failed");
		}

		WaitForSingleObject(m_hNotiifcationEvent, 10000);


		
		if(WlanGetAvailableNetworkList(m_hClientHandle,
									&InterfaceGUID,
									WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_ADHOC_PROFILES|
									WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_MANUAL_HIDDEN_PROFILES,
									NULL,
									&pAvailableNetworkList) != ERROR_SUCCESS)
		{
			throw std::exception("Available network list call failed!!!");
		}
	}
	catch(std::exception& e)
	{
		AfxMessageBox(e.what());
		return NULL;
	}

	return pAvailableNetworkList;
}
BOOL CWlanForVista::OpenHandle()
{
	try
	{
		if(NULL == m_hClientHandle)
		{
			if(WlanOpenHandle(1, NULL, &m_dwNegotiatedVersion, &m_hClientHandle) != ERROR_SUCCESS)
			{
				throw std::exception("Failed! Cannot open handle to Wifi...");
			}
			m_hNotiifcationEvent = CreateEvent(NULL, FALSE, FALSE,NULL);

			if(WlanRegisterNotification(m_hClientHandle,
							WLAN_NOTIFICATION_SOURCE_ALL,
							false,
							(WLAN_NOTIFICATION_CALLBACK)NotificationCallbackForVista,
							m_hNotiifcationEvent,
							NULL,
							NULL) != ERROR_SUCCESS)
			{
				throw std::exception("Failed to Register for notification!!");
			}
		}
	}
	catch(std::exception& e)
	{
		AfxMessageBox(e.what());
		return false;
	}
	return true;
}

BOOL CWlanForVista::EnumInterfaces()
{
	if(WlanEnumInterfaces(m_hClientHandle, NULL, &m_pInterfaceList) != ERROR_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}

PWLAN_INTERFACE_INFO_LIST CWlanForVista::GetNICsList()
{
	return m_pInterfaceList;
}

BOOL CWlanForVista::ConnectToNetwork(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID)
{

	ResetEvent(m_hNotiifcationEvent);
	WLAN_CONNECTION_PARAMETERS connectionParam;

	connectionParam.dot11BssType = pNetwork->dot11BssType;
	connectionParam.pDot11Ssid = &pNetwork->dot11Ssid;
	connectionParam.pDesiredBssidList = NULL;
	connectionParam.dwFlags = 0;
	connectionParam.strProfile = NULL;
	connectionParam.wlanConnectionMode = wlan_connection_mode_discovery_unsecure;

	if(pNetwork->bSecurityEnabled)
	{
		connectionParam.wlanConnectionMode = wlan_connection_mode_discovery_secure;
	}
	if(pNetwork->dwFlags & WLAN_AVAILABLE_NETWORK_HAS_PROFILE)
	{
		connectionParam.strProfile = pNetwork->strProfileName;
		connectionParam.wlanConnectionMode = wlan_connection_mode_profile;
	}

	DWORD dwRet = WlanConnect(m_hClientHandle,
					&interfaceGUID,
					&connectionParam,
					NULL);

	if(dwRet!= ERROR_SUCCESS)
	{
		return FALSE;
	}
	else
	{
		WaitForSingleObject(m_hNotiifcationEvent, 10000);
		return TRUE;
	}
}

BOOL CWlanForVista::DisconnectFromNetwork(GUID interfaceGUID)
{
	ResetEvent(m_hNotiifcationEvent);

	DWORD dwRet = WlanDisconnect(m_hClientHandle,
				&interfaceGUID,
				NULL);

	if(dwRet!= ERROR_SUCCESS)
	{
		return FALSE;
	}
	else
	{
		WaitForSingleObject(m_hNotiifcationEvent, 10000);
		return TRUE;
	}
}

BOOL CWlanForVista::GetProfile(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID, CString& strProfileXML)
{
	LPWSTR  pstrProfileXML = NULL;
	DWORD dwFlags = 0;
	DWORD dwGrantedAccess = 0;

	DWORD dwRet = WlanGetProfile(m_hClientHandle,
		        &interfaceGUID,
				pNetwork->strProfileName,
				NULL,
				&pstrProfileXML,
				&dwFlags,
				&dwGrantedAccess);;

	if(dwRet == ERROR_SUCCESS)
	{
		strProfileXML = pstrProfileXML;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}
BOOL CWlanForVista::DeleteProfile(PWLAN_AVAILABLE_NETWORK pNetwork, 
							GUID interfaceGUID)
{
		

	DWORD dwRet = WlanDeleteProfile(m_hClientHandle,
								&interfaceGUID,
								pNetwork->strProfileName,
								NULL);

	if(dwRet == ERROR_SUCCESS)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL CWlanForVista::SetProfile(CString strProfileXML, GUID interfaceGUID, PWLAN_AVAILABLE_NETWORK pNetwork)
{
	size_t noOfCharConverted;
	size_t maxSizeNeeded;
	size_t sizeConverted;
	int istoredProfilelen = strProfileXML.GetLength() + 1;
	LPWSTR storedProfileW = new WCHAR[istoredProfilelen];

	if(mbstowcs_s(&sizeConverted,
			storedProfileW,
			istoredProfilelen,
			strProfileXML.GetBuffer(),
			strProfileXML.GetLength() +1) != -1);
	{
			
		DWORD dwReasonCode;
		DWORD dwRet = WlanSetProfile(m_hClientHandle,
						&interfaceGUID,
						0,
						storedProfileW,
						0,
						TRUE,
						NULL,
						&dwReasonCode);
		if(dwRet != ERROR_SUCCESS)
		{
			CString strError;
			strError.Format("Error! Set profile failed %d", dwRet);
			AfxMessageBox(strError);
			return false;
		}
	}
	return TRUE;
}

BOOL CWlanForVista::GetProfileList(GUID interfaceGUID, StringList& profileList)
{
	BOOL bSuccess = TRUE;
	PWLAN_PROFILE_INFO_LIST pProfileInfoList;
	DWORD dwRet  = WlanGetProfileList(m_hClientHandle,
								&interfaceGUID,
								NULL,
								&pProfileInfoList);

	if(dwRet == ERROR_SUCCESS)
	{
		size_t numofCharConverted = 0;
		char chProfilename[MAX_PATH] = {0};;

		for(int i = 0; i<pProfileInfoList->dwIndex; i++)
		{
			if(wcstombs_s(&numofCharConverted,
				chProfilename,
				MAX_PATH,
				pProfileInfoList->ProfileInfo[i].strProfileName,
				MAX_PATH))
			{
				profileList.push_back(chProfilename);
			}
			else
			{
				bSuccess = FALSE;
				AfxMessageBox("Wcs To Mbcs failed for GetProfileList");
			}
		}
	}
	else
	{
		CString strError;
		DWORD dwErr = GetLastError();
		strError.Format("GetProfileList failed with Error code: [%d]", dwErr);
		bSuccess = FALSE;
		AfxMessageBox(strError);

	}

	return bSuccess;
}

