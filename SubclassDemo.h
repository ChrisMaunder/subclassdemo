// SubclassDemo.h : main header file for the SUBCLASSDEMO application
//

#if !defined(AFX_SUBCLASSDEMO_H__10CEB9D6_11F9_11D4_A2EA_0048543D92F7__INCLUDED_)
#define AFX_SUBCLASSDEMO_H__10CEB9D6_11F9_11D4_A2EA_0048543D92F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSubclassDemoApp:
// See SubclassDemo.cpp for the implementation of this class
//

class CSubclassDemoApp : public CWinApp
{
public:
	CSubclassDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubclassDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSubclassDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBCLASSDEMO_H__10CEB9D6_11F9_11D4_A2EA_0048543D92F7__INCLUDED_)
