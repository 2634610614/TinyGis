#ifndef _ROUTESELECT_
#define _ROUTESELECT_
#pragma once
#include "afxwin.h"

// RouteSelect �Ի���

class RouteSelect : public CDialogEx
{
	DECLARE_DYNAMIC(RouteSelect)

public:
	RouteSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RouteSelect();
	
// �Ի�������
	enum { IDD = IDD_DIALOGSelect };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ���ҵ�index���ַ�������
	CString m_index;
};
#endif
