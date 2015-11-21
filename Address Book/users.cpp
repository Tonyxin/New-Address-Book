// users.h : Cusers 类的实现



// Cusers 实现

// 代码生成在 2015年11月20日, 21:26

#include "stdafx.h"
#include "users.h"
IMPLEMENT_DYNAMIC(Cusers, CRecordset)

Cusers::Cusers(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_u_id = 0;
	m_u_name = "";
	m_u_password = "";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cusers::GetDefaultConnect()
{
	return _T("DSN=DataSourceOfAddr;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=DESKTOP-TLIOR44;DATABASE=AddressBook");
}

CString Cusers::GetDefaultSQL()
{
	return _T("[dbo].[users]");
}

void Cusers::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[u_id]"), m_u_id);
	RFX_Text(pFX, _T("[u_name]"), m_u_name);
	RFX_Text(pFX, _T("[u_password]"), m_u_password);

}
/////////////////////////////////////////////////////////////////////////////
// Cusers 诊断

#ifdef _DEBUG
void Cusers::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cusers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


