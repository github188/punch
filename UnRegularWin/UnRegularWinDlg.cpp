
// UnRegularWinDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UnRegularWin.h"
#include "UnRegularWinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CUnRegularWinDlg 对话框




CUnRegularWinDlg::CUnRegularWinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnRegularWinDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUnRegularWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUnRegularWinDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CUnRegularWinDlg 消息处理程序

BOOL CUnRegularWinDlg::OnInitDialog()
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
	ModifyStyle(WS_CAPTION, 0); // 去掉窗体的的标题栏，这样看起来更美观
	int cx,cy;
	cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN);
	
	CRect rcTemp;
	rcTemp.BottomRight() = CPoint(cx, cy);
	rcTemp.TopLeft() = CPoint(0, 0);
	MoveWindow(&rcTemp);
	HRGN wndRgn;  
	CClientDC dc(this);  
	CFont mFont;  
	if (dc.m_hDC!=NULL)  { 
		CPoint ZbPoints[4] = {CPoint(0,0),CPoint(cx/2,0),CPoint(cx/2,cy),CPoint(cx,cy)}; 
		CPoint ZbPoints2[4] = {CPoint(cx,cy-10),CPoint(cx/2+10,cy),CPoint(cx/2+10,0),CPoint(10,10)}; 
		//开始记录窗体轮廓路径  
		dc.BeginPath();   
		//设置背景为透明模式,这句话是必须有的。   
		dc.SetBkMode(TRANSPARENT); 
		CPen penBlue(PS_SOLID, 5, RGB(0, 0, 255));
		CPen* pOldPen = dc.SelectObject(&penBlue);
		dc.MoveTo(0,0);
		BOOL ft = dc.PolyBezier(ZbPoints,4);
		dc.MoveTo(cx,cy);
		dc.LineTo(cx,cy-10);
		ft = dc.PolyBezier(ZbPoints2,4);
		
		dc.MoveTo(10,10);		
		dc.LineTo(0,0);
		//dc.MoveTo(cx,cy);
		//dc.LineTo(10,10);
		
		
		//dc.LineTo(0,cy);
		//dc.LineTo(cx,cy);
		//dc.LineTo(0,0);
		//dc.CloseFigure();
		//dc.ArcTo(&rcTemp,CPoint(cx/2,0),CPoint(cx,cy/2));
		//dc.Arc(&rcTemp,CPoint(0,cy/2),CPoint(cx/2,cy));
		//结束记录窗体轮廓路径   
		dc.SelectObject( pOldPen ); 
		dc.EndPath();  
		//把所记录的路径转化为窗体轮廓句柄   
		wndRgn = ::PathToRegion(dc.m_hDC);  
		//赋予窗体指定的轮廓形状  
		
		this->SetWindowRgn(wndRgn, TRUE);
		//::DeleteObject(wndRgn);
	}
	/*HRGN wndRgn;  
	CClientDC dc(this);  
	CFont mFont;  
	if (dc.m_hDC!=NULL)  { 
		VERIFY(mFont.CreateFont(200, 50, 0, 0, FW_HEAVY, TRUE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,  
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "宋体"));   
		//开始记录窗体轮廓路径  
		dc.BeginPath();   
		//设置背景为透明模式,这句话是必须有的。   
		dc.SetBkMode(TRANSPARENT);   
		CFont * pOldFont; 
		pOldFont = dc.SelectObject( &mFont );   
		dc.TextOut(0, 0, "Hello");  
		//结束记录窗体轮廓路径   
		dc.SelectObject( pOldFont );  
		dc.EndPath();  
		//把所记录的路径转化为窗体轮廓句柄   
		wndRgn = ::PathToRegion(dc.m_hDC);  
		//赋予窗体指定的轮廓形状  
		this->SetWindowRgn(wndRgn, TRUE);
	}*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUnRegularWinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUnRegularWinDlg::OnPaint()
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
HCURSOR CUnRegularWinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

