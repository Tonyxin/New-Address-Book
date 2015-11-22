
// Address BookDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "LoginDlg.h"




// CAddressBookDlg �Ի���
class CAddressBookDlg : public CDialog
{
// ����
public:
	
	CAddressBookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ADDRESSBOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	Cusers rs_user;							//���û���󶨵Ķ���
	Cview_group rs_group;				//�ͷ�����ͼ�󶨵Ķ���
	Cview_member rs_member;		//�ͳ�Ա��ͼ�󶨵Ķ���
	CDatabase m_db;						
	DataStruct datastruct;				
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecevUser(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP();
public:
	LinkList_Users L;							//�û�����
	LinkList_Group L_Group;				//��������
	int id_user;									//��ǰ�û�id
	CLoginDlg m_loginDlg;
	CTreeCtrl m_AddrbookTree;
	CImageList m_ImageList;
	afx_msg void OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult);
	void ConnectDataSource();
	void InqTable_Users();
	void InqView_Group();
	void InqView_Member();
	afx_msg void OnEnChangeEditSelected();
};
