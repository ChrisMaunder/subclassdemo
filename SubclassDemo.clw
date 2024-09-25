; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyButton
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SubclassDemo.h"

ClassCount=4
Class1=CSubclassDemoApp
Class2=CSubclassDemoDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SUBCLASSDEMO_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Class4=CMyButton
Resource5=IDD_SUBCLASSDEMO_DIALOG (English (U.S.))

[CLS:CSubclassDemoApp]
Type=0
HeaderFile=SubclassDemo.h
ImplementationFile=SubclassDemo.cpp
Filter=N

[CLS:CSubclassDemoDlg]
Type=0
HeaderFile=SubclassDemoDlg.h
ImplementationFile=SubclassDemoDlg.cpp
Filter=D
LastObject=IDC_BUTTON1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SubclassDemoDlg.h
ImplementationFile=SubclassDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_SUBCLASSDEMO_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSubclassDemoDlg

[DLG:IDD_SUBCLASSDEMO_DIALOG (English (U.S.))]
Type=1
Class=CSubclassDemoDlg
ControlCount=2
Control1=IDCANCEL,button,1342242816
Control2=IDC_BUTTON1,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CMyButton]
Type=0
HeaderFile=MyButton.h
ImplementationFile=MyButton.cpp
BaseClass=CButton
Filter=W
LastObject=CMyButton
VirtualFilter=BWC

