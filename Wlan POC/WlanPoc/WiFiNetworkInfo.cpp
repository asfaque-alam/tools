#include "StdAfx.h"
#include "WiFiNetworkInfo.h"
#include "common.h"

CWiFiNetworkInfo::CWiFiNetworkInfo(void)
{
}

CWiFiNetworkInfo::CWiFiNetworkInfo(PWLAN_AVAILABLE_NETWORK pNetwork)
{
	m_pTempNetwork = pNetwork;
	m_csProfileName       = pNetwork->strProfileName;
	m_csSSID              = pNetwork->dot11Ssid.ucSSID;
	//m_csAuthentication    = pNetwork->dot11DefaultAuthAlgorithm

	//Connection Type
	switch(pNetwork->dot11BssType)
	{
		case dot11_BSS_type_infrastructure:
			m_csdBssType = "INFRASTRUCTURE";
			break;
		case dot11_BSS_type_independent:
			m_csdBssType = "ADHOC";
			break;
	}

	//Authentication Method
	switch(pNetwork->dot11DefaultAuthAlgorithm)
	{
		case DOT11_AUTH_ALGO_80211_OPEN:
			m_csAuthentication = STR_AUTHENTICATION_OPEN.c_str(); 
			break;
		case DOT11_AUTH_ALGO_80211_SHARED_KEY:
			m_csAuthentication = STR_AUTHENTICATION_SHARED.c_str();
			break;
		case DOT11_AUTH_ALGO_WPA:
			m_csAuthentication = STR_AUTHENTICATION_WPA.c_str(); 
			break;
		case DOT11_AUTH_ALGO_WPA_PSK:
			m_csAuthentication = STR_AUTHENTICATION_WPAPSK.c_str();
			break;
		case DOT11_AUTH_ALGO_RSNA:
			m_csAuthentication = STR_AUTHENTICATION_WPA2.c_str(); 
			break;
		case DOT11_AUTH_ALGO_RSNA_PSK:
			m_csAuthentication = STR_AUTHENTICATION_WPA2PSK.c_str();
			break;
	}

	switch(pNetwork->dot11DefaultCipherAlgorithm)
	{
		case DOT11_CIPHER_ALGO_NONE:
			m_csEncryption = STR_ENCRYPTION_NONE.c_str();
			break;
		case DOT11_CIPHER_ALGO_WEP:
		case DOT11_CIPHER_ALGO_WEP40:
		case DOT11_CIPHER_ALGO_WEP104:
			m_csEncryption = STR_ENCRYPTION_WEP.c_str();
			break;
		case DOT11_CIPHER_ALGO_TKIP:
			m_csEncryption = STR_ENCRYPTION_TKIP.c_str();
			break;
		case DOT11_CIPHER_ALGO_CCMP:
			m_csEncryption = STR_ENCRYPTION_AES.c_str();
			break;
	}
	
	m_ulSignalQuality	  = pNetwork->wlanSignalQuality;
	m_bNetworkConnectable = pNetwork->bNetworkConnectable;
	m_bSecurityEnable     = pNetwork->bSecurityEnabled;
}

CWiFiNetworkInfo::~CWiFiNetworkInfo(void)
{
	
}

PWLAN_AVAILABLE_NETWORK CWiFiNetworkInfo::GetNetwork()
{
	return m_pTempNetwork;
}

CString CWiFiNetworkInfo::GetSSID()
{
	return m_csSSID;
}
CString CWiFiNetworkInfo::GetProfileName()
{
	return m_csProfileName;
}
CString CWiFiNetworkInfo::GetAuthentication()
{
	return m_csAuthentication;
}
CString CWiFiNetworkInfo::GetConnectionType()
{
	return m_csdBssType;
}
ULONG CWiFiNetworkInfo::GetSignalQuality()
{
	return m_ulSignalQuality;
}
BOOL CWiFiNetworkInfo::IsNetworkConntectable()
{
	return m_bNetworkConnectable;
}
BOOL CWiFiNetworkInfo::IsSecurityEnable()
{
	return m_bSecurityEnable;
}
BOOL CWiFiNetworkInfo::HasProfile()
{
	if(m_pTempNetwork->dwFlags & WLAN_AVAILABLE_NETWORK_HAS_PROFILE)
	{
		return true;
	}
	return false;
}
BOOL CWiFiNetworkInfo::IsNetworkConnected()
{
	if(m_pTempNetwork->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED)
	{
		return true;
	}
	return false;
}
void CWiFiNetworkInfo::SetInterfaceGUID(GUID interfaceGUID)
{
	m_interfaceGUID = interfaceGUID;
}
GUID CWiFiNetworkInfo::GetInterfaceGUID()
{
	return m_interfaceGUID;
}
CString CWiFiNetworkInfo::GetEncryption()
{
	return m_csEncryption;
}
void CWiFiNetworkInfo::SetPassphrase(const CString& csPassphrase)
{
	m_csPassphrase = csPassphrase;
}
CString CWiFiNetworkInfo::GetPassphrase()
{
	return m_csPassphrase;
}
