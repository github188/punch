
// punchDlg.h : 头文件
//

#pragma once
#include "myworktime.h"

// CpunchDlg 对话框
class CpunchDlg : public CDialog
{
// 构造 
public:
	CpunchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PUNCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStartTime();
	afx_msg void OnBnClickedButtonLeaveTime();
private:
	CMyWorkTime m_mytime;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonForTest();
	afx_msg LRESULT OnMyTray(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnHappyLeave(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSystrayShow();
	afx_msg void OnSystrayQuit();
	afx_msg UINT OnPowerBroadcast(UINT nPowerEvent, UINT nEventData);
	afx_msg void OnSystrayHibernation();
	afx_msg void OnSystraySuspend();
};
