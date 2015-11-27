// memberinfo.h : Cmemberinfo ������

#pragma once

// ���������� 2015��11��22��, 12:49

class Cmemberinfo : public CRecordset
{
public:
	Cmemberinfo(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cmemberinfo)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	int	m_m_id;
	CStringA	m_m_name;
	CStringA	m_m_sex;
	CStringA	m_m_birthday;
	CStringA	m_m_email;
	CStringA	m_m_phone;
	CStringA	m_m_teleph;
	CStringA	m_m_qq;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


