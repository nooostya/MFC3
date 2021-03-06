﻿
// MFC3Dlg.cpp : implementation file
//
//#include "pch.h"
#include "framework.h"
#include "MFC3.h"
#include "MFC3Dlg.h"
#include "afxdialogex.h"
#include <string>
#include "XmlSerialization.h"
#include "BCGCBProInc.h"
//#include "Resourсe.h"

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
	//}}AFX_DATA_INIT
	
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

CMFC3Dlg::CMFC3Dlg(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_MFC3_DIALOG, pParent)
	, name_f(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CMFC3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, txtName2, name_f);
}

BEGIN_MESSAGE_MAP(CMFC3Dlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BtnFilter, &CMFC3Dlg::OnBnClickedBtnFilter)
	ON_BN_CLICKED(btnReset, &CMFC3Dlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(btnDelete, &CMFC3Dlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(btnImport, &CMFC3Dlg::OnBnClickedBtnImport)
	ON_BN_CLICKED(btnExport, &CMFC3Dlg::OnBnClickedBtnExport)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_ENDINPLACEEDIT, OnEndLabelEdit)
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

	nGrid.SetListener(this);

	nGrid.CreateOnPlaceHolder(this, pictureGrid);
	nGrid.InsertColumn(0, L"RowID", 100);
	nGrid.InsertColumn(1, L"Name", 150);
	nGrid.InsertColumn(2, L"Birthday", 100);

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
void CMFC3Dlg::OnBnClickedBtnFilter()//filter by name button
{
	
	UpdateData(TRUE); 
	nGrid.RemoveAll();	
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
void CMFC3Dlg::OnOK()
{
	nGrid.RemoveAll();
	std::list<userData> dataList;
	data.DataIntoList(dataList);
	Output(dataList);
}

void CMFC3Dlg::OnBnClickedBtnReset()
{
	std::list<userData> dataList;
	data.DataIntoList(dataList);
	nGrid.RemoveAll();
	Output(dataList);
	name_f = "";
	UpdateData(FALSE);
}

void CMFC3Dlg::OnBnClickedBtnDelete()
{
	try {
		Transaction tr(data);
		std::list<userData> dataList;
		CBCGPGridRow* pRow = nGrid.GetCurSel();

		if (nGrid.GetCurSel() == 0) {
			throw SQLException("nothing selected");
		}

		int number = pRow->GetData();
		data.DeleteItem(dataList, number);
		data.DataIntoList(dataList);
		tr.commit();
		
		nGrid.RemoveAll();
		Output(dataList);
	}
	catch (SQLException &ex) {
		MessageBoxA(NULL, ex.what(), "error", MB_OK);
	}
}


void CMFC3Dlg::Output(UserDataList & dataList)
{
	const int nColumns = nGrid.GetColumnCount();
	for (UserDataList::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		
		std::wstring numberStr(std::to_wstring(it->number));
		std::wstring birthdayStr(std::to_wstring(it->birthday));
		
		CBCGPGridRow* pRow = nGrid.CreateRow(nColumns);
		CString name;
		pRow->GetItem(0)->SetValue(numberStr.c_str());
		pRow->GetItem(0)->SetReadOnly(TRUE);
		pRow->GetItem(1)->SetValue(it->name.c_str());
		pRow->GetItem(2)->SetValue(birthdayStr.c_str());
		pRow->SetData(it->number);
			
		nGrid.AddRow(pRow, FALSE);
		
	}
	nGrid.AdjustLayout();
}


void CMFC3Dlg::OnBnClickedBtnImport()
{
	try{
	nGrid.RemoveAll();
	std::list<userData> dataList;
	std::list<userData> dataList2;
	XMLImport(dataList);
	DataSelection(dataList, dataList2);

	data.insertData(dataList);
	data.insertData2(dataList2);

	data.DataIntoList(dataList);
	Output(dataList);
	UpdateData(FALSE);
	}
	catch (SQLException &ex) {
		MessageBoxA(NULL, ex.what(), "error", MB_OK);
	}
}


void CMFC3Dlg::OnBnClickedBtnExport()
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
}

void CMFC3Dlg::DataSelection(UserDataList & dataList, UserDataList & dataList2)
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

void CMFC3Dlg::OnGridItemChanged(CBCGPGridItem * pItem, int nRow, int nColumn)
{
	try {
		CBCGPGridRow* pRow = nGrid.GetCurSel();
		int number = pRow->GetData();
		int count;
		
		if(nColumn == 2)
		{ 
			CString birthday = pItem->GetValue();
			int b = _wtoi(birthday);
			data.UpdateDataBirthday(number, b);
		}
		if (nColumn == 1)
		{
			CString name;
			name = pItem->GetValue();
			CT2CA pszConvertedAnsiString(name);//Converting an MFC CString to a std::string
			std::string n(pszConvertedAnsiString);
			data.UpdateDataName(number, n);
		}		
	}
	catch (SQLException &ex) {
		MessageBoxA(NULL, ex.what(), "error", MB_OK);
	}
}
LRESULT CMFC3Dlg::OnEndLabelEdit(WPARAM wp, LPARAM lp)
{
	BCGPGRID_ITEM_INFO* pii = (BCGPGRID_ITEM_INFO*)lp;
	ASSERT(pii != NULL);
	ASSERT_VALID(pii->pItem);

	// Handle ENTER after in-place edit is closed
	if ((pii->dwResultCode & EndEdit_Return) != 0)
	{
		OnInplaceGridEditEnter(pii->pItem);
		return 0;
	}
}
void CMFC3Dlg::OnInplaceGridEditEnter(CBCGPGridItem* pItem)
{
	ASSERT_VALID(pItem);
	CBCGPGridItemID id = pItem->GetGridItemID();
	int nLastValuableRow = nGrid.GetRowCount() - 1;
	if (id.m_nRow < nLastValuableRow)
	{
		id.m_nRow++;		
	}
	else
	{
		InsertNewRecordGrid(nLastValuableRow + 1);
		id.m_nRow = nLastValuableRow + 1;
	}
	if (id.m_nColumn == 0) {
		id.m_nColumn = 1;
	}
	nGrid.SetCurSel(id);
	ContinueGridInplaceEditing();
	
}
void CMFC3Dlg::ContinueGridInplaceEditing()
{
	CBCGPGridRow* pSel = nGrid.GetCurSel();
	if (pSel != NULL && pSel->GetInPlaceWnd() == NULL)
	{
		SendMessage(WM_KEYDOWN, VK_F2);
	}
}
int CMFC3Dlg::InsertNewRecordGrid(int nPos)
{
	CBCGPGridRow* pRow = nGrid.CreateRow(nGrid.GetColumnCount());
	pRow->GetItem(0)->SetValue(nPos+1);
	pRow->GetItem(0)->SetReadOnly(TRUE);
	pRow->GetItem(1)->SetValue(_T(""));
	pRow->GetItem(2)->SetValue(_T(""));
	pRow->SetData(nPos + 1);
	std::list<userData> dataList;
	userData c;
	c.name = "0";
	c.birthday = 0;
	dataList.push_back(c);
	data.insertData2(dataList);
	
	int nIndex = (nPos == 0) ? nGrid.InsertRowBefore(0, pRow) : nGrid.InsertRowAfter(nPos - 1, pRow);
	nGrid.AdjustLayout();
	return nIndex;
}
