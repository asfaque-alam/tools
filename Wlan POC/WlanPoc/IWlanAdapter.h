#pragma once
#include "wlanapi.h"
#include "common.h"

class IWlanAdapter
{
public:
	virtual ~IWlanAdapter(){}
	virtual BOOL OpenHandle() = 0;
	virtual BOOL EnumInterfaces() = 0;
	virtual PWLAN_INTERFACE_INFO_LIST GetNICsList() = 0;

	virtual BOOL ConnectToNetwork(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID) = 0; 
	virtual PWLAN_AVAILABLE_NETWORK_LIST SiteSurvey(GUID InterfaceGUID) = 0;
	virtual BOOL DisconnectFromNetwork(GUID interfaceGUID) = 0;
	virtual BOOL GetProfile(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID, CString& strProfileXML) = 0;
	virtual BOOL DeleteProfile(PWLAN_AVAILABLE_NETWORK pNetwork, GUID interfaceGUID) = 0;
	virtual BOOL SetProfile(CString strProfileXML, 
				GUID interfaceGUID,
				PWLAN_AVAILABLE_NETWORK pNetwork = NULL)= 0;
	virtual BOOL GetProfileList(GUID interfaceGUID, StringList& profileList) = 0;
};
