// NetworkListControl.cpp : implementation file
//

#include "stdafx.h"
#include "WlanPoc.h"
#include "NetworkListControl.h"


// CNetworkListControl

IMPLEMENT_DYNAMIC(CNetworkListControl, CListCtrl)

CNetworkListControl::CNetworkListControl()
{

}

CNetworkListControl::~CNetworkListControl()
{
}

void CNetworkListControl::InitListCtrl()
{
	CRect rcList ;
    GetClientRect(&rcList);
	float icolumnWidthSSID = (float)(rcList.Width()/5);

	CString strColumnSSIDText = TEXT("SSID");
	CString strColumnProfileText = TEXT("Profile Name");
	CString strColumnBSSTypeText = TEXT("Connection Type");
	CString strColumnSignalText = TEXT("Signal Strength");
	CString strColumnSecurityText = TEXT("Status");
	

	int ret = CListCtrl::InsertColumn(1, strColumnSSIDText,LVCFMT_LEFT, icolumnWidthSSID);
	ret = CListCtrl::InsertColumn(2, strColumnProfileText, LVCFMT_LEFT,  icolumnWidthSSID);
	ret = CListCtrl::InsertColumn(3, strColumnBSSTypeText, LVCFMT_LEFT,  icolumnWidthSSID);
	ret = CListCtrl::InsertColumn(4, strColumnSignalText, LVCFMT_LEFT,  icolumnWidthSSID);
	ret = CListCtrl::InsertColumn(5, strColumnSecurityText, LVCFMT_LEFT,  icolumnWidthSSID);

	CListCtrl::SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
}

void CNetworkListControl::PopulateListCtrl(NetworkInfoList networkInfoList)
{
	DeleteAllItems();
	if(networkInfoList.size() > 0)
	{
		NetworkInfoList::iterator itr;
		int nItem = 0;
		for(itr = networkInfoList.begin(); itr != networkInfoList.end(); itr++)
		{
			CWiFiNetworkInfo *pNetworkInfo = *itr;

			nItem = InsertItem(LVCF_TEXT|LVIF_STATE, 
						nItem, 
						pNetworkInfo->GetSSID(), 
						LVIS_SELECTED, 
						LVIS_SELECTED, 
						0, 
						(LPARAM)pNetworkInfo);
			
			SetItemText(nItem, 0, pNetworkInfo->GetSSID());
			SetItemText(nItem, 1, pNetworkInfo->GetProfileName());
			SetItemText(nItem, 2, pNetworkInfo->GetConnectionType());
			CString strSignalStrength;
			strSignalStrength.Format("%d", pNetworkInfo->GetSignalQuality());
			SetItemText(nItem, 3, strSignalStrength);

			if(pNetworkInfo->IsNetworkConnected() == TRUE)
			{
				SetItemText(nItem, 4, "Connected");
			}
		}
	}
}

CWiFiNetworkInfo* CNetworkListControl::GetSelectedNetwork()
{
	LVITEM lvitem;
	int iItem = GetSelectionMark();
	lvitem.iItem = iItem;
	lvitem.mask = LVIF_PARAM;
	bool bSuccess = GetItem(&lvitem);
	CWiFiNetworkInfo *pNetwork = NULL;

	if(bSuccess)
	{
		pNetwork = (CWiFiNetworkInfo*)lvitem.lParam;
	}

	return pNetwork;
}

BEGIN_MESSAGE_MAP(CNetworkListControl, CListCtrl)
END_MESSAGE_MAP()



// CNetworkListControl message handlers


