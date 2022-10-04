
// Cyan_DBA_LihuaDoc.h : CCyan_DBA_LihuaDoc ��Ľӿ�
//
#ifndef	 _CYAN_DBA_LIHUADOC_
#define  _CYAN_DBA_LIHUADOC_
#pragma once

#include <AfxTempl.h>
#include "Draw.h"
#include "Circle.h"
#include "PLine.h"
#include "Text.h"
#include "ImageCenterDib.h"
#define MAXSize0fArray (4096)

struct GraphSelectStruct
{
	short int Lb;		//���
	short int Index;	//���
	short buff;			 //����������
	int sumbuf;			 //����������
};//�����洢ѡ��ͼ�ε����ݽṹ




class CCyan_DBA_LihuaDoc : public CDocument
{
protected: // �������л�����
	CCyan_DBA_LihuaDoc();
	DECLARE_DYNCREATE(CCyan_DBA_LihuaDoc)

	////////////��ɸ�Ĺ�������///////////////////
	int* m_index;

	/////////����ͼ��ѡ��Ĺ�ɸ��������///////////////////
	int* select_array;

//��������ָ�������
private:
	CTypedPtrArray<CObArray,CCircle*>m_CircleArray;	//���������ָ������ Lb1
	CTypedPtrArray<CObArray,CPLine*>m_PLineArray;	//�������ߺͶ���ζ����ָ������ Lb 2
	CTypedPtrArray<CObArray,CText*>m_TextArray;		//�����ע���ֶ����ָ������ Lb 3
	

// ����
public:
	int n_GraphSelect;				//��ѡ����Ĵ�С
	GraphSelectStruct *GraphSelect;	 //��ѡ�����ָ��
	ImgCenterDib m_dib;	//����һ����ͼ����

// ����
public:

	///////////////////����ͼ��Ԫ��///////////////////////
	//����PLine
	CPLine* AddPLine(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
			int m_Numble,PointStruct *m_PointList,int m_Lb);
	//����Text
	CText* AddText(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
			float m_StartX,float m_StartY,float m_Angle,float m_TextHeight,float m_TextWide,float m_FontWeight,CString m_Text);
	//����Circle
	CCircle* AddCircle(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
			float CircleX,float CircleY,float CircleR,short Lb);

	//////////////////��ȡָ�������е�ֵ//////////////////////
	CDraw* GetGraph(short Lb,int Index);
								    
	//////////////////��ȡָ�����������±� size -1///////////////////
	int GetGraphUpperBound(short Lb);

	//////////////////��ȡָ�������Size(����)/////////////////////////
	int GetGraphNumb(short Lb);

	/////////////////ɾ��ָ�������ָ��Ԫ��/////////////////////////////
	void DeleteGraph(short Lb,int Index);

	/////////////////�����������///////////////////////////////////////
	void clearAll();

	/////////////////��ȡָ���������С����ID///////////////////////////
	int GetGraphID(short Lb);

	///////////ȫͼ��ʾ////////////
	BOOL GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);

	///////////////////��ӵ�ѡ���б�//////////////////////////
	BOOL AddSelectList(int Lb,int Index);

	///////////////////ɾ��ѡ���б�ָ��Ԫ��//////////////////////////
	void DelSelectList(int Lb,int Index); 

	////////////����ɾ��///////
	void OnPack();

	/////////////���ص�ͼ�������׵�ַ////////////
	ImgCenterDib* GetPDib();


// ��д
public:
	virtual BOOL OnNewDocument();
	/////////////�浵//////////////////
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CCyan_DBA_LihuaDoc();
	////////////////DOC�е�Draw///////////////////////////
	virtual void DocDraw(CDC* pDC,int m_DrawMode);
	

	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnLoadbasemap();
};


#endif

//////////////////////////////////////////////////////////
//�ڴ�����ȫ������
extern CString name;			//��ͼ����
extern BOOL isAdd ;				//�Ƿ��Ѿ���ӵ�ͼ����ʼ��Ϊδ��ӵ�ͼ



////////////////////////////////////////////////////////////////////////