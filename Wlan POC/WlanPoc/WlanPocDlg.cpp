// WlanPocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WlanPoc.h"
#include "WlanPocDlg.h"
#include <map>
#include <string>
#include "WlanInterface.h"
#include "WiFiInfoList.h"
#include "OSVersion.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWlanPocDlg dialog




CWlanPocDlg::CWlanPocDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWlanPocDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bShowBusyCursor	=	FALSE;
}

void CWlanPocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_EDIT1, m_editSSID);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT, m_btnDisconnect);
	DDX_Control(pDX, IDC_BUTTON_GETPROFILE, m_btnGetProfile);
	DDX_Control(pDX, IDC_BUTTON_DELETEPROFILE, m_btnDeleteProfile);
	DDX_Control(pDX, IDC_LIST4, m_ListCtrlNetwork);
	DDX_Control(pDX, IDC_BUTTON_SITESURVEY, m_btnSiteSurvey);
	DDX_Control(pDX, IDC_BUTTON5_CREATE_PROFILE, m_btnCreateProfile);
}

BEGIN_MESSAGE_MAP(CWlanPocDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CWlanPocDlg::OnClickConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CWlanPocDlg::OnBnClickDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_GETPROFILE, &CWlanPocDlg::OnBnClickGetProfile)
	ON_BN_CLICKED(IDC_BUTTON_DELETEPROFILE, &CWlanPocDlg::OnBnClickDeleteProfile)

	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SITESURVEY, &CWlanPocDlg::OnClickedSiteSurvey)
	ON_BN_CLICKED(IDCANCEL, &CWlanPocDlg::OnClose)
	ON_MESSAGE(WM_WLAN_NOTIFY, OnWlanNotify)
	ON_BN_CLICKED(IDC_BUTTON5_CREATE_PROFILE, &CWlanPocDlg::OnClickedCreateProfile)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CWlanPocDlg message handlers

