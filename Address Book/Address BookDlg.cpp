
// Address BookDlg.cpp : ʵ���ļ�
//


#include "stdafx.h"
#include "Address Book.h"
#include "Address BookDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddressBookDlg �Ի���



CAddressBookDlg::CAddressBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddressBookDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddressBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_AddressBook, m_AddrbookTree);
}

BEGIN_MESSAGE_MAP(CAddressBookDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_AddressBook, &CAddressBookDlg::OnTvnSelchangedTreeAddressbook)
END_MESSAGE_MAP()


// CAddressBookDlg ��Ϣ�������

BOOL CAddressBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	ConnectDataSource();		//��������Դ
	InqTable_Users();				//��ѯ�û�����Ϣ��������֤�˺�����

	//������½�Ի���
	m_loginDlg.L_login = L;			//���ó�Ա���ʵķ�ʽ���û�����L�������½�Ի���
	if (m_loginDlg.DoModal() != IDOK)	//��������½�Ի���ʱִ��OnOk();		
	{														
		OnOK();										//�������ڵĶԻ���
	}

	HICON hIcon[5];						//����ͼ��������
	HTREEITEM hRoot;					//���ڵ���
	HTREEITEM hPacket;					//��ʾ��һ������
	HTREEITEM hMember;				//��ʾ��һ��Ա���

	//����ͼ�꣬�����ǵľ�����浽����
	hIcon[0] = theApp.LoadIcon(IDI_ICON_addrbook);
	hIcon[1] = theApp.LoadIcon(IDI_ICON_family);
	hIcon[2] = theApp.LoadIcon(IDI_ICON_classmate);
	hIcon[3] = theApp.LoadIcon(IDI_ICON_friend);
	hIcon[4] = theApp.LoadIcon(IDI_ICON_people);

	//����ͼ������CImageList����
	m_ImageList.Create(32, 32, ILC_COLOR32, 5, 5);
	//��ͼ����ӵ�����
	for (int i = 0; i < 5; i++)		m_ImageList.Add(hIcon[i]);

	//Ϊ���οؼ�����ͼ������
	m_AddrbookTree.SetImageList(&m_ImageList, TVSIL_NORMAL);

	//������ڵ�
	hRoot = m_AddrbookTree.InsertItem(_T("ͨѶ¼"), 0, 0);
	//������²����ӽڵ㡰���ˡ�
	hPacket = m_AddrbookTree.InsertItem(_T("����"), 1, 1, hRoot, TVI_LAST);
	//�ڡ����ˡ��ڵ��²����ӽڵ�
	hMember = m_AddrbookTree.InsertItem(_T("����"), 4, 4, hPacket, TVI_LAST);
	//������²����ӽڵ㡰ͬѧ��
	hPacket = m_AddrbookTree.InsertItem(_T("ͬѧ"), 2, 2, hRoot, TVI_LAST);
	//�ڡ�ͬѧ���ڵ��²����ӽڵ�
	hMember = m_AddrbookTree.InsertItem(_T("����"), 4, 4, hPacket, TVI_LAST);
	//������²����ӽڵ㡰���ѡ�
	hPacket = m_AddrbookTree.InsertItem(_T("����"), 3, 3, hRoot, TVI_LAST);
	//�ڡ����ѡ��ڵ��²����ӽڵ�
	hMember = m_AddrbookTree.InsertItem(_T("�ϳ�"), 4, 4, hPacket, TVI_LAST);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAddressBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAddressBookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAddressBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAddressBookDlg::OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CString strText;				//������ڵ�ı�ǩ�ı��ַ���

	//��ȡ��ǰѡ�еľ��
	HTREEITEM hItem = m_AddrbookTree.GetSelectedItem();
	//��ȡѡ�нڵ�ı�ǩ�ַ���
	strText = m_AddrbookTree.GetItemText(hItem);
	//���ַ�����ʾ���༭����
	SetDlgItemText(IDC_EDIT_SELECTED, strText);
}

//��������Դ
void CAddressBookDlg::ConnectDataSource()
{
	//��������Դ
	TRY
	{
	m_db.OpenEx(_T("DSN=DataSourceOfAddr;"), CDatabase::noOdbcDialog);	//���ӵ�һ����ΪDataSourceOfAddr������Դ
	rs_user.m_pDatabase = &m_db;
	}

	//��ʾ�����Ƿ�ɹ�
	if (!m_db.IsOpen())		AfxMessageBox(_T("��������Դʧ��"));

	//�����쳣��Ϣ
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, ex)
	{
		TCHAR szError[100];
		ex->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH;
}

//��ѯ�û�����Ϣ
void CAddressBookDlg::InqTable_Users()
{
	CString sql = _T("SELECT * FROM users");		//sql���Ҫִ�е�SQL���
	L = datastruct.CreatList_Users();
	LinkList_Users L_temp = L;
	TRY
	{
		rs_user.Open(CRecordset::snapshot, sql);			//�򿪲�ѯ��¼
		rs_user.MoveFirst();											//������һ����¼
		while (!rs_user.IsEOF())										//δ�������һ����¼����ִ��
		{
			ElemType_Users data_user;
			data_user.user_name = rs_user.m_u_name;					//��Ϊ�Ѿ�����Cusers�󶨵���users��
			data_user.user_password = rs_user.m_u_password;		//��ʵʱ����
			datastruct.InsertList_Users(L, data_user);						//�����û�����
			rs_user.MoveNext();														//������һ����¼
		}
	}
	/*
	while (L->next)
	{
		AfxMessageBox(L->next->data.user_name);
		L = L->next;
	}
	L = L_temp;
	datastruct.Destory_Users(L);          //��������
	*/
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	END_CATCH;
}
