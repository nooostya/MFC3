
// MFC3Dlg.cpp : implementation file
//
#include "pch.h"
#include "framework.h"
#include "MFC3.h"
#include "MFC3Dlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC3Dlg dialog



CMFC3Dlg::CMFC3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC3_DIALOG, pParent)
	, birthday(_T(""))
	, name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listctrl);
	DDX_Text(pDX, txtBirthday, birthday);
	DDX_Text(pDX, txtName, name);
}

BEGIN_MESSAGE_MAP(CMFC3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC3Dlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CMFC3Dlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(btnInsert, &CMFC3Dlg::OnBnClickedbtninsert)
END_MESSAGE_MAP()


// CMFC3Dlg message handlers

BOOL CMFC3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	listctrl.InsertColumn(0, L"Name", LVCFMT_LEFT, 150);
	listctrl.InsertColumn(2, L"Birthday", LVCFMT_LEFT, 100);
	data.Open("C:\\DataBase\\first.db");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFC3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFC3Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFC3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC3Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	try{
	CT2CA pszConvertedAnsiString(name);
	std::string n(pszConvertedAnsiString);
	std::list<userData> dataList;
	data.bindName(dataList, n);
	for (UserDataList::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		CA2W cvtStr(it->name.c_str());

		int nItem=listctrl.InsertItem(0, cvtStr);

		std::wstring birthdayStr( std::to_wstring(it->birthday));
		
		listctrl.SetItemText(nItem,1, birthdayStr.c_str());
	}

	}
	catch (SQLException &ex) 
	{
		MessageBoxA(NULL, ex.what(),"error",MB_OK);
	}
}


void CMFC3Dlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CMFC3Dlg::OnBnClickedbtninsert()
{
	UpdateData(TRUE);
	try {
	std::list<userData> dataList;
	data.insertData(dataList);
	for (UserDataList::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		CA2W cvtStr(it->name.c_str());

		int nItem = listctrl.InsertItem(0, cvtStr);

		std::wstring birthdayStr(std::to_wstring(it->birthday));

		listctrl.SetItemText(nItem, 1, birthdayStr.c_str());
	}

	}
	catch (SQLException &ex)
	{
		MessageBoxA(NULL, ex.what(), "error", MB_OK);
	}
}
