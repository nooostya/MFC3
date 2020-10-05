
// MFC3Dlg.h : header file
//

#pragma once
#include "SQL.h"
#include "fileOperations.h"
#include "userData.h"
#include <string>
#include "Transaction.h"
#include "BCGCBProInc.h"

class GridListener
{
public:
	virtual void OnGridItemChanged(CBCGPGridItem *  pItem, int nRow, int nColumn) = 0;
};

class MyGridControl : public CBCGPGridCtrl
{
public:

	void SetListener(GridListener* listener)
	{
		m_listener = listener;
	}

	void OnItemChanged(CBCGPGridItem *  pItem, int nRow, int nColumn) override
	{
		m_listener->OnGridItemChanged(pItem, nRow, nColumn);
	}

private:
	GridListener* m_listener;
};

// CMFC3Dlg dialog
class CMFC3Dlg : public CBCGPDialog, public GridListener
{
// Construction
public:
	CMFC3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC3_DIALOG };
#endif
	CBCGPThemeSelectorComboBox	m_wndVisualTheme;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
	int number = 0;
	fileOperations op;
	afx_msg void OnBnClickedbtninsert();
	CString birthday;
	CString name;
	CString name_f;
	CString pathName;
	afx_msg void OnBnClickedbtnreset();
	afx_msg void OnBnClickedbtndelete();
	void Output(UserDataList & dataList);
	afx_msg void OnBnClickedbtnimport();
	CString Nnumber;
	afx_msg void OnBnClickedbtnexport();
	void XMLImport(UserDataList & dataList);
	void DataSort(UserDataList & dataList, UserDataList & dataList2);

	virtual void OnGridItemChanged(CBCGPGridItem *  pItem, int nRow, int nColumn) override;

	MyGridControl nGrid;
	SQL data;
};