#include "StdAfx.h"
#include "CreateProfileFromXML.h"
#include <string>
#include "SampleProfile.h"

#define STR_PROFILE_FILENAME   TEXT("sample Profile.xml")

const std::string  MACRO_PROFILE_NAME		 =	"_PROFILEMACRO_PROFILE_NAME";
const std::string  MACRO_HEX_SSID			 =	"_PROFILEMACRO_HEX_SSID";
const std::string  MACRO_SSID_NAME			 =	"_PROFILEMACRO_SSID_NAME";
const std::string  MACRO_CONNECTION_TYPE	 =	"_PROFILEMACRO_CONNECTION_TYPE";
const std::string  MACRO_CONNECTION_MODE     =  "_PROFILEMACRO_CONNECTION_MODE";
const std::string  MACRO_AUTHENTICATION		 =	"_PROFILEMACRO_AUTHENTICATION";
const std::string  MACRO_ENCRYPTION			 =	"_PROFILEMACRO_ENCRYPTION";
const std::string  MACRO_USEONEX_FLAG		 =	"_PROFILEMACRO_USEONEX_FLAG";
const std::string  MACRO_KEY_TYPE			 =	"_PROFILEMACRO_KEY_TYPE";
const std::string  MACRO_SHAREDKEY_PROTECTED =	"_PROFILEMACRO_SHAREDKEY_PROTECTED";
const std::string  MACRO_KEY_MATERIAL		 =	"_PROFILEMACRO_KEY_MATERIAL";
const std::string  MACRO_KEYINDEX			 =  "_PROFILEMACRO_KEYINDEX";

const std::string STR_NETWORK_KEY				 =  "networkKey";
const std::string STR_PASSPHRASE				 =  "passPhrase";
const std::string STR_CONNECTION_MODE_AUTO       = "auto";
const std::string STR_CONNECTION_MODE_MANUAL     = "manual";

const std::string STR_KEY_INDEX_TAG				 =  "<keyIndex>_PROFILEMACRO_KEYINDEX</keyIndex>";

const std::string STR_PROFILEMACRO_PATTERN   = "_PROFILEMACRO";

CCreateProfileFromXML::CCreateProfileFromXML(void)
{
	m_pListener = NULL;
	m_pTempNetworkInfo = NULL;
	m_pWifiNetwork = NULL;
	m_hSetProfileThread = NULL;
}

CCreateProfileFromXML::CCreateProfileFromXML(IWlanAdapter* pWlanNetwork)
{
	m_pListener = NULL;
	m_pTempNetworkInfo = NULL;
	m_pWifiNetwork = pWlanNetwork;
	m_hSetProfileThread = NULL;
}
CCreateProfileFromXML::~CCreateProfileFromXML(void)
{
}
void CCreateProfileFromXML::SetCmdParameter(void* pData)
{
	if(pData)
	{
		m_pTempNetworkInfo = (CWiFiNetworkInfo*)pData;
	}

}

BOOL CCreateProfileFromXML::Execute(IListener *pListener)
{
	if(pListener)
	{
		m_pListener = pListener;
	}

	if(m_pTempNetworkInfo == NULL)
	{
		return FALSE;
	}

	std::string strXMLProfile = SAMPLE_XML;
	StringList xmlMacroList = GetXMLMacroList(SAMPLE_XML);

	MacroValueMap macroValueMap = ResolveProfileMacros(xmlMacroList);

	MacroValueMap::iterator itr = macroValueMap.find(MACRO_KEY_TYPE);
	if(itr != macroValueMap.end())
	{
		std::string strKeyIndexValue = itr->second;

		if(strKeyIndexValue == STR_PASSPHRASE)
		{
			size_t index = strXMLProfile.find(STR_KEY_INDEX_TAG);

			strXMLProfile.erase(index, STR_KEY_INDEX_TAG.length());
		}
	}

	ReplaceMacroList(macroValueMap, strXMLProfile);

	BOOL bSuccess = m_pWifiNetwork->SetProfile(strXMLProfile.c_str(), 
					m_pTempNetworkInfo->GetInterfaceGUID(),
					m_pTempNetworkInfo->GetNetwork()
					);

	if(m_pListener)
	{
		if(bSuccess)
		{
			m_pListener->Notify(NOTIFY_ID_CREATEPROFILE_SUCCESS, NULL);
		}
		else
		{
			m_pListener->Notify(NOTIFY_ID_CREATEPROFILE_FAILED, NULL);
		}
	}

	return TRUE;
}

