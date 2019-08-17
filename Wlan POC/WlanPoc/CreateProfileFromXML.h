#pragma once
#include "icmd.h"
#include "IListener.h"
#include "common.h"
#include "IWlanAdapter.h"
#include <list>
#include <map>

typedef std::list<std::string> StringList;
typedef std::map<const std::string,std::string> MacroValueMap;

class CCreateProfileFromXML : public ICmd
{
public:
	CCreateProfileFromXML(void);
	CCreateProfileFromXML(IWlanAdapter* pAdaptor);
	~CCreateProfileFromXML(void);
	void SetCmdParameter(void* pData);
	BOOL Execute(IListener *pListener = NULL);

private:
	std::string GetXMLStringFromFile(const std::string& csXMLFilePath);
	StringList GetXMLMacroList(const std::string& strXMLProfile);
	bool ReplaceMacroList(MacroValueMap macroValueMap, std::string& strXMLString);
	MacroValueMap ResolveProfileMacros(StringList macroList);
	CString StringToHex(CString csString);

private:
	IWlanAdapter *m_pWifiNetwork;
	CWiFiNetworkInfo* m_pTempNetworkInfo;
	IListener *m_pListener;
	HANDLE m_hSetProfileThread;

};
