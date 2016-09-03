; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConnectDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "netchess.h"
LastPage=0

ClassCount=1

ResourceCount=3
Resource1=IDC_NETCHESS
Resource2=IDD_ABOUTBOX
Class1=CConnectDialog
Resource3=IDD_CONNECT (English (U.S.))

[MNU:IDC_NETCHESS]
Type=1
Class=?
Command1=ID_NEW
Command2=IDC_WAIT
Command3=ID_CONNECT
Command4=IDM_EXIT
Command5=IDM_ABOUT
CommandCount=5

[DLG:IDD_CONNECT (English (U.S.))]
Type=1
Class=CConnectDialog
ControlCount=5
Control1=IDC_CONNECT,button,1342242816
Control2=IDC_IP,SysIPAddress32,1342242816
Control3=IDC_PORT,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[ACL:IDC_NETCHESS]
Type=1
Class=?
Command1=IDM_ABOUT
Command2=IDM_ABOUT
CommandCount=2

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=9
Control1=IDC_MYICON,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_CONNECT,button,1342242816
Control6=IDC_IP,SysIPAddress32,1342242816
Control7=IDC_PORT,edit,1350639744
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:CConnectDialog]
Type=0
HeaderFile=ConnectDialog.h
ImplementationFile=ConnectDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CConnectDialog
VirtualFilter=dWC

