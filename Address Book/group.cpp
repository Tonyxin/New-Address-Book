// group.h : Cgroup ���ʵ��



// Cgroup ʵ��

// ���������� 2015��11��27��, 19:39

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Int(pFX, _T("[p_id]"), m_p_id);
	RFX_Text(pFX, _T("[p_mode]"), m_p_mode);

}
/////////////////////////////////////////////////////////////////////////////
// Cgroup ���

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


