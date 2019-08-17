
#pragma once
#include "WiFiNetworkInfo.h"
#include <list>
#include "ICmd.h"

#define WM_WLAN_NOTIFY  WM_USER+1

typedef std::list<CWiFiNetworkInfo*> NetworkInfoList;
typedef std::list<std::string> StringList;

typedef enum OSVersion
{
	WINDOWS_2K = 0,
	WINDOWS_XP,
	WINDOWS_VISTA
}OS_VERSION;

#define NOTIFY_ID_SITESURVEY_SUCCESS		TEXT("NOTIFY_ID_SITE_SURVEY_SUCCESS")
#define NOTIFY_ID_SITESURVEY_FAILED			TEXT("NOTIFY_ID_SITESURVEY_FAILED")
#define NOTIFY_ID_CONNECT_SUCCESS			TEXT("NOTIFY_ID_CONNECT_SUCCESS")
#define NOTIFY_ID_CONNECT_FAILED			TEXT("NOTIFY_ID_CONNECT_FAILED")
#define NOTIFY_ID_DISCONNECT_SUCCESS		TEXT("NOTIFY_ID_DISCONNECT_SUCCESS")
#define NOTIFY_ID_DISCONNECT_FAILED			TEXT("NOTIFY_ID_CONNECT_FAILED")
#define NOTIFY_ID_GETPROFILE_SUCCESS		TEXT("NOTIFY_ID_GETPROFILE_SUCCESS")
#define NOTIFY_ID_GETPROFILE_FAILED			TEXT("NOTIFY_ID_GETPROFILE_FAILED")
#define NOTIFY_ID_DELETEPROFILE_SUCCESS		TEXT("NOTIFY_ID_DELETEPROFILE_SUCCESS")
#define NOTIFY_ID_DELETEPROFILE_FAILED		TEXT("NOTIFY_ID_DELETEPROFILE_FAILED")
#define NOTIFY_ID_CREATEPROFILE_FAILED		TEXT("NOTIFY_ID_CREATEPROFILE_FAILED")
#define NOTIFY_ID_CREATEPROFILE_SUCCESS		TEXT("NOTIFY_ID_CREATEPROFILE_SUCCESS")

#define CMD_SITESURVEY				TEXT("CMD_SITESURVEY")
#define CMD_CONNECT					TEXT("CMD_CONNECT")
#define CMD_DISCONNECT				TEXT("CMD_DISCONNECT")
#define CMD_GETPROFILE              TEXT("CMD_GETPROFILE")
#define CMD_DELETEPROFILE           TEXT("CMD_DELETEPROFILE")
#define CMD_CREATE_PROFILE          TEXT("CMD_CREATE_PROFILE")

#define STR_INFRASTRUCTURE          TEXT("INFRASTRUCTURE")
#define STR_ADHOC					TEXT("ADHOC")
#define STR_ESS						TEXT("ESS")
#define STR_IBSS					TEXT("IBSS")

const std::string STR_AUTHENTICATION_OPEN = "open";
const std::string STR_AUTHENTICATION_SHARED = 	"shared";
const std::string STR_AUTHENTICATION_WPA	= 		"WPA";
const std::string STR_AUTHENTICATION_WPAPSK		= "WPAPSK";
const std::string STR_AUTHENTICATION_WPA2		=	"WPA2";
const std::string STR_AUTHENTICATION_WPA2PSK		= "WPA2PSK";
const std::string STR_ENCRYPTION_NONE				= "none";
const std::string STR_ENCRYPTION_WEP				= "WEP";
const std::string STR_ENCRYPTION_TKIP				= "TKIP";
const std::string STR_ENCRYPTION_AES				= "AES";


  