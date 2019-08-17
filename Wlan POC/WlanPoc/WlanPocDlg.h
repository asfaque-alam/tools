// WlanPocDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "NetworkListControl.h"
#include "IListener.h"


// CWlanPocDlg dialog
class CWlanPocDlg : public CDialog,IListener
{
// Construction
public:
	CWlanPocDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WLANPOC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CToolTipCtrl m_toolTipCtrl;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedSiteSurvey();
	afx_msg void OnClickConnect();
	afx_msg void OnBnClickDisconnect();
	afx_msg void OnBnClickGetProfile();
	afx_msg void OnBnClickDeleteProfile();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	
	afx_msg LRESULT OnWlanNotify(WPARAM wparam, LPARAM lParam);

	//IListener declaration
public:
	virtual void Notify(CString NotifyID, void* pData);

private:
	CButton					m_btnConnect;
	CEdit					m_editSSID;
	CButton					m_btnSiteSurvey;
	CNetworkListControl		m_ListCtrlNetwork;
	CButton					m_btnDisconnect;
	CButton					m_btnGetProfile;
	CButton					m_btnDeleteProfile;
	CString					m_csNotifyID;
	void*					m_pData;
	BOOL					m_bShowBusyCursor;
	afx_msg void OnClickedCreateProfile();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	CButton m_btnCreateProfile;
	BOOL SaveProfile(CString strProfileXML);
};
