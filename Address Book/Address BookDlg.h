
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
	Cusers rs_user;
	CDatabase m_db;
	DataStruct datastruct;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	LinkList_Users L;
	CLoginDlg m_loginDlg;
	CTreeCtrl m_AddrbookTree;
	CImageList m_ImageList;
	afx_msg void OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult);
	void ConnectDataSource();
	void InqTable_Users();
};
