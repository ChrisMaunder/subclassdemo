# Create your own controls - the art of subclassing

An introduction to subclassing the Windows common controls using MFC



## Introduction

There are many windows common controls that you as a programmer can use to provide
an interface to an application. Everything from lists to buttons to progress controls
are available. Even so, there will often come a time when the standard selection of
controls - diverse as they are - are just not enough. Welcome to the gentle art of
subclassing controls.

Subclassing a window control is not the same as subclassing a C++ class. Subclassing
a control means you replace some or all of the message handlers of a window with your
own. You effectively hijack the control and make it behave the way you want, not the
way Windows wants. This allows you to take a control that is almost, but not quite, what
you want, and make it perfect. There are two types of subclassing: *instance subclassing*
 and *global subclassing*. Instance subclassing is when you subclass a single instance
 of a window. Global subclassing subclasses *all* windows of a particular type with
 your own version. We'll only discuss single instance here.

It's important to remember the distinction between an object derived from `CWnd` and the window itself (a `HWND`). You C++ `CWnd`-derived object contains a member variable that points to a `HWND`, and contains functions that the `HWND` message pump calls when processing messages (eg `WM_PAINT`, `WM_MOUSEMOVE`). When you subclass a window with your C++ object, you are attaching that `HWND` to your C++ object and setting that objects callback functions as the one the message pump for that `HWND` will invoke.

Subclassing is easy. First you create a class that will handle all the windows messages
you are interested in, and then you physically subclass an exising window and make it
behave the way your new class dictates. The window becomes possessed, in a way. For this 
example we'll subclass a button control and make it do things it never knew it was capable 
of.

## A New Class

To subclass a control we need to create a new class that handles all the windows 
messages we are interested in. Since we are lazy it's best to minimise the number of
messages you actually have to deal with, and the best way of doing this is by deriving
your class from the control class you are subclassing. In our case `CButton`.

Lets assume we want to do something bizarre like make the button glow bright yellow
everytime the mouse moves over it. Stranger things have been done. First thing we do is
use ClassWizard to create a new class derived from `CButton` called 
`CMyButton`.

