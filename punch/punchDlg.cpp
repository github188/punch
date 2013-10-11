
// punchDlg.cpp : ʵ���ļ�
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
#define WM_HAPPY_LEAVE WM_USER+2014
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CpunchDlg �Ի���




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
	ON_MESSAGE(WM_HAPPY_LEAVE,&CpunchDlg::OnHappyLeave)
	ON_WM_CLOSE()
	ON_COMMAND(ID_SYSTRAY_SHOW, &CpunchDlg::OnSystrayShow)
	ON_COMMAND(ID_SYSTRAY_QUIT, &CpunchDlg::OnSystrayQuit)
	ON_WM_POWERBROADCAST()
	ON_COMMAND(ID_SYSTRAY_HIBERNATION, &CpunchDlg::OnSystrayHibernation)
	ON_COMMAND(ID_SYSTRAY_SUSPEND, &CpunchDlg::OnSystraySuspend)
END_MESSAGE_MAP()


// CpunchDlg ��Ϣ�������

BOOL CpunchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->GetSafeHwnd();
	nid.uID = 201355;
	nid.uFlags = NIF_ICON | NIF_MESSAGE |NIF_TIP;
	nid.hIcon = m_hIcon;
	nid.uCallbackMessage = WM_MYSHELL_NOTIFY;
	nid.uVersion = NOTIFYICON_VERSION;  
	strcpy_s(nid.szTip , 11,"HappyLeave");

	Shell_NotifyIcon(NIM_ADD,&nid);
	::SetWindowPos(GetSafeHwnd(),HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	//this->ShowWindow(SW_HIDE);	//���ش���
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CpunchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		//this->ShowWindow(TRUE);
		
		KillTimer(1);
		ptime t(second_clock::local_time());
		std::string time = posix_time::to_iso_extended_string(t);
		SetDlgItemText(IDC_STATIC_PUNCH_OUT,time.c_str());
		//AfxMessageBox("Happy Leave!:)");

		PostMessage(WM_HAPPY_LEAVE,0,0);
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
	/*strcpy(nid.szTip , "HappyLeave");*/
	strcpy_s(nid.szTip , 11,"HappyLeave");
	Shell_NotifyIcon(NIM_ADD,&nid);
}

LRESULT CpunchDlg::OnMyTray(WPARAM wParam,LPARAM lParam)
{
	if(wParam!=201355)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:
		{
			/*LPPOINT lpoint=new tagPOINT;
			::GetCursorPos(lpoint);//�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();//����һ������ʽ�˵�
			//���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ���
			//���أ��������������
			menu.AppendMenu(MF_STRING,WM_DESTROY,"�ر�"); 
			//ȷ������ʽ�˵���λ��
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);
			//��Դ����
			HMENU hmenu=menu.Detach();
			menu.DestroyMenu();
			delete lpoint;*/
			//AfxMessageBox("rbuttonup");
			CMenu   menu;   //��������Ҫ�õ���cmenu����
			menu.LoadMenu(IDR_MENU_SYSTRAY); //װ���Զ�����Ҽ��˵� 
			CMenu   *pContextMenu=menu.GetSubMenu(0); //��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵� 
			CPoint point;//����һ������ȷ�����λ�õ�λ��  
			GetCursorPos(&point);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����  
			pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,   AfxGetMainWnd()); //��ָ��λ����ʾ�����˵�
		}
		break;
	case WM_LBUTTONDBLCLK://˫������Ĵ���
		{
			this->ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶�
			::SetWindowPos(GetSafeHwnd(),HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			this->GetFocus();
		}
		break;
	}
	return 0;
}
LRESULT CpunchDlg::OnHappyLeave(WPARAM wParam,LPARAM lParam)
{
	//doing much much working to tell "***"
	AfxMessageBox("OnHappyLeave");
	return 0;
}
void CpunchDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("onclose");
	this->ShowWindow(SW_HIDE);
	//this->SetFocus();//???
//	CDialog::OnClose();
}

void CpunchDlg::OnSystrayShow()
{
	// TODO: Add your command handler code here
	this->ShowWindow(SW_SHOW);
	::SetWindowPos(GetSafeHwnd(),HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	
}

void CpunchDlg::OnSystrayQuit()
{
	// TODO: Add your command handler code here
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->GetSafeHwnd();
	nid.uID = 201355;
	
	SetFocus();
	Shell_NotifyIcon(NIM_DELETE,&nid);
	CDialog::OnClose();
	DestroyWindow();
}

UINT CpunchDlg::OnPowerBroadcast(UINT nPowerEvent, UINT nEventData)
{
	//����һ��
	switch (nPowerEvent)
	{
	case PBT_APMRESUMESUSPEND://�ָ�
		//AfxMessageBox("PBT_APMRESUMESUSPEND");
		//��ϵͳ�ָ���ʼ�Զ���ʱ
		KillTimer(1);
		m_mytime.Init();
		SetDlgItemText(IDC_STATIC_PUNCH_IN,m_mytime.time_start_str().c_str());
		SetDlgItemText(IDC_STATIC_PUNCH_OUT,m_mytime.time_end_str().c_str());
		OnSystrayShow();
		SetTimer(1, 1000, NULL);
		break;
	case PBT_APMSUSPEND://������� or ����
		//KillTimer(1);
		//AfxMessageBox("PBT_APMSUSPEND");
		//OnSystrayQuit();

		break;
	default:
		;
	}
		return CDialog::OnPowerBroadcast(nPowerEvent, nEventData);
}

void CpunchDlg::OnSystrayHibernation()
{
	// TODO: Add your command handler code here
	if(IDCANCEL == MessageBox("ϵͳ˯��","����",MB_OKCANCEL)) return;
	static HANDLE hToken;
	static TOKEN_PRIVILEGES tp;
	static LUID luid;
	if(::OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,
		&hToken))
	{
		::LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&luid);
		tp.PrivilegeCount=1;
		tp.Privileges[0].Luid =luid;
		tp.Privileges[0].Attributes =SE_PRIVILEGE_ENABLED;
		::AdjustTokenPrivileges(hToken,false,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL);
	}
	::SetSystemPowerState(false,true); 
}

void CpunchDlg::OnSystraySuspend()
{
	// TODO: Add your command handler code here
	if(IDCANCEL == MessageBox("ϵͳ����","����",MB_OKCANCEL|MB_ICONWARNING)) return;
	static HANDLE hToken;
	static TOKEN_PRIVILEGES tp;
	static LUID luid;
	if(::OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,
		&hToken))
	{
		::LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&luid);
		tp.PrivilegeCount=1;
		tp.Privileges[0].Luid =luid;
		tp.Privileges[0].Attributes =SE_PRIVILEGE_ENABLED;
		::AdjustTokenPrivileges(hToken,false,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL);
	}
	//KillTimer(1);
	::SetSystemPowerState(true,true);//����������ٷ��� PBT_APMSUSPEND ��Ϣ

}
