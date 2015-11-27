// group.h : Cgroup 类的实现



// Cgroup 实现

// 代码生成在 2015年11月27日, 19:39

#include "stdafx.h"
#include "group.h"
IMPLEMENT_DYNAMIC(Cgroup, CRecordset)

Cgroup::Cgroup(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_p_id = 0;
	m_p_mode = "";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cgroup::GetDefaultConnect()
{
	return _T("DSN=DataSourceOfAddr;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=DESKTOP-TLIOR44;DATABASE=AddressBook");
}

CString Cgroup::GetDefaultSQL()
{
	return _T("[dbo].[packetmode]");
}

void Cgroup::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Int(pFX, _T("[p_id]"), m_p_id);
	RFX_Text(pFX, _T("[p_mode]"), m_p_mode);

}
/////////////////////////////////////////////////////////////////////////////
// Cgroup 诊断

#ifdef _DEBUG
void Cgroup::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cgroup::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


