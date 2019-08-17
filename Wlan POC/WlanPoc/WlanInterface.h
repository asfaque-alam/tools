#pragma once
#include "common.h"
#include "IListener.h"
#include "IWlanAdapter.h"
#include <string>
#include <map>

typedef std::list<IListener*> ListnerList;
typedef std::map<std::string,ICmd*> CmdMap;

class CWlanInterface
{
public:
	CWlanInterface(void);
public:
	~CWlanInterface(void);
	BOOL Initialize(void);
	void UnInitialize();
	static CWlanInterface* GetInstance(void);
	static void DestroyInstance();
	void RegisterListener(IListener* pListener);
	ICmd* GetCmd(CString csCmdID);

private:
	BOOL IsNICAvailable(void);
	void ClearNetworkList();

private:
	static CWlanInterface *m_pWlanInterface;
	IWlanAdapter *m_pWifiNetwork;
	NetworkInfoList m_NetworkInfoList;
	ListnerList m_ListenerList;
	CmdMap m_cmdMap;
};
