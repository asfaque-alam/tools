#pragma once
#include "stdafx.h"

const std::string SAMPLE_XML = "<?xml version=\"1.0\"?>"
"<WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\">"
	"<name>_PROFILEMACRO_PROFILE_NAME</name>"
	"<SSIDConfig>"
		"<SSID>"
			"<hex>_PROFILEMACRO_HEX_SSID</hex>"
			"<name>_PROFILEMACRO_SSID_NAME</name>"
		"</SSID>"
	"</SSIDConfig>"
	"<connectionType>_PROFILEMACRO_CONNECTION_TYPE</connectionType>"
	"<connectionMode>_PROFILEMACRO_CONNECTION_MODE</connectionMode>"
	"<MSM>"
		"<security>"
			"<authEncryption>"
				"<authentication>_PROFILEMACRO_AUTHENTICATION</authentication>"
				"<encryption>_PROFILEMACRO_ENCRYPTION</encryption>"
				"<useOneX>_PROFILEMACRO_USEONEX_FLAG</useOneX>"
			"</authEncryption>"
			"<sharedKey>"
				"<keyType>_PROFILEMACRO_KEY_TYPE</keyType>"
				"<protected>_PROFILEMACRO_SHAREDKEY_PROTECTED</protected>"
				"<keyMaterial>_PROFILEMACRO_KEY_MATERIAL</keyMaterial>"
			"</sharedKey>"
			"<keyIndex>_PROFILEMACRO_KEYINDEX</keyIndex>"
		"</security>"
	"</MSM>"
"</WLANProfile>";