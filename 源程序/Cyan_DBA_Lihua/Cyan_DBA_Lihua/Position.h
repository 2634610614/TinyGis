#pragma once
#include "afxwin.h"


// Position �Ի���

class Position : public CDialogEx
{
	DECLARE_DYNAMIC(Position)

public:
	Position(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Position();

// �Ի�������
	enum { IDD = IDD_SelectAddress };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����
	CString longitude;

	// γ��
	CString latitude;
};
