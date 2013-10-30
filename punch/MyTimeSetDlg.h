#pragma once


// CMyTimeSetDlg dialog

class CMyTimeSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyTimeSetDlg)

public:
	CMyTimeSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyTimeSetDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_hours;
	int m_minitus;
	int m_seconds;
};
