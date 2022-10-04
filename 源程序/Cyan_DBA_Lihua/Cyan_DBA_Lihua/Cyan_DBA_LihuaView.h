
// Cyan_DBA_LihuaView.h : CCyan_DBA_LihuaView ��Ľӿ�
//
#ifndef	 _CYAN_DBA_LIHUAView_
#define  _CYAN_DBA_LIHUAView_
#pragma once


#include <stdlib.h>
#include <iostream>
#include <limits>
#include "resource.h"
#include"TextDlg.h"
#include "ColorTool.h"
#include "MapMessage.h"
#include "RouteSelect.h"
#include "MainFrm.h"
#include "ImageCenterDib.h"
#include "WINDOWSX.H "
#include "BaseMapSet.h"
#include "Position.h"
#include "MapBuffer.h"
#include "math.h"
#include <windows.h>
const int EARTH_RADIUS = 6371000;	//��
#define ArraySize (1024)


class CCyan_DBA_LihuaView : public CFormView
{
protected: // �������л�����
	CCyan_DBA_LihuaView();
	DECLARE_DYNCREATE(CCyan_DBA_LihuaView)

public:
	enum{ IDD = IDD_CYAN_DBA_LIHUA_FORM };

// ����
public:
	CCyan_DBA_LihuaDoc* GetDocument() const;

// ����
public:
	int GetScreenH();	//��ȡ��Ļ�߶�
	int GetScreenW();	//��ȡ��Ļ���
	int imgWidth;	//��ͼ���
	int imgHeight;	//��ͼ�߶�
	int xmove,ymove	;	//��ͼ��ʼ��X ,Y ����
	float xmoveTo ,ymoveTo;	//������ͼ������ת��
	double sumLength;	//�����ĳ���

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

	COLORREF m_pColor;	//������ɫ
	COLORREF m_brushColor;  //��ˢ��ɫ
	short m_LineWide;	//�����߿�
	short m_LineType;	//��������
	CPen m_pen;		//���廭��	���캯����ʼ��
	CBrush m_brush;	//���廭ˢ	���캯����ʼ��
	CPoint mPointOrign;	//��ȡ����λ��
	CPoint mPointOld; //��ȡ����λ��
	//short m_layer; //��������ͼ��
	PointStruct* PointXyz; //��������ָ��
	CImage m_image;//ָ����
	int m_hScreen;	//(Form)��Ļ�߶�
	int m_wScreen;	//(Form)��Ļ���
	PointStruct pstOrign;
	PointStruct psOld;	

