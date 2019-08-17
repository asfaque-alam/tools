#pragma once
#include "wlanapi.h"



class CWiFiNetworkInfo
{
public:
	CWiFiNetworkInfo(void);
	CWiFiNetworkInfo(PWLAN_AVAILABLE_NETWORK pNetwork);
public:
	~CWiFiNetworkInfo(void);

private:
	PWLAN_AVAILABLE_NETWORK m_pTempNetwork;
	CString m_csProfileName;
	CString m_csSSID;
	CString m_csdBssType;
	BOOL m_bNetworkConnectable;
	BOOL m_bSecurityEnable;
	ULONG m_ulSignalQuality;
	CString m_csAuthentication;
	CString m_csEncryption;
	GUID m_interfaceGUID;
	CString m_csPassphrase;

public:
	CString GetSSID();
	CString GetProfileName();
	CString GetAuthentication();
	CString GetConnectionType();
	ULONG GetSignalQuality();
	BOOL IsNetworkConntectable();
	BOOL IsSecurityEnable();
	BOOL IsNetworkConnected();
	BOOL HasProfile();
	PWLAN_AVAILABLE_NETWORK GetNetwork();
	void SetInterfaceGUID(GUID interfaceGUID);
	GUID GetInterfaceGUID();
	CString GetEncryption();
	void SetPassphrase(const CString& csPassphrase);
	CString GetPassphrase();
};
