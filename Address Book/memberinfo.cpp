// memberinfo.h : Cmemberinfo ���ʵ��



// Cmemberinfo ʵ��

// ���������� 2015��11��22��, 12:49

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
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
// Cmemberinfo ���

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


