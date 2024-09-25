// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "SubclassDemo.h"
#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
    m_bOverControl = FALSE;
    m_nTimerID     = 1;
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

void CMyButton::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (!m_bOverControl)                    // Cursor has just moved over control
    {
        TRACE0("Entering control\n");

        m_bOverControl = TRUE;				// Set flag telling us the mouse is in
        Invalidate();                       // Force a redraw

        SetTimer(m_nTimerID, 100, NULL);    // Keep checking back every 1/10 sec
    }
	
	CButton::OnMouseMove(nFlags, point);    // drop through to default handler
}

void CMyButton::OnTimer(UINT nIDEvent) 
{
    // Where is the mouse?
    CPoint p(GetMessagePos());
    ScreenToClient(&p);

    // Get the bounds of the control (just the client area)
    CRect rect;
    GetClientRect(rect);

    // Check the mouse is inside the control
    if (!rect.PtInRect(p))
    {
        TRACE0("Leaving control\n");

        // if not then stop looking...
        m_bOverControl = FALSE;
        KillTimer(m_nTimerID);

        // ...and redraw the control
        Invalidate();
    }
	
	// drop through to default handler
	CButton::OnTimer(nIDEvent);
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;

	CString strText;
	GetWindowText(strText);

    // draw the control edges (DrawFrameControl is handy!)
	if (state & ODS_SELECTED)
        pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
    else
        pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

    // Fill the interior color if necessary
    
    rect.DeflateRect( CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
    if (m_bOverControl)
        pDC->FillSolidRect(rect, RGB(255, 255, 0)); // yellow

    // Draw the text
    if (!strText.IsEmpty())
    {
        CSize Extent = pDC->GetTextExtent(strText);
		CPoint pt( rect.CenterPoint().x - Extent.cx/2, rect.CenterPoint().y - Extent.cy/2 );

		if (state & ODS_SELECTED) 
            pt.Offset(1,1);

		int nMode = pDC->SetBkMode(TRANSPARENT);

		if (state & ODS_DISABLED)
			pDC->DrawState(pt, Extent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
			pDC->TextOut(pt.x, pt.y, strText);

        pDC->SetBkMode(nMode);
    }
}

void CMyButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW);	// make the button owner drawn
}