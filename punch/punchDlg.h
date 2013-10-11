
// punchDlg.h : ͷ�ļ�
//

#pragma once
#include "myworktime.h"

// CpunchDlg �Ի���
class CpunchDlg : public CDialog
{
// ���� 
public:
	CpunchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PUNCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
