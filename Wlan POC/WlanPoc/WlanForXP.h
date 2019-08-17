#pragma once
#include "Wlanapi.h"
#include "IWlanAdapter.h"
#include "common.h"

class CWlanForXP : public IWlanAdapter
{
public:
	CWlanForXP(void);
	~CWlanForXP(void);
	BOOL OpenHandle();
	BOOL EnumInterfaces();
	PWLAN_INTERFACE_INFO_LIST GetNICsList();

	BOOL ConnectToNetwork(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID);
	PWLAN_AVAILABLE_NETWORK_LIST SiteSurvey(GUID InterfaceGUID);
	BOOL DisconnectFromNetwork(GUID interfaceGUID);
	BOOL GetProfile(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID, CString& strProfileXML);
	BOOL DeleteProfile(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID);
	BOOL SetProfile(CString strProfileXML, 
				GUID interfaceGUID,
				PWLAN_AVAILABLE_NETWORK pNetwork = NULL);

	BOOL GetProfileList(GUID interfaceGUID, StringList& profileList);

private:
	HANDLE m_hClientHandle;
	DWORD m_dwNegotiatedVersion;
	PWLAN_INTERFACE_INFO_LIST m_pInterfaceList;
	PWLAN_AVAILABLE_NETWORK_LIST m_pAvailableNetworkList;
	DWORD m_InterfaceIndex;
	GUID m_InterfaceGuid;
	DWORD m_NetworkIndex;
	CString m_strSSID;
	HANDLE m_hNotiifcationEvent;


};
