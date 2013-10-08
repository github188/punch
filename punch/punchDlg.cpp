
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
	: CDialog(CpunchDlg::IDD, pParent)
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


void CpunchDlg::OnBnClickedButtonStartTime()
{
	// TODO: Add your control notification handler code 
	/*
using namespace boost;
	using namespace local_time;
	using namespace gregorian;
	using posix_time::time_duration;

	/ ***** custom_time_zone ***** /

	// create the dependent objects for a custom_time_zone
	time_zone_names tzn("Eastern Standard Time", "EST",
		"Eastern Daylight Time", "EDT");
	time_duration utc_offset(-5,0,0);
	dst_adjustment_offsets adj_offsets(time_duration(1,0,0), 
		time_duration(2,0,0), 
		time_duration(2,0,0));
	// rules for this zone are:
	// start on first Sunday of April at 2 am
	// end on last Sunday of October at 2 am
	// so we use a first_last_dst_rule
	first_day_of_the_week_in_month start_rule(Sunday, Apr);
	last_day_of_the_week_in_month    end_rule(Sunday, Oct);
	shared_ptr<dst_calc_rule> nyc_rules(new first_last_dst_rule(start_rule, 
		end_rule));
	// create more dependent objects for a non-dst custom_time_zone
	time_zone_names tzn2("Mountain Standard Time", "MST",
		"", ""); // no dst means empty dst strings
	time_duration utc_offset2(-7,0,0);
	dst_adjustment_offsets adj_offsets2(time_duration(0,0,0), 
		time_duration(0,0,0), 
		time_duration(0,0,0));
	// no dst means we need a null pointer to the rules
	shared_ptr<dst_calc_rule> phx_rules;

	// create the custom_time_zones
	time_zone_ptr nyc_1(new custom_time_zone(tzn, utc_offset, 
		adj_offsets, nyc_rules));
	time_zone_ptr phx_1(new custom_time_zone(tzn2, utc_offset2, 
		adj_offsets2, phx_rules));

	/ ***** posix_time_zone ***** /

	// create posix_time_zones that are the duplicates of the 
	// custom_time_zones created above. See posix_time_zone documentation 
	// for details on full zone names.
	std::string nyc_string, phx_string;
	nyc_string = "EST-05:00:00EDT+01:00:00,M4.1.0/02:00:00,M10.5.0/02:00:00";
	// nyc_string = "EST-05EDT,M4.1.0,M10.5.0"; // shorter when defaults used
	phx_string = "MST-07"; // no-dst
	time_zone_ptr nyc_2(new posix_time_zone(nyc_string));
	time_zone_ptr phx_2(new posix_time_zone(phx_string));


	/ ***** show the sets are equal ***** /

	std::cout << "The first zone is in daylight savings from:\n " 
		<< nyc_1->dst_local_start_time(2004) << " through "
		<< nyc_1->dst_local_end_time(2004) << std::endl;

	std::cout << "The second zone is in daylight savings from:\n " 
		<< nyc_2->dst_local_start_time(2004) << " through "
		<< nyc_2->dst_local_end_time(2004) << std::endl;

	std::cout << "The third zone (no daylight savings):\n " 
		<< phx_1->std_zone_abbrev() << " and "
		<< phx_1->base_utc_offset() << std::endl;

	std::cout << "The fourth zone (no daylight savings):\n " 
		<< phx_2->std_zone_abbrev() << " and "
		<< phx_2->base_utc_offset() << std::endl;
*/
	using namespace boost;
	using namespace local_time;
	using namespace gregorian;
	using namespace posix_time;
	//date d(day_clock::local_day());
	ptime t(second_clock::local_time());
	std::string time = posix_time::to_iso_string( t);
}
