// memberinfo.h : Cmemberinfo 类的实现



// Cmemberinfo 实现

// 代码生成在 2015年11月22日, 12:49

#include "stdafx.h"
#include "memberinfo.h"
IMPLEMENT_DYNAMIC(Cmemberinfo, CRecordset)

Cmemberinfo::Cmemberinfo(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_m_id = 0;
	m_m_name = "";
	m_m_sex = "";
	m_m_birthday;
	m_m_email = "";
	m_m_phone = "";
	m_m_teleph = "";
	m_m_qq = "";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cmemberinfo::GetDefaultConnect()
{
	return _T("DSN=DataSourceOfAddr;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=DESKTOP-TLIOR44;DATABASE=AddressBook");
}

CString Cmemberinfo::GetDefaultSQL()
{
	return _T("[dbo].[membership]");
}

void Cmemberinfo::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Int(pFX, _T("[m_id]"), m_m_id);
	RFX_Text(pFX, _T("[m_name]"), m_m_name);
	RFX_Text(pFX, _T("[m_sex]"), m_m_sex);
	RFX_Text(pFX, _T("[m_birthday]"), m_m_birthday);
	RFX_Text(pFX, _T("[m_email]"), m_m_email);
	RFX_Text(pFX, _T("[m_phone]"), m_m_phone);
	RFX_Text(pFX, _T("[m_teleph]"), m_m_teleph);
	RFX_Text(pFX, _T("[m_qq]"), m_m_qq);

}
/////////////////////////////////////////////////////////////////////////////
// Cmemberinfo 诊断

#ifdef _DEBUG
void Cmemberinfo::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cmemberinfo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


