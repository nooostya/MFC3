
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
	virtual LRESULT OnEndGridLabelEdit(WPARAM wp, LPARAM lp) = 0;
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
		if (m_listener!=0){
		m_listener->OnGridItemChanged(pItem, nRow, nColumn);
		}
	}
	int InsertNewRecord(int nPos) {
		if (m_listener != 0) {
			m_listener->InsertNewRecordGrid(nPos);
		}
		return 0;
	}
	LRESULT OnEndLabelEdit(WPARAM wp, LPARAM lp) {
		if (m_listener != 0) {
			m_listener->OnEndGridLabelEdit(wp,lp);
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

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	BOOL	m_bOption6; // Move to the next row on ENTER
	BOOL	m_bOption7; // Add new row after last row on ENTER/DOWN
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
	virtual void OnGridItemChanged(CBCGPGridItem *  pItem, int nRow, int nColumn);
	virtual int InsertNewRecordGrid(int nPos);

	afx_msg LRESULT OnEndGridLabelEdit(WPARAM, LPARAM lp);

	void OnInplaceGridEditEnter(CBCGPGridItem * pItem);

	void ContinueInplaceEditing();


	MyGridControl nGrid;
	SQL data;
	enum EndEditResultFlags
	{
		EndEdit_NoResult = 0x0,
		EndEdit_OK = 0x1,
		EndEdit_Cancel = 0x2,
		EndEdit_AutoApply = 0x4,

		// Key reasons:
		EndEdit_Return = 0x10,
		EndEdit_Tab = 0x20,
		EndEdit_Left = 0x40,
		EndEdit_Right = 0x80,
		EndEdit_Up = 0x100,
		EndEdit_Down = 0x200,
		EndEdit_Escape = 0x400,
		EndEdit_Shift = 0x1000,
		EndEdit_Ctrl = 0x2000,
		EndEdit_Home = 0x4000,
		EndEdit_End = 0x8000,
		EndEdit_KeyMask = 0xfff0,

		// Activation reasons:
		EndEdit_KillFocus = 0x10000,
		EndEdit_Selection = 0x20000,
		EndEdit_Layout = 0x40000
	};
	enum Direction
	{
		NoMove = 0x0,
		Up = 0x1,
		Down = 0x2,
		Left = 0x4,
		Right = 0x8,

		PrevColumn = 0x10,
		NextColumn = 0x20,
		FirstColumn = 0x40,
		LastColumn = 0x80,

		PrevRow = 0x100,
		NextRow = 0x200,
		FirstRow = 0x400,
		LastRow = 0x800
	};
};