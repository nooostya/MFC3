﻿
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
	virtual int InsertNewRecordGrid(int nPos) = 0;
	virtual void OnInplaceGridEditEnter(CBCGPGridItem * pItem) =0;
	virtual void ContinueGridInplaceEditing()=0;

};

class MyGridControl : public CBCGPGridCtrl
{
public:
	MyGridControl() {
		m_listener = 0;
	}
	void SetListener(GridListener* listener)
	{
		m_listener = listener;
	}
	void OnItemChanged(CBCGPGridItem *  pItem, int nRow, int nColumn) override
	{
		if (m_listener != 0) {
			m_listener->OnGridItemChanged(pItem, nRow, nColumn);
		}
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
	//MyGridControl* m_pGrid;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

	fileOperations op;
	MyGridControl nGrid;
	SQL data;

public:
	afx_msg void OnBnClickedBtnFilter();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnExport();

	CString name_f;
	
	void Output(UserDataList & dataList);
	void XMLImport(UserDataList & dataList);
	void DataSort(UserDataList & dataList, UserDataList & dataList2);
	

	LRESULT OnEndLabelEdit(WPARAM, LPARAM lp);

	virtual void OnGridItemChanged(CBCGPGridItem *  pItem, int nRow, int nColumn);
	virtual void OnInplaceGridEditEnter(CBCGPGridItem * pItem);
	virtual void ContinueGridInplaceEditing();
	virtual int InsertNewRecordGrid(int nPos);

	const int EndEdit_Return = 0x10;
	
};