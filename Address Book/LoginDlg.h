#pragma once
#include "afxwin.h"


// CLoginDlg �Ի���

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_login };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	LinkList_Users L_login;
	CString username;
	CString password;
	CButton button_ok;
	afx_msg void OnBnClickedButtonclick();
	BOOL PreTranslateMessage(MSG* pMsg);
};