BOOL CWlanPocDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_toolTipCtrl.Create(this);
	m_toolTipCtrl.Activate(true);

	CString csTtSiteSurvey = "Click to see details of all the wireless networks available in your surrounding.";
	CString csTtConnectXP = "Click to connect to selected network. Selected network should have saved profile.";
	CString csTtConnectVista = "Click to connect to selected network";
	CString csTtDisconnect = "Click to disconnect the host from selected network";
	CString csTtGetProfile = "Click to see the profile of selected network";
	CString csTtDeleteProfile = "Click to Delete the saved profile of selected network from your PC";
	CString csTtCreateProfile = "Select a network, enter its passphrase.This will save the profile and connect the PC to the selected network";

	if(COSVersion::GetOSVersion() == WINDOWS_XP)
	{
		m_toolTipCtrl.AddTool(&m_btnConnect, csTtConnectXP);
	}
	else
	{
		m_toolTipCtrl.AddTool(&m_btnConnect, csTtConnectVista);
	}
	m_toolTipCtrl.AddTool(&m_btnSiteSurvey, csTtSiteSurvey);
	m_toolTipCtrl.AddTool(&m_btnDisconnect, csTtDisconnect);
	m_toolTipCtrl.AddTool(&m_btnGetProfile, csTtGetProfile);
	m_toolTipCtrl.AddTool(&m_btnDeleteProfile, csTtDeleteProfile);
	m_toolTipCtrl.AddTool(&m_btnCreateProfile, csTtCreateProfile);

	//Initializing Network List control
	m_ListCtrlNetwork.InitListCtrl();

	CWlanInterface *pWlan = CWlanInterface::GetInstance();

	BOOL bSuccess = false;
	bSuccess = pWlan->Initialize();
	if(bSuccess)
	{
		//pWlan->RegisterListener(this);

		ICmd* pCmd = pWlan->GetCmd(CMD_SITESURVEY);
		if(pCmd)
		{
			bSuccess = pCmd->Execute(this);
		}
		if(!bSuccess)
		{
			AfxMessageBox("SiteSurvey failed");

		}
		else
		{
			m_btnSiteSurvey.EnableWindow(false);
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWlanPocDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWlanPocDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWlanPocDlg::OnClickConnect()
{

	//CWlanInterface::GetInstance()->Connect(m_ListCtrlNetwork.GetSelectedNetwork());

	CWlanInterface *pWlan = CWlanInterface::GetInstance();

	if(pWlan)
	{
		ICmd *pCmd = pWlan->GetCmd(CMD_CONNECT);

		if(pCmd)
		{
			CWiFiNetworkInfo *pNetwork = NULL;
			pNetwork = m_ListCtrlNetwork.GetSelectedNetwork();
			if(pNetwork)
			{
				pCmd->SetCmdParameter((void*)pNetwork);
				BOOL bSuccess = pCmd->Execute(this);

				if(bSuccess)
				{
					m_btnConnect.EnableWindow(FALSE);
				}
				else
				{
					AfxMessageBox("CMD_CONNECT failed");
				}
			}
			else
			{
				AfxMessageBox("No network selected!!!");
			}
		}

	}

}

void CWlanPocDlg::OnBnClickDisconnect()
{
	CWlanInterface *pWlan = CWlanInterface::GetInstance();

	if(pWlan)
	{
		ICmd *pCmd = pWlan->GetCmd(CMD_DISCONNECT);

		if(pCmd)
		{
			CWiFiNetworkInfo *pNetwork = m_ListCtrlNetwork.GetSelectedNetwork();
			if(pNetwork)
			{
				pCmd->SetCmdParameter(pNetwork);
				BOOL bSuccess = pCmd->Execute(this);

				if(bSuccess)
				{
					m_bShowBusyCursor = TRUE;
					m_btnDisconnect.EnableWindow(FALSE);
				}
				else
				{
					AfxMessageBox("CMD_CONNECT failed");
				}
			}
			else
			{
				AfxMessageBox("No network selected!!!");
			}
		}
	}
}

void CWlanPocDlg::OnBnClickGetProfile()
{
	CWlanInterface *pWlan = CWlanInterface::GetInstance();

	if(pWlan)
	{
		ICmd* pCmd = pWlan->GetCmd(CMD_GETPROFILE);
		if(pCmd)
		{
			CWiFiNetworkInfo *pNetwork = m_ListCtrlNetwork.GetSelectedNetwork();
			if(pNetwork)
			{
				pCmd->SetCmdParameter(pNetwork);
				if(pCmd->Execute(this))
				{
					m_btnGetProfile.EnableWindow(FALSE);
				}
				else
				{
					AfxMessageBox("FAiled to retrieve Profile");
				}
			}
			else
			{
				AfxMessageBox("No network selected!!!");
			}
		}
	}
}

void CWlanPocDlg::OnClickedSiteSurvey()
{
	ICmd *pCmd = CWlanInterface::GetInstance()->GetCmd(CMD_SITESURVEY);
	if(pCmd)
	{
		if(!pCmd->Execute(this))
		{
			m_bShowBusyCursor = TRUE;
			AfxMessageBox("SiteSurvey failed");
		}
		else
		{
			m_ListCtrlNetwork.DeleteAllItems();
			m_btnSiteSurvey.EnableWindow(false);
		}
	}
}

void CWlanPocDlg::OnBnClickDeleteProfile()
{
	ICmd *pCmd = CWlanInterface::GetInstance()->GetCmd(CMD_DELETEPROFILE);
	if(pCmd)
	{
		CWiFiNetworkInfo *pNetwork = m_ListCtrlNetwork.GetSelectedNetwork();
		if(pNetwork)
		{
			pCmd->SetCmdParameter(pNetwork);
			if(!pCmd->Execute(this))
			{
				m_bShowBusyCursor = TRUE;
				AfxMessageBox("Delete profile failed");
			}
			else
			{
				m_btnDeleteProfile.EnableWindow(false);
			}
		}
		else
		{
			AfxMessageBox("No network selected!!!");
		}
	}
	
}

void CWlanPocDlg::Notify(CString csNotifyID, void* pData)
{
	m_csNotifyID = csNotifyID;
	m_pData = pData;
	PostMessage(WM_WLAN_NOTIFY, 0, 0);
}
LRESULT CWlanPocDlg::OnWlanNotify(WPARAM wparam, LPARAM lParam)
{
	m_bShowBusyCursor = FALSE;
	if(NOTIFY_ID_SITESURVEY_SUCCESS == m_csNotifyID)
	{
		if(m_pData)
		{
			CWiFiInfoList *pInfoList = (CWiFiInfoList*)m_pData;

			m_ListCtrlNetwork.PopulateListCtrl(pInfoList->GetNetworkInfoList());

			m_btnSiteSurvey.EnableWindow(true);
		}
	}
	else if(NOTIFY_ID_SITESURVEY_FAILED == m_csNotifyID)
	{
		m_btnSiteSurvey.EnableWindow(TRUE);
		AfxMessageBox("Site survey failed");
	}
	else if(NOTIFY_ID_CONNECT_SUCCESS == m_csNotifyID)
	{
		m_btnConnect.EnableWindow(TRUE);
		AfxMessageBox("Successfully Connected");
	}
	else if(NOTIFY_ID_CONNECT_FAILED == m_csNotifyID)
	{
		m_btnConnect.EnableWindow(TRUE);
		AfxMessageBox("Couldn't connect to network");
	}
	else if(NOTIFY_ID_DISCONNECT_FAILED == m_csNotifyID)
	{
		m_btnDisconnect.EnableWindow(TRUE);
		AfxMessageBox("Failed to Disconnect");
	}
	else if(NOTIFY_ID_DISCONNECT_SUCCESS == m_csNotifyID)
	{
		m_btnDisconnect.EnableWindow(TRUE);
		AfxMessageBox("Successfully to Disconnect");
	}
	else if(NOTIFY_ID_GETPROFILE_FAILED == m_csNotifyID)
	{
		m_btnGetProfile.EnableWindow(TRUE);
		AfxMessageBox("Failed to get profile");
	}
	else if(NOTIFY_ID_GETPROFILE_SUCCESS == m_csNotifyID)
	{
		//AfxMessageBox("Successfully Getprofile");
		CString strProfileXML((char*)m_pData);

		if(IDYES == MessageBox(strProfileXML, "Want to save the profile?",MB_YESNO))
		{
			SaveProfile(strProfileXML);
			
		}
		m_btnGetProfile.EnableWindow(TRUE);
	}
	else if(NOTIFY_ID_DELETEPROFILE_FAILED == m_csNotifyID)
	{
		m_btnDeleteProfile.EnableWindow(TRUE);
		AfxMessageBox("Failed to Delete profile");
	}
	else if(NOTIFY_ID_DELETEPROFILE_SUCCESS == m_csNotifyID)
	{
		m_btnDeleteProfile.EnableWindow(TRUE);
		AfxMessageBox("Successfully delete profile");
	}
	else if(NOTIFY_ID_CREATEPROFILE_FAILED == m_csNotifyID)
	{
		m_btnCreateProfile.EnableWindow(TRUE);
		AfxMessageBox("Failed to Create and save profile");
	}
	else if(NOTIFY_ID_CREATEPROFILE_SUCCESS == m_csNotifyID)
	{
		m_btnCreateProfile.EnableWindow(TRUE);
		AfxMessageBox("Successfully create and save profile");
	}


	return 1l;
}

BOOL CWlanPocDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	m_toolTipCtrl.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CWlanPocDlg::OnClose()
{
	CWlanInterface::DestroyInstance();
	CDialog::OnOK();
}

void CWlanPocDlg::OnClickedCreateProfile()
{
	CWlanInterface *pWlan = CWlanInterface::GetInstance();
	if(pWlan)
	{
		ICmd* pCmd = pWlan->GetCmd(CMD_CREATE_PROFILE);
		if(pCmd)
		{
			CString strPassphrase = "";
			m_editSSID.GetWindowText(strPassphrase);

			CWiFiNetworkInfo *pNetwork = m_ListCtrlNetwork.GetSelectedNetwork();

			if(pNetwork)
			{
				pNetwork->SetPassphrase(strPassphrase);
				pCmd->SetCmdParameter((void*)m_ListCtrlNetwork.GetSelectedNetwork());
				BOOL bSuccess = pCmd->Execute(this);

				if(bSuccess)
				{
					m_btnCreateProfile.EnableWindow(FALSE);
				}
				else
				{
					AfxMessageBox("CMD_CONNECT failed");
				}
			}
			else
			{
				AfxMessageBox("No network selected!!!");
			}
		}
	}
}

BOOL CWlanPocDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_bShowBusyCursor)
	{
		HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
		SetCursor(hCursor);
		return FALSE;
	}
	else
	{
		return CDialog::OnSetCursor(pWnd, nHitTest, message);
	}
}

