#ifndef _MAPMESSAGE_
#define _MAPMESSAGE_
#pragma once


// MapMessage �Ի���

class MapMessage : public CDialogEx
{
	DECLARE_DYNAMIC(MapMessage)

public:
	MapMessage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MapMessage();

// �Ի�������
	enum { IDD = IDD_DIALOGMessage };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	// �����ؼ���ֵ
	CString message;
};
#endif
