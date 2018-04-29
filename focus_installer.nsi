!include "MUI.nsh"

!define MUI_ICON "icon_daemon.ico"
!define MUI_UNICON "icon_uninstall.ico"
!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_LANGUAGE "English"

RequestExecutionLevel admin

Name "Focus"
OutFile "Setup.exe"
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
	CreateShortCut "$SMPROGRAMS\Focus\Focus.lnk" "$INSTDIR\Focus\daemon_windows.exe" "" "$INSTDIR\Focus\icon_daemon.ico" 0
	CreateShortCut "$DESKTOP\Focus.lnk" "$INSTDIR\Focus\daemon_windows.exe" "" "$INSTDIR\Focus\icon_daemon.ico" 0
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
