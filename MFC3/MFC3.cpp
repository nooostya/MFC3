
// MFC3.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFC3.h"
#include "MFC3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC3App

BEGIN_MESSAGE_MAP(CMFC3App, CBCGPWinApp)
	ON_COMMAND(ID_HELP, CBCGPWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC3App construction

CMFC3App::CMFC3App()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	SetVisualTheme(BCGP_VISUAL_THEME_VS_2019_DARK);
	// Place all significant initialization in InitInstance
}


// The one and only CMFC3App object

CMFC3App theApp;


// CMFC3App initialization

BOOL CMFC3App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CBCGPWinApp::InitInstance();
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CBCGPShellManager *pShellManager = new CBCGPShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPWinXPVisualManager));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("MyCompany\\MyProduct"));

	CMFC3Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