BOOL CWlanPocDlg::SaveProfile(CString strProfileXML)
{
	//Display Save Dialog
	OPENFILENAME ofn;
	CString csProfileName = "\0" + m_ListCtrlNetwork.GetSelectedNetwork()->GetProfileName();
	char szFileName[MAX_PATH] = {0};
	memcpy(szFileName, csProfileName.GetBuffer(), MAX_PATH);
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); 
	ofn.hwndOwner = this->GetSafeHwnd();
	ofn.lpstrFilter = _T("XML File (*.xml)\0*.xml\0TXT File (*.txt)\0*.txt\0");
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = _T("xml");

	char szInitPath[MAX_PATH] = {0};
	SHGetSpecialFolderPath(this->GetSafeHwnd(),szInitPath,CSIDL_MYDOCUMENTS,FALSE);
	ofn.lpstrInitialDir = szInitPath;

	csProfileName.ReleaseBuffer();

	if(!GetSaveFileName(&ofn))
	{	
		//return if user press cancel
		return FALSE;
	}	

	CString strFilename = szFileName;
	CString strFilepath = strFilename;

	int index = strFilename.ReverseFind('.');

	strFilename.Delete(0, index);

	if(!(strFilename.MakeUpper()== ".XML"))
		if(!(strFilename.MakeUpper()== ".TXT"))
		{
			int filterIndex = ofn.nFilterIndex;
			if(filterIndex == 1)
			{
				strFilepath = strFilename + ".xml";
			}
			if(filterIndex == 2)
			{
				strFilepath = strFilename + ".txt";
			}
		}


	HANDLE hFile = CreateFile(strFilepath,
		GENERIC_READ|GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	
	if(hFile)
	{
		DWORD  dwWritten;
		WriteFile(hFile, strProfileXML.GetBuffer(), strProfileXML.GetLength(),&dwWritten, NULL);
		CloseHandle(hFile);
	}

	return TRUE;
}
