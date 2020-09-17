
// MFC3Dlg.h : header file
//

#pragma once
#include "SQL.h"
#include "fileOperations.h"
#include "userData.h"
#include <string>
#include "Transaction.h"

// CMFC3Dlg dialog
class CMFC3Dlg : public CDialogEx
{
// Construction
public:
	CMFC3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC3_DIALOG };
#endif

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
	CListCtrl listctrl;
	SQL data;
	int number;
	fileOperations op;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedbtninsert();
	CString birthday;
	CString name;
	CString name_f;
	CString pathName;
	afx_msg void OnBnClickedbtnreset();
	afx_msg void OnEnChangetxtname2();
	afx_msg void OnBnClickedbtndelete();
	void Output(UserDataList & dataList);
	afx_msg void OnBnClickedbtnimport();
	CString Nnumber;
	afx_msg void OnBnClickedbtnexport();
	void XMLParser(UserDataList & dataList);
	void DataSort(UserDataList & dataList, UserDataList & dataList2);
};
