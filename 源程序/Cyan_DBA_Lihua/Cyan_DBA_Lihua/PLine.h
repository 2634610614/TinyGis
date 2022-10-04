#ifndef _PLINE_
#define _PLINE_
#pragma once
#include "draw.h"



class CPLine :
	public CDraw
{
public:
	DECLARE_SERIAL (CPLine)
	CPLine(void);
	//���캯��
	CPLine(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			int m_Numble,PointStruct *m_PointList,int m_Lb);
	//////////////�������ߣ������////////////////
	void Draw(CDC *pDC,int Mode,int length = 0,int index =0);
	~CPLine(void);
	//////ȷ����Ӿ����������ֵ//////////
	void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);
	////////////�浵//////////////////
	void Serialize(CArchive& ar);
	/////////��ѡ////////////////
	bool IsPoint(CDC *pDC,float px,float py);
	/////////��ѡ////////////////
	bool IsRect(CDC *pDC,CRect rect);

protected:
	//����ֱ�߻��߶��������Ķ�����Ŀ
	int m_Numble;
	//��ʾ�Ƿ���� ���
	int m_Lb;
	//�洢�������������ָ��(����) 
	PointStruct *m_PointList;
};
#endif

