
// Cyan_DBA_Lihua.h : Cyan_DBA_Lihua Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "LoginInterface.h"


// CCyan_DBA_LihuaApp:
// �йش����ʵ�֣������ Cyan_DBA_Lihua.cpp
//

class CCyan_DBA_LihuaApp : public CWinAppEx
{
public:
	CCyan_DBA_LihuaApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCyan_DBA_LihuaApp theApp;
