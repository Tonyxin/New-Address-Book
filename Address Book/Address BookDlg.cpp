
// Address BookDlg.cpp : 实现文件
//


#include "stdafx.h"
#include "Address Book.h"
#include "Address BookDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAddressBookDlg 对话框



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


// CAddressBookDlg 消息处理程序

BOOL CAddressBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	ConnectDataSource();		//连接数据源
	InqTable_Users();				//查询用户表信息，用于验证账号密码

	//弹出登陆对话框
	m_loginDlg.L_login = L;			//利用成员访问的方式将用户链表L存入给登陆对话框
	if (m_loginDlg.DoModal() != IDOK)	//当×掉登陆对话框时执行OnOk();		
	{														
		OnOK();										//结束所在的对话框
	}

	HICON hIcon[5];						//设置图标句柄数组
	HTREEITEM hRoot;					//根节点句柄
	HTREEITEM hPacket;					//表示任一分组句柄
	HTREEITEM hMember;				//表示任一成员句柄

	//加载图标，将他们的句柄保存到数组
	hIcon[0] = theApp.LoadIcon(IDI_ICON_addrbook);
	hIcon[1] = theApp.LoadIcon(IDI_ICON_family);
	hIcon[2] = theApp.LoadIcon(IDI_ICON_classmate);
	hIcon[3] = theApp.LoadIcon(IDI_ICON_friend);
	hIcon[4] = theApp.LoadIcon(IDI_ICON_people);

	//创建图像序列CImageList对象
	m_ImageList.Create(32, 32, ILC_COLOR32, 5, 5);
	//将图标添加到序列
	for (int i = 0; i < 5; i++)		m_ImageList.Add(hIcon[i]);

	//为树形控件设置图像序列
	m_AddrbookTree.SetImageList(&m_ImageList, TVSIL_NORMAL);

	//插入根节点
	hRoot = m_AddrbookTree.InsertItem(_T("通讯录"), 0, 0);
	//根结点下插入子节点“家人”
	hPacket = m_AddrbookTree.InsertItem(_T("家人"), 1, 1, hRoot, TVI_LAST);
	//在“家人”节点下插入子节点
	hMember = m_AddrbookTree.InsertItem(_T("老王"), 4, 4, hPacket, TVI_LAST);
	//根结点下插入子节点“同学”
	hPacket = m_AddrbookTree.InsertItem(_T("同学"), 2, 2, hRoot, TVI_LAST);
	//在“同学”节点下插入子节点
	hMember = m_AddrbookTree.InsertItem(_T("老李"), 4, 4, hPacket, TVI_LAST);
	//根结点下插入子节点“朋友”
	hPacket = m_AddrbookTree.InsertItem(_T("朋友"), 3, 3, hRoot, TVI_LAST);
	//在“朋友”节点下插入子节点
	hMember = m_AddrbookTree.InsertItem(_T("老陈"), 4, 4, hPacket, TVI_LAST);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAddressBookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAddressBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAddressBookDlg::OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	CString strText;				//存放树节点的标签文本字符串

	//获取当前选中的句柄
	HTREEITEM hItem = m_AddrbookTree.GetSelectedItem();
	//获取选中节点的标签字符串
	strText = m_AddrbookTree.GetItemText(hItem);
	//将字符串显示到编辑框中
	SetDlgItemText(IDC_EDIT_SELECTED, strText);
}

//连接数据源
void CAddressBookDlg::ConnectDataSource()
{
	//连接数据源
	TRY
	{
	m_db.OpenEx(_T("DSN=DataSourceOfAddr;"), CDatabase::noOdbcDialog);	//连接到一个名为DataSourceOfAddr的数据源
	rs_user.m_pDatabase = &m_db;
	}

	//显示连接是否成功
	if (!m_db.IsOpen())		AfxMessageBox(_T("连接数据源失败"));

	//处理异常消息
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

//查询用户表信息
void CAddressBookDlg::InqTable_Users()
{
	CString sql = _T("SELECT * FROM users");		//sql存放要执行的SQL语句
	L = datastruct.CreatList_Users();
	LinkList_Users L_temp = L;
	TRY
	{
		rs_user.Open(CRecordset::snapshot, sql);			//打开查询记录
		rs_user.MoveFirst();											//滚到第一条记录
		while (!rs_user.IsEOF())										//未滚过最后一条记录，则执行
		{
			ElemType_Users data_user;
			data_user.user_name = rs_user.m_u_name;					//因为已经将类Cusers绑定到表users中
			data_user.user_password = rs_user.m_u_password;		//会实时更新
			datastruct.InsertList_Users(L, data_user);						//插入用户链表
			rs_user.MoveNext();														//滚向下一条记录
		}
	}
	/*
	while (L->next)
	{
		AfxMessageBox(L->next->data.user_name);
		L = L->next;
	}
	L = L_temp;
	datastruct.Destory_Users(L);          //销毁链表
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