![Adding a new class](https://raw.githubusercontent.com/ChrisMaunder/subclassdemo/master/docs/assets/SubclassDemo2.gif) 

Deriving from `CButton` within the MFC framework has a lot of advantages,
with the biggest one being we don't actually have to add a single line of code for our
class to be a fully functioning windows control. If we wished we could move onto the
next step and subclass a button control with our new class and we would have a perfectly
functioning, though somewhat boring, button control. This is becuase MFC implements default
handlers for all it's messages, so we can simply pick the ones we are interested in, and
ignore the others.

However for this example we have loftier plans for our control - making it bright yellow.

To check if the mouse is over the control we will set a variable *m\_bOverControl* to
TRUE when the mouse enters the control, and then check periodically (using a timer) to
keep track of when the mouse leaves the control. Unfortunately for us there is no
`OnMouseEnter` and `OnMouseLeave` function that can be used across
platforms, so we have to make do with using `OnMouseMove`. If, on a timer tick, 
we find the mouse is no longer in the control we turn off the timer and redraw the control. 

Use ClassWizard to add a WM\_MOUSEMOVE and WM\_TIMER message handlers mapped to `OnMouseMove` 
and `OnTimer` respectively.

![Adding message handlers](https://raw.githubusercontent.com/ChrisMaunder/subclassdemo/master/docs/assets/SubclassDemo3.gif) 

ClassWizard will add the following code to your new button class:

```cpp
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
    // TODO: Add your message handler code here and/or call default

    CButton::OnMouseMove(nFlags, point);
}

void CMyButton::OnTimer(UINT nIDEvent) 
{
    // TODO: Add your message handler code here and/or call default

    CButton::OnTimer(nIDEvent);
}
```

The message map entries (in the `BEGIN_MESSAGE_MAP` section) map the
windows message to the function. `ON_WM_MOUSEMOVE` maps WM\_MOUSEMOVE 
to your `OnMouseMove` function, and `ON_WM_TIMER` maps WM\_TIMER
to `OnTimer`. These macros are defined in the MFC source, but they
are *not* required reading. For this excercise simply have faith that they do their job.

Assuming we have declared two variables *m\_bOverControl* and *m\_nTimerID* of
type BOOL and UINT respectively, and initialised them in the constructor, our message
handlers will be as follows

```cpp
void CMyButton::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (!m_bOverControl)                    // Cursor has just moved over control
    {
        TRACE0("Entering control\n");

        m_bOverControl = TRUE;              // Set flag telling us the mouse is in
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
```

The final piece of our new class is drawing, and for this we don't handle a message,
but rather override the `CWnd::DrawItem` virtual function. This function is
**only** called for owner-drawn controls, and does not have a default implementation
that can be called (it ASSERT's if you try). This function is designed to be overriden 
and used by derived classes only.

![Adding DrawItem override](https://raw.githubusercontent.com/ChrisMaunder/subclassdemo/master/docs/assets/SubclassDemo5.gif) 

Use the ClassWizard to add a `DrawItem` override and add in the following
code

```cpp
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

    // Deflate the drawing rect by the size of the button's edges
    rect.DeflateRect( CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
    
    // Fill the interior color if necessary
    if (m_bOverControl)
        pDC->FillSolidRect(rect, RGB(255, 255, 0)); // yellow

    // Draw the text
    if (!strText.IsEmpty())
    {
        CSize Extent = pDC->GetTextExtent(strText);
        CPoint pt( rect.CenterPoint().x - Extent.cx/2, 
        rect.CenterPoint().y - Extent.cy/2 );

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
```

Everything is now in place - but there is one last step. The `DrawItem`
function requires that the control be owner drawn. This can be achieved in the dialog
resource editor by checking the appropriate box - but a far nicer way is to have the
class itself set the style of the window it is subclassing automatically in order to make the class a true
"drop-in" replacement for `CButton`. To do this we override a final function:
`PreSubclassWindow`.

This function is called by `SubclassWindow`, which in turn is called by
either `CWnd::Create` or `DDX_Control`, meaning that if you created
an instance of you new class either dynamically or by using a dialog template, `PreSubclassWindow`
will still be called. `PreSubclassWindow` will be called after the window you are 
subclassing has been created, but before it becomes visible after you subclass it. In other 
words - a perfect time to perform initialisation that requires the window to be present.

An important note here: if you create a control using a dialog resource, then your subclassed
control **will not** see the WM\_CREATE message, hance we cannot use `OnCreate` for
our initialisation, since it won't be called in all cases.

Use ClassWizard to override `PreSubclassWindow` and add the following code

```cpp
void CMyButton::PreSubclassWindow() 
{
    CButton::PreSubclassWindow();

    ModifyStyle(0, BS_OWNERDRAW);    // make the button owner drawn
}
```

Congratulations - you now have a `Cbutton` derived class!

## The Subclass

### Using DDX to subclass a window at creation time

In this example I'm working with a dialog on which I've placed a button control:

![a button](https://raw.githubusercontent.com/ChrisMaunder/subclassdemo/master/docs/assets/SubclassDemo1.gif) 

We let the normal dialog creation routines create the dialog with the control, and
use the `DDX_...` routines to subclass the control with our new class. To
do this simply use ClassWizard to add a member variable to you dialog class attached
to your button control (in my case it's ID is `IDC_BUTTON1`), and choose the variable
as a Control type, with class name `CMyButton`.

![subclassing the control](https://raw.githubusercontent.com/ChrisMaunder/subclassdemo/master/docs/assets/SubclassDemo4.gif) 

The ClassWizard generates a `DDX_Control` call in your dialog's
`DoDataExchange` function. `DDX_Control` calls 
`SubclassWindow` which causes the button to use the  `CMyButton`
message handlers instead of the usual  `CButton` handlers. The button
has been hijacked and will behave from now on the way we want it to. 

### Subclassing a window using a class not recognised by the ClassWizard

If you have added a window class to your project and want to subclass a window
with an object of this new class' type, but the ClassWizard isn't offering you that
new object's type as an option, then you may need to rebuild the class wizard file.

Make a backup of your projects .clw file, delete the original file, then go into
Visual Studio and hit Ctrl+W. You will then be prompted for which files you want to
have included in the class scan. Ensure that the new class files are included!

Your new class should now be available as an option. If not, then you can always
use the classwizard to subclass you control as a generic control (say, `CButton`)
and then go into the header file manually and change this to the class that you
want (eg `CMyButton`).

### Subclassing an existing window

Using DDX is simple, but doesn't help us if we need to subclass a control that
already exists. For instance, say you want to subclass the Edit control in a combobox.
You need to have the combobox (and hence it's child edit window) already created
before you can subclass the edit window.

In this case you make use of the handy `SubclassDlgItem` or `SubclassWindow` functions. These two functions allow you to dynamically
subclass a window - in other words, attach an object of your new window class type
to an existing window. 

For example, suppose we have a dialog containing a button with ID `IDC_BUTTON1`. That button has already been created and we want to associate
that button with an object of type `CMyButton` so that the button behaves
in the manner we want.

To do this we need to have an object of our new type already created. A member
variable of your dialog or view class is perfect.

```cpp
CMyButton m_btnMyButton;
```

Then call in your dialog's `OnInitDialog` (or whereever is appropriate) call

```cpp
m_btnMyButton.SubclassDlgItem(IDC_BUTTON1, this);
```

Alternatively suppose you already have a pointer to a window you wish to subclass, or you are working within a `CView` or other `CWnd` derived class where the controls are created dynamically or you dont't wish to use `SubclassDlgItem`. Simply call

```cpp
CWnd* pWnd = GetDlgItem(IDC_BUTTON1); // or use some other method to get
                                      // a pointer to the window you wish
                                      // to subclass
ASSERT( pWnd && pWnd->GetSafeHwnd() );
m_btnMyButton.SubclassWindow(pWnd->GetSafeHwnd());
```

The button drawing is very simple and does not take into account button styles
such as flat buttons, or justified text, but scope is there for you to do whatever 
you wish. If you compile and run the accompanying code you'll see a simple button 
that turns bright yellow when the mouse passes over it.

![The finished product](https://raw.githubusercontent.com/ChrisMaunder/subclassdemo/master/docs/assets/SubclassDemo6.gif) 

Notice that we only really overrode the drawing functionality, and intercepted the
mouse movement functions (but passed these on to the default handler). This means that
the control is still, deep down, a button. Add a button click handler to your dialog
class and you'll see it will still get called.

## Conclusion

Subclassing is not hard - you just need to choose the 
class you wish to subclass carefully, and be aware of what messages you need to 
handle. Read up on the control you are subclassing - learn about the messages it handles
and also the virtual member functions of its implementation class. Once you've hooked 
into a control and taken over it's inner workings the sky's the limit.

## History

26 Oct 2001 - added info in SubclassWindow and SubclassDlgItem