bool CCreateProfileFromXML::ReplaceMacroList(MacroValueMap macroValueMap, 
											 std::string& strXMLString)
{
	std::string strValue;
	std::string strMacro;
	MacroValueMap::iterator itrMap;
	if(macroValueMap.size()==0)
	{
		
	}

	for(itrMap = macroValueMap.begin(); itrMap != macroValueMap.end(); itrMap++)
	{
		strMacro = itrMap->first;
		strValue = itrMap->second;

		size_t nPos = -1;
		size_t nSize = strMacro.size();

		nPos = strXMLString.find(strMacro);
		
		if(nPos != std::string::npos)
		{
			strXMLString.replace(nPos, nSize, strValue);
		}
	}

	return true;

}
MacroValueMap CCreateProfileFromXML::ResolveProfileMacros(StringList macroList)
{
	MacroValueMap macroValueMap;

	StringList::iterator itr;
	std::string strValue = "";
	std::string strMacro = "";

	for(itr = macroList.begin(); itr != macroList.end(); itr++)
	{
		strMacro = (*itr);

		if(strMacro.compare(MACRO_PROFILE_NAME) == 0)
		{
			strValue = m_pTempNetworkInfo->GetSSID().GetBuffer();
		}
		else if(strMacro.compare(MACRO_HEX_SSID)==0)
		{
			strValue = StringToHex(m_pTempNetworkInfo->GetSSID());
			
		}
		else if(strMacro.compare(MACRO_SSID_NAME)== 0)
		{
			strValue = m_pTempNetworkInfo->GetSSID().GetBuffer();
		}
		else if(strMacro.compare(MACRO_CONNECTION_TYPE)== 0)
		{
			if(m_pTempNetworkInfo->GetConnectionType() == STR_INFRASTRUCTURE)
			{
				strValue = STR_ESS;
			}
			else if(m_pTempNetworkInfo->GetConnectionType() == STR_ADHOC)
			{
				strValue = STR_IBSS;
			}
		}
		else if(strMacro.compare(MACRO_CONNECTION_MODE) == 0)
		{
			if(m_pTempNetworkInfo->GetConnectionType() = STR_INFRASTRUCTURE)
			{
				strValue = STR_CONNECTION_MODE_AUTO;
			}
			else if(m_pTempNetworkInfo->GetConnectionType() == STR_ADHOC)
			{
				strValue = STR_CONNECTION_MODE_MANUAL;
			}
		}
		else if(strMacro.compare(MACRO_AUTHENTICATION) == 0)
		{
			strValue = m_pTempNetworkInfo->GetAuthentication();

		}
		else if(strMacro.compare(MACRO_ENCRYPTION) == 0)
		{
			strValue = m_pTempNetworkInfo->GetEncryption();
		}
		else if(strMacro.compare(MACRO_USEONEX_FLAG) == 0)
		{
			strValue = "false";
		}
		else if(strMacro.compare(MACRO_KEY_TYPE) == 0)
		{
			if(m_pTempNetworkInfo->GetEncryption().CompareNoCase(STR_ENCRYPTION_WEP.c_str()) == 0)
			{
				strValue = STR_NETWORK_KEY;
			}
			else
			{
				strValue = STR_PASSPHRASE;
			}
		}
		else if(strMacro.compare(MACRO_SHAREDKEY_PROTECTED) == 0)
		{
			strValue = "false";
		}
		else if(strMacro.compare(MACRO_KEY_MATERIAL) == 0)
		{
			strValue = m_pTempNetworkInfo->GetPassphrase();
		}
		else if(strMacro.compare(MACRO_KEYINDEX) == 0)
		{
			strValue = "0";
		}

		macroValueMap[strMacro] = strValue;
	}

	return macroValueMap;
}
StringList CCreateProfileFromXML::GetXMLMacroList(const std::string& strXMLProfile)
{
	StringList xmlMacroList;

	bool bSuccess = true;
	try
	{
		std::string strTempString = strXMLProfile;
		size_t StartIndex = 0;
		do
		{
			StartIndex = strTempString.find(STR_PROFILEMACRO_PATTERN);

			if(StartIndex != std::string::npos)
			{
				strTempString.erase(0, StartIndex);

				size_t endIndex = strTempString.find("</", 0);

				if(endIndex == std::string::npos)
				{
					throw std::exception("Invalid XML");
				}

				std::string strMacro = strTempString.substr(0, endIndex);

				strTempString.erase(0,endIndex);

				xmlMacroList.push_back(strMacro);
			}
		}while(StartIndex != std::string::npos);
	}
	catch(std::exception& e)
	{
		xmlMacroList.clear();
	}

	return xmlMacroList;
}

std::string CCreateProfileFromXML::GetXMLStringFromFile(const std::string& strXMLFilePath)
{

	std::string strXMLStringFromFile = "";
	try
	{
		FILE *pFile = NULL;
		long lFileSize = 0;
		char* pchFileBuf = NULL;

		pFile = fopen(strXMLFilePath.c_str(), "r");

		if(NULL == pFile)
		{
			throw std::exception("failed to open XML file");
		}

		//Obtain file size
		if(fseek(pFile, 0, SEEK_END))
		{
			throw std::exception("Failed to get file size");
		}

		//Get file size
		lFileSize = ftell(pFile);

		//Reset to zero position
		rewind(pFile);

		pchFileBuf = (char*)malloc(lFileSize*sizeof(char));

		memset(pchFileBuf, 0, lFileSize);

		if(pchFileBuf == NULL)
		{
			throw std::exception("failed to allocate buffer for file size");
		}

		unsigned int uiFileRead = fread(pchFileBuf, 1, lFileSize, pFile);

		if(uiFileRead != lFileSize)
		{
			//throw std::exception("File reading error");
		}

		strXMLStringFromFile.assign(pchFileBuf);

		fclose(pFile);
		free(pchFileBuf);
		pchFileBuf = NULL;
	}
	catch(std::exception &e)
	{
	}

	return strXMLStringFromFile;
}

CString CCreateProfileFromXML::StringToHex(CString csString)
{
	char* chHex = csString.GetBuffer();
	CString csHex = "";

	int iLen = csString.GetLength();
	for(int i = 0; i<iLen; i++)
	{
		CString csTempHex;
		csTempHex.Format("%x", chHex[i]);
		csHex.Append(csTempHex);
	}

	return csHex;
}

