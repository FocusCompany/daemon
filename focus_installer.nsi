!include "MUI.nsh"

!define MUI_ABORTWARNING # This will warn the user if he exits from the installer.
!insertmacro MUI_PAGE_WELCOME # Welcome to the installer page.
!insertmacro MUI_PAGE_INSTFILES # Installing page.
!insertmacro MUI_PAGE_FINISH # Finished installation page.
!insertmacro MUI_LANGUAGE "English"

!define PRODUCT_NAME "Focus Beta Ver. 1.0"

RequestExecutionLevel admin

Name "Focus"
OutFile "Focus_Installer.exe"
InstallDir "$PROGRAMFILES64\Focus"
ShowInstDetails show

Section "Focus"

	SetOutPath "C:\OpenSSL-Win32\"
	File /r "C:\OpenSSL-Win32\*"
	
	SetOutPath $INSTDIR

	File /r "C:\Users\pasteu_e\Desktop\Focus\*"

	AccessControl::GrantOnFile "$INSTDIR\Focus" "(BU)" "FullAccess"
	
	WriteUninstaller "$INSTDIR\uninstall.exe"

	SetOutPath $INSTDIR\Focus

	CreateDirectory "$SMPROGRAMS\Focus"
	CreateShortCut "$SMPROGRAMS\Focus\uninstall.lnk" "$INSTDIR\uninstall.exe"
	CreateShortCut "$SMPROGRAMS\Focus\Focus.lnk" "$INSTDIR\Focus\daemon_windows.exe"
	CreateShortCut "$DESKTOP\Focus.lnk" "$INSTDIR\Focus\daemon_windows.exe"
SectionEnd

Section "Uninstall"
    Delete "$SMPROGRAMS\Focus\uninstall.lnk"
    Delete "$SMPROGRAMS\Focus\Focus.lnk"
    Delete "$DESKTOP\Focus.lnk"
	RmDir  "$SMPROGRAMS\Focus"

    Delete "$INSTDIR\uninstall.exe"

    RMDir /r "C:\OpenSSL-Win32\*"
    RMDir "C:\OpenSSL-Win32\"

    RMDir /r "$INSTDIR\*"
    RMDir "$INSTDIR"
 SectionEnd

Function .onInstSuccess
  MessageBox MB_OK "You have successfully installed ${PRODUCT_NAME}."
FunctionEnd
 
 
Function un.onUninstSuccess
  MessageBox MB_OK "You have successfully uninstalled ${PRODUCT_NAME}."
FunctionEnd