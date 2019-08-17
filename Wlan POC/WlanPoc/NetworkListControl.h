#pragma once

#include "common.h"

// CNetworkListControl

class CNetworkListControl : public CListCtrl
{
	DECLARE_DYNAMIC(CNetworkListControl)

public:
	CNetworkListControl();
	virtual ~CNetworkListControl();
	void InitListCtrl();
	void PopulateListCtrl(NetworkInfoList networkInfoList);
	CWiFiNetworkInfo* GetSelectedNetwork();

protected:
	DECLARE_MESSAGE_MAP()
};


