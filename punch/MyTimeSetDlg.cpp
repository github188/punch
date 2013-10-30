// MyTimeSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "punch.h"
#include "MyTimeSetDlg.h"


// CMyTimeSetDlg dialog

IMPLEMENT_DYNAMIC(CMyTimeSetDlg, CDialog)

CMyTimeSetDlg::CMyTimeSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyTimeSetDlg::IDD, pParent)
	, m_hours(0)
	, m_minitus(0)
	, m_seconds(0)
{

}

CMyTimeSetDlg::~CMyTimeSetDlg()
{
}

void CMyTimeSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOURS, m_hours);
	DDV_MinMaxInt(pDX, m_hours, 0, 23);
	DDX_Text(pDX, IDC_EDIT_MINITUS, m_minitus);
	DDV_MinMaxInt(pDX, m_minitus, 0, 59);
	DDX_Text(pDX, IDC_EDIT_SECONDS, m_seconds);
	DDV_MinMaxInt(pDX, m_seconds, 0, 59);
}


BEGIN_MESSAGE_MAP(CMyTimeSetDlg, CDialog)
END_MESSAGE_MAP()


// CMyTimeSetDlg message handlers
