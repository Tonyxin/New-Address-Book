// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Address Book.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedButtonclick()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString user_name;					//�˻�
	CString user_password;				//����
	GetDlgItem(IDC_EDIT_name)->GetWindowTextW(user_name);			//��������ַ������浽��Ӧ�ı�����
	GetDlgItem(IDC_EDIT_password)->GetWindowTextW(user_password);
	bool name_mark=0;					//��֤�˺��Ƿ���ȷ
	bool password_mark = 0;			//��֤�����Ƿ���ȷ
	LinkList_Users L_logintemp = L_login;
	while (L_logintemp->next)
	{
		L_logintemp = L_logintemp->next;
		if (L_logintemp->data.user_name == user_name)						//�����˻�Ϊ���ݿ��������˻�
		{
			name_mark = 1;
			if (L_logintemp->data.user_password == user_password)     //�����Ӧ�����Ƿ���ȷ
			{
				password_mark = 1;
				::SendMessage(this->GetParent()->m_hWnd, WM_RECEV_USER, 0, (LPARAM)(&(L_logintemp->data.user_id)));
				break;
			}//if
		}//if
	}//while

	if (name_mark&&password_mark)	OnOK();
	else if (name_mark && (!password_mark))							//�ж��Ƿ�������ȷ
		MessageBox(_T("���벻��ȷ"), _T("��ʾ"));
	else
		MessageBox(_T("�û�������ȷ"), _T("��ʾ"));
}

//����ESC���ͻس�����
BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
