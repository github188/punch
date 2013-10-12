
// UnRegularWinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UnRegularWin.h"
#include "UnRegularWinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CUnRegularWinDlg �Ի���




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


// CUnRegularWinDlg ��Ϣ�������

BOOL CUnRegularWinDlg::OnInitDialog()
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
	ModifyStyle(WS_CAPTION, 0); // ȥ������ĵı�����������������������
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
		//��ʼ��¼��������·��  
		dc.BeginPath();   
		//���ñ���Ϊ͸��ģʽ,��仰�Ǳ����еġ�   
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
		//������¼��������·��   
		dc.SelectObject( pOldPen ); 
		dc.EndPath();  
		//������¼��·��ת��Ϊ�����������   
		wndRgn = ::PathToRegion(dc.m_hDC);  
		//���贰��ָ����������״  
		
		this->SetWindowRgn(wndRgn, TRUE);
		//::DeleteObject(wndRgn);
	}
	/*HRGN wndRgn;  
	CClientDC dc(this);  
	CFont mFont;  
	if (dc.m_hDC!=NULL)  { 
		VERIFY(mFont.CreateFont(200, 50, 0, 0, FW_HEAVY, TRUE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,  
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����"));   
		//��ʼ��¼��������·��  
		dc.BeginPath();   
		//���ñ���Ϊ͸��ģʽ,��仰�Ǳ����еġ�   
		dc.SetBkMode(TRANSPARENT);   
		CFont * pOldFont; 
		pOldFont = dc.SelectObject( &mFont );   
		dc.TextOut(0, 0, "Hello");  
		//������¼��������·��   
		dc.SelectObject( pOldFont );  
		dc.EndPath();  
		//������¼��·��ת��Ϊ�����������   
		wndRgn = ::PathToRegion(dc.m_hDC);  
		//���贰��ָ����������״  
		this->SetWindowRgn(wndRgn, TRUE);
	}*/
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUnRegularWinDlg::OnPaint()
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
HCURSOR CUnRegularWinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