	CMap<int ,int , CPoint, CPoint> m_PointMap;	//�洢·���ĵ�
	CMap<int ,int ,CString, CString&> m_StringMap; //�洢·������Ϣ
	BOOL light ;	//�˵���ť�ĻҺ�,��ʼ��ť	 ��ʼ��ΪTRUE�����������ģ��������ť�ǻ�ɫ��
	int m_index;	//·����key
	int* hash_array;
	bool mapSet;	//��ͼ�Ƿ�����
	double rad(double d);	//��ȡ����
	double GetDistance(double lng1,double lat1,double lng2,double lat2);		//��ȡ����




// ʵ��
public:
	virtual ~CCyan_DBA_LihuaView();
	virtual void OnDraw(CDC* pDC);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//��ǰ���ڲ��������
	int  m_DrawCurrent;
	//��¼�������Ĵ���
	int PushNum;
	//�жϻ���վ�Ƿ�Ϊ��
	bool isEmptytrash;


// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
	afx_msg void OnDrawPoint();
	afx_msg void OnUpdateDrawPoint(CCmdUI *pCmdUI);
	afx_msg void OnDrawTriangle();
	afx_msg void OnUpdateDrawTriangle(CCmdUI *pCmdUI);
	afx_msg void OnDrawPolyline();
	afx_msg void OnUpdateDrawPolyline(CCmdUI *pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI *pCmdUI);
	afx_msg void OnDrawText();
	afx_msg void OnUpdateDrawText(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAttributes();
	afx_msg void OnUpdateAttributes(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawNorth();
	afx_msg void OnUpdateDrawNorth(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnlarge();
	afx_msg void OnUpdateEnlarge(CCmdUI *pCmdUI);
	afx_msg void On2xzoomout();
	afx_msg void OnUpdate3xzoomout(CCmdUI *pCmdUI);
	afx_msg void On3xzoomout();
	afx_msg void OnUpdate2xzoomout(CCmdUI *pCmdUI);
	afx_msg void OnPan();
	afx_msg void OnUpdatePan(CCmdUI *pCmdUI);
	afx_msg void OnFullmap();
	afx_msg void OnUpdateFullmap(CCmdUI *pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void On2xenlargement();
	afx_msg void OnUpdate2xenlargement(CCmdUI *pCmdUI);
	afx_msg void On3xenlargement();
	afx_msg void OnUpdate3xenlargement(CCmdUI *pCmdUI);
	afx_msg void OnZoomout();
	afx_msg void OnUpdateZoomout(CCmdUI *pCmdUI);
	afx_msg void OnBegindraw();
	afx_msg void OnUpdateBegindraw(CCmdUI *pCmdUI);
	afx_msg void OnEnddraw();
	afx_msg void OnUpdateEnddraw(CCmdUI *pCmdUI);
	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI *pCmdUI);
	afx_msg void OnClicktoselect();
	afx_msg void OnUpdateClicktoselect(CCmdUI *pCmdUI);
	afx_msg void OnFrameselection();
	afx_msg void OnUpdateFrameselection(CCmdUI *pCmdUI);
	afx_msg void OnSubtractselected();
	afx_msg void OnUpdateSubtractselected(CCmdUI *pCmdUI);
	afx_msg void OnGraphicdeletion();
	afx_msg void OnUpdateGraphicdeletion(CCmdUI *pCmdUI);
	afx_msg void OnUndodelete();
	afx_msg void OnUpdateUndodelete(CCmdUI *pCmdUI);
	afx_msg void OnUncheck();
	afx_msg void OnUpdateUncheck(CCmdUI *pCmdUI);
	afx_msg void OnEmptytrash();
	afx_msg void OnUpdateEmptytrash(CCmdUI *pCmdUI);
	afx_msg void OnSaveplot();
	afx_msg void OnRemovebasemap();
	afx_msg void OnInputboundary();
	afx_msg void OnPointonmap();
	afx_msg void OnUpdatePointonmap(CCmdUI *pCmdUI);
	afx_msg void OnPosition();
	afx_msg void OnBuffer();
	afx_msg void OnRedraw();
	afx_msg void OnMeasure();
	afx_msg void OnUpdateMeasure(CCmdUI *pCmdUI);
	afx_msg void OnSelectall();
	afx_msg void OnUpdateSelectall(CCmdUI *pCmdUI);
	afx_msg void OnClearall();
	afx_msg void Onbufferset();
	afx_msg void OnAllbuffer();
	afx_msg void OnPullframe();
	afx_msg void OnUpdatePullframe(CCmdUI *pCmdUI);
	afx_msg void Ontwinkle();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFillpullframe();
	afx_msg void OnUpdateFillpullframe(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // Cyan_DBA_LihuaView.cpp �еĵ��԰汾
inline CCyan_DBA_LihuaDoc* CCyan_DBA_LihuaView::GetDocument() const
   { return reinterpret_cast<CCyan_DBA_LihuaDoc*>(m_pDocument); }
#endif





/////////////�ڴ�����ȫ�����ݣ�extern��/////////////////////////
extern float m_originX; //ԭ��.x
extern float m_originY; //ԭ��.y
extern float m_originXTo;	//��ʱ����ԭ�� �� x
extern float m_originYTo;	//��ʱ����ԭ�� �� y 
extern float scale;	 //��ǰ�����ߣ���ʼ��Ϊ1��
extern float scaleNow;	//�����ߣ���ʼ��Ϊ1�� ��ͼʱ�ı�����		   
extern CCyan_DBA_LihuaView* pView;	//view��ָ��(���캯���г�ʼ��Ϊthis)


//�߼�תʵ�ʣ�����  ����
extern void VPtoDP(int x,int y,float *X,float *Y);

//ʵ��ת�߼����������أ� ����
extern void DPtoVP(float X,float Y,int *x,int *y);

//�߼�תʵ�ʣ�����  ����
extern float VLtoDL(float l);

//ʵ��ת�߼����������أ�  ����
extern float DLtoVL(float l);

//��ȡ��ǰ����·��
extern CString GetCurrentPath();

///////////////////////////////////////////////
#endif