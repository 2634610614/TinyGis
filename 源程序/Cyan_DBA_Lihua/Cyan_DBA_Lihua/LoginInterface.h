#ifndef _LOGININTERFACE_
#define _LOGININTERFACE_
#pragma once


// LoginInterface �Ի���

class LoginInterface : public CDialogEx
{
	DECLARE_DYNAMIC(LoginInterface)

public:
	LoginInterface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginInterface();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �˺�
	CString account;
	// ����
	CString password;
	afx_msg void OnBnClickedOk();
	HICON m_hIcon;
	int OnNO();

};


#endif