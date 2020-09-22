
// MFC3Dlg.cpp : implementation file
//
#include "pch.h"
#include "framework.h"
#include "MFC3.h"
#include "MFC3Dlg.h"
#include "afxdialogex.h"
#include <string>
#include "XmlSerialization.h"
#include "pch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	CBCGPURLLinkButton m_btnURL;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()
CAboutDlg::CAboutDlg() : CBCGPDialog(IDD_ABOUTBOX)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}



CMFC3Dlg::CMFC3Dlg(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_MFC3_DIALOG, pParent)
	, birthday(_T(""))
	, name(_T(""))
	, name_f(_T(""))
	, Nnumber(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listctrl);
	DDX_Text(pDX, txtBirthday, birthday);
	DDX_Text(pDX, txtName, name);
	DDX_Text(pDX, txtName2, name_f);
	DDX_Text(pDX, txtNumber2, Nnumber);
	/*DDX_Control(pDX, btnDelete, del);
	DDX_Control(pDX, btnExport, exp);
	DDX_Control(pDX, btnImport, imp);
	DDX_Control(pDX, btnInsert, ins);
	DDX_Control(pDX, btnReset, res);
	DDX_Control(pDX, IDC_BUTTON1, btn1);
	DDX_Control(pDX, txtBirthday, bir);
	DDX_Control(pDX, txtName, nam);
	DDX_Control(pDX, txtName2, namf);
	DDX_Control(pDX, txtNumber2, nnum);*/
}

BEGIN_MESSAGE_MAP(CMFC3Dlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC3Dlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CMFC3Dlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(btnInsert, &CMFC3Dlg::OnBnClickedbtninsert)
	ON_BN_CLICKED(btnReset, &CMFC3Dlg::OnBnClickedbtnreset)
	ON_EN_CHANGE(txtName2, &CMFC3Dlg::OnEnChangetxtname2)
	ON_BN_CLICKED(btnDelete, &CMFC3Dlg::OnBnClickedbtndelete)
	ON_BN_CLICKED(btnImport, &CMFC3Dlg::OnBnClickedbtnimport)
	ON_BN_CLICKED(btnExport, &CMFC3Dlg::OnBnClickedbtnexport)
END_MESSAGE_MAP()


// CMFC3Dlg message handlers

BOOL CMFC3Dlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

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

	listctrl.InsertColumn(3, L"Name", LVCFMT_LEFT, 150);
	listctrl.InsertColumn(2, L"Birthday", LVCFMT_LEFT, 100);
	listctrl.InsertColumn(0, L"RowID", LVCFMT_LEFT, 100);
	data.Open("C:\\DataBase\\first.db");
	std::list<userData> dataList;
	data.DataIntoList(dataList);
	Output(dataList);
	
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
		CBCGPDialog::OnSysCommand(nID, lParam);
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
		CBCGPDialog::OnPaint();
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
	listctrl.DeleteAllItems();
	try{
	CT2CA pszConvertedAnsiString(name_f);//Converting an MFC CString to a std::string
	std::string n(pszConvertedAnsiString);
	std::list<userData> dataList;
	data.bindName(dataList, n);
	Output(dataList);

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
	std::list<userData> dataList;
	userData c;
	CT2CA pszConvertedAnsiString(name);//Converting an MFC CString to a std::string
	std::string n(pszConvertedAnsiString);
	c.name = n;
	c.birthday = _wtoi(birthday);
	c.number = _wtoi(Nnumber);
	dataList.push_back(c);

	data.insertData(dataList);
	Output(dataList);
	Nnumber = "";
	name = "";
	birthday = "";
	UpdateData(FALSE);
}

void CMFC3Dlg::OnBnClickedbtnreset()
{
	std::list<userData> dataList;
	data.DataIntoList(dataList);
	listctrl.DeleteAllItems();
	Output(dataList);
	name_f = "";
	UpdateData(FALSE);
}


void CMFC3Dlg::OnEnChangetxtname2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFC3Dlg::OnBnClickedbtndelete()
{
	try {
		Transaction tr(data);
		std::list<userData> dataList;
		POSITION pos = listctrl.GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			MessageBox(NULL, L"Nothing selected!");
		}
		else
		{
			while (pos)
			{
				int nItem = listctrl.GetNextSelectedItem(pos);
				CString numb = listctrl.GetItemText(nItem, 0);
				number = _ttoi(numb);
				data.DeleteItem(dataList, number);
			}
			data.DataIntoList(dataList);
		}
		listctrl.DeleteAllItems();
		tr.commit();
		Output(dataList);
	}
	catch (SQLException &ex) {
		MessageBoxA(NULL, ex.what(), "error", MB_OK);
	}
}


void CMFC3Dlg::Output(UserDataList & dataList)
{
	for (UserDataList::iterator it = dataList.begin(); it != dataList.end(); it++)//datalist output into listctrl
	{
		int itemCount = listctrl.GetItemCount();
		std::wstring numberStr(std::to_wstring(it->number));
		int nItem = listctrl.InsertItem(itemCount, numberStr.c_str());

		CA2W cvtStr(it->name.c_str());//Converting string to a Cstring

		listctrl.SetItemText(nItem, 1, cvtStr);

		std::wstring birthdayStr(std::to_wstring(it->birthday));

		listctrl.SetItemText(nItem, 2, birthdayStr.c_str());
	}
	
}


void CMFC3Dlg::OnBnClickedbtnimport()
{
	try{
	listctrl.DeleteAllItems();
	std::list<userData> dataList;
	std::list<userData> dataList2;
	XMLImport(dataList);
	DataSort(dataList, dataList2);

	data.insertData(dataList);
	data.insertData2(dataList2);

	data.DataIntoList(dataList);
	Output(dataList);
	//Output(dataList2);
	UpdateData(FALSE);
	}
	catch (SQLException &ex) {
		MessageBoxA(NULL, ex.what(), "error", MB_OK);
	}
}


void CMFC3Dlg::OnBnClickedbtnexport()
{
	CFileDialog dlg(FALSE, _T("xml"), _T("*.xml"));
	if (dlg.DoModal() == IDOK)
	{
		std::list<userData> dataList;
		data.DataIntoList(dataList);

		ToXml(dlg.GetPathName().GetString(), dataList);

	}

}

void CMFC3Dlg::XMLImport(UserDataList & dataList) 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"XML Files (*.xml)|*.xml||", NULL, 0);
	if (dlg.DoModal() == IDOK)
	{
		bool status = FromXml(dlg.GetPathName().GetString(), dataList);

		if (!status)
		{
			MessageBoxA(NULL, "Failed to load xml", "RESULT", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, L"DLG error");
	}
}

void CMFC3Dlg::DataSort(UserDataList & dataList, UserDataList & dataList2)
{
	auto it = dataList.begin();

	while (it != dataList.end())
	{
		if (data.isexist(it->number) != 0)
		{
			dataList2.push_back(*it);

			auto toDelete = it;
			++it;
			dataList.erase(toDelete);
		}
		else
		{
			++it;
		}
	}

}
