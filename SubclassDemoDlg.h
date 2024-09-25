// SubclassDemoDlg.h : header file
//

#if !defined(AFX_SUBCLASSDEMODLG_H__10CEB9D8_11F9_11D4_A2EA_0048543D92F7__INCLUDED_)
#define AFX_SUBCLASSDEMODLG_H__10CEB9D8_11F9_11D4_A2EA_0048543D92F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyButton.h"

/////////////////////////////////////////////////////////////////////////////
// CSubclassDemoDlg dialog

class CSubclassDemoDlg : public CDialog
{
// Construction
public:
	CSubclassDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSubclassDemoDlg)
	enum { IDD = IDD_SUBCLASSDEMO_DIALOG };
	CMyButton	m_button;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubclassDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSubclassDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBCLASSDEMODLG_H__10CEB9D8_11F9_11D4_A2EA_0048543D92F7__INCLUDED_)
