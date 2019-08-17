#include "StdAfx.h"
#include "OSVersion.h"

COSVersion::COSVersion(void)
{
}

COSVersion::~COSVersion(void)
{
}

OS_VERSION COSVersion::GetOSVersion()
{
	BOOL bIsWin2k = FALSE;
	BOOL bIsWinXp = FALSE;
	BOOL bIsWinLH = FALSE;
	
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx( &osvi );
	
	bIsWinLH = (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
			(osvi.dwMajorVersion == 6);

	bIsWin2k = 
	   (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
	   (osvi.dwMajorVersion == 5) &&
	   (osvi.dwMinorVersion == 0);

	bIsWinXp = 
	   (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
	   (osvi.dwMajorVersion == 5) &&
	   (osvi.dwMinorVersion == 1);

	if( bIsWin2k )	return WINDOWS_2K;
	if( bIsWinXp )	return WINDOWS_XP;
	if( bIsWinLH )	return WINDOWS_VISTA;

	return WINDOWS_XP;
}
