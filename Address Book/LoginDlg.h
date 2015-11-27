#pragma once
#include "afxwin.h"


// CLoginDlg 对话框

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_login };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	LinkList_Users L_login;
	CString username;
	CString password;
	CButton button_ok;
	afx_msg void OnBnClickedButtonclick();
	BOOL PreTranslateMessage(MSG* pMsg);
};
