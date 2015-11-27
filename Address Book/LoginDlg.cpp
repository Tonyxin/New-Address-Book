// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Address Book.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, username(_T(""))
	, password(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_name, username);
	DDX_Text(pDX, IDC_EDIT_password, password);
	DDX_Control(pDX, IDC_BUTTON_click, button_ok);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_click, &CLoginDlg::OnBnClickedButtonclick)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButtonclick()
{
	// TODO:  在此添加控件通知处理程序代码
	CString user_name;					//账户
	CString user_password;				//密码
	GetDlgItem(IDC_EDIT_name)->GetWindowTextW(user_name);			//将输入的字符串保存到相应的变量中
	GetDlgItem(IDC_EDIT_password)->GetWindowTextW(user_password);
	bool name_mark=0;					//验证账号是否正确
	bool password_mark = 0;			//验证密码是否正确
	LinkList_Users L_logintemp = L_login;
	while (L_logintemp->next)
	{
		L_logintemp = L_logintemp->next;
		if (L_logintemp->data.user_name == user_name)						//输入账户为数据库中已有账户
		{
			name_mark = 1;
			if (L_logintemp->data.user_password == user_password)     //检查响应密码是否正确
			{
				password_mark = 1;
				::SendMessage(this->GetParent()->m_hWnd, WM_RECEV_USER, 0, (LPARAM)(&(L_logintemp->data.user_id)));
				break;
			}//if
		}//if
	}//while

	if (name_mark&&password_mark)	OnOK();
	else if (name_mark && (!password_mark))							//判断是否输入正确
		MessageBox(_T("密码不正确"), _T("提示"));
	else
		MessageBox(_T("用户名不正确"), _T("提示"));
}

//屏蔽ESC键和回车按键
BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
