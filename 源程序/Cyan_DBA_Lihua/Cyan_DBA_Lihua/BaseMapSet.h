#pragma once


// BaseMapSet �Ի���

class BaseMapSet : public CDialogEx
{
	DECLARE_DYNAMIC(BaseMapSet)

public:
	BaseMapSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BaseMapSet();

// �Ի�������
	enum { IDD = IDD_BaseMapSet };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// //��С��������
	CString minLongitude;

	CString d1;
	CString f1;
	CString m1;

	// ��Сγ������
	CString minLatitude;

	CString d2;
	CString f2;
	CString m2;

	// ��󾭶�����
	CString maxLongitude;

	CString d3;
	CString f3;
	CString m3;
	// ���γ������ 
	CString maxLatitude;

	CString d4;
	CString f4;
	CString m4;
};
