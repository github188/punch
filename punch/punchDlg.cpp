
// punchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "punch.h"
#include "punchDlg.h"

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost\date_time\local_time\local_time.hpp"
//#include "boost/date_time/posix_time/time_formatters.hpp"
//#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_MYSHELL_NOTIFY WM_USER+2013
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CpunchDlg 对话框




CpunchDlg::CpunchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CpunchDlg::IDD, pParent),m_mytime(0,0)//8,1 for test
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpunchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CpunchDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_START_TIME, &CpunchDlg::OnBnClickedButtonStartTime)
	ON_BN_CLICKED(IDC_BUTTON_LEAVE_TIME, &CpunchDlg::OnBnClickedButtonLeaveTime)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_FOR_TEST, &CpunchDlg::OnBnClickedButtonForTest)
	ON_MESSAGE(WM_MYSHELL_NOTIFY,&CpunchDlg::OnMyTray)
	ON_WM_CLOSE()
	ON_COMMAND(ID_SYSTRAY_SHOW, &CpunchDlg::OnSystrayShow)
	ON_COMMAND(ID_SYSTRAY_QUIT, &CpunchDlg::OnSystrayQuit)
END_MESSAGE_MAP()


// CpunchDlg 消息处理程序

BOOL CpunchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpunchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpunchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpunchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

using namespace boost;
using namespace local_time;
using namespace gregorian;
using namespace posix_time;

void CpunchDlg::OnBnClickedButtonStartTime()
{
	// TODO: Add your control notification handler code 
	
	//date d(day_clock::local_day());
	m_mytime.Init();
	SetTimer(1, 1000, NULL);
	ptime t(second_clock::local_time());
	std::string time = posix_time::to_iso_extended_string(t);
	SetDlgItemText(IDC_STATIC_PUNCH_IN,time.c_str());
}

void CpunchDlg::OnBnClickedButtonLeaveTime()
{
	// TODO: Add your control notification handler code here
	//ptime t(second_clock::local_time());
	ptime noon (day_clock::local_day());
	noon+=time_duration(12,0,0);
	std::string time = posix_time::to_iso_extended_string(noon);
	SetDlgItemText(IDC_STATIC_PUNCH_OUT,time.c_str());
	//time_period 
}

void CpunchDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(m_mytime.LeaveHappy())
	{
		this->ShowWindow(TRUE);
		this->GetFocus();
		KillTimer(1);
		ptime t(second_clock::local_time());
		std::string time = posix_time::to_iso_extended_string(t);
		SetDlgItemText(IDC_STATIC_PUNCH_OUT,time.c_str());
		AfxMessageBox("Happy Leave!:)");
	}

	CDialog::OnTimer(nIDEvent);
}

typedef HRESULT (__stdcall *PDllGetVersion)(DLLVERSIONINFO *pdvi);

void CpunchDlg::OnBnClickedButtonForTest()
{
	// TODO: Add your control notification handler code here
	HMODULE libshell =  LoadLibrary ("shell32.dll");
	PDllGetVersion func_ver = (PDllGetVersion)GetProcAddress(libshell,"DllGetVersion");
	DLLVERSIONINFO dvi;
	dvi.cbSize = sizeof(DLLVERSIONINFO);
	if(S_OK == func_ver(/*(DLLVERSIONINFO*)(void*)*/&dvi))
	{
		dvi;	
	}
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->GetSafeHwnd();
	nid.uID = 201355;
	nid.uFlags = NIF_ICON | NIF_MESSAGE |NIF_TIP;
	nid.hIcon = m_hIcon;
	nid.uCallbackMessage = WM_MYSHELL_NOTIFY;
	nid.uVersion = NOTIFYICON_VERSION;  
	strcpy(nid.szTip , "HappyLeave");

	Shell_NotifyIcon(NIM_ADD,&nid);
}

LRESULT CpunchDlg::OnMyTray(WPARAM wParam,LPARAM lParam)
{
	if(wParam!=201355)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
		{
			/*LPPOINT lpoint=new tagPOINT;
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();//声明一个弹出式菜单
			//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已
			//隐藏），将程序结束。
			menu.AppendMenu(MF_STRING,WM_DESTROY,"关闭"); 
			//确定弹出式菜单的位置
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);
			//资源回收
			HMENU hmenu=menu.Detach();
			menu.DestroyMenu();
			delete lpoint;*/
			//AfxMessageBox("rbuttonup");
			CMenu   menu;   //定义下面要用到的cmenu对象
			menu.LoadMenu(IDR_MENU_SYSTRAY); //装载自定义的右键菜单 
			CMenu   *pContextMenu=menu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单 
			CPoint point;//定义一个用于确定光标位置的位置  
			GetCursorPos(&point);//获取当前光标的位置，以便使得菜单可以跟随光标  
			pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,   AfxGetMainWnd()); //在指定位置显示弹出菜单
		}
		break;
	case WM_LBUTTONDBLCLK://双击左键的处理
		{
			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
		}
		break;
	}
	return 0;
}
void CpunchDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("onclose");
	this->ShowWindow(SW_HIDE);
//	CDialog::OnClose();
}

void CpunchDlg::OnSystrayShow()
{
	// TODO: Add your command handler code here
	this->ShowWindow(SW_SHOW);
}

void CpunchDlg::OnSystrayQuit()
{
	// TODO: Add your command handler code here
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->GetSafeHwnd();
	nid.uID = 201355;
	

	Shell_NotifyIcon(NIM_DELETE,&nid);
	CDialog::OnClose();
	DestroyWindow();
}
