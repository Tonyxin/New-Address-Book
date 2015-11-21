// users.h : Cusers ���ʵ��



// Cusers ʵ��

// ���������� 2015��11��20��, 21:26

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[u_id]"), m_u_id);
	RFX_Text(pFX, _T("[u_name]"), m_u_name);
	RFX_Text(pFX, _T("[u_password]"), m_u_password);

}
/////////////////////////////////////////////////////////////////////////////
// Cusers ���

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


