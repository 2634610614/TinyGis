#ifndef _DRAW_
#define _DRAW_

#pragma once
#include "afx.h"




//�߼�תʵ�ʣ�����  ����
extern void VPtoDP(int x,int y,float *X,float *Y);

//ʵ��ת�߼����������أ� ����
extern void DPtoVP(float X,float Y,int *x,int *y);

//�߼�תʵ�ʣ�����  ����
extern float VLtoDL(float l);

//ʵ��ת�߼����������أ�  ����
extern float DLtoVL(float l);

//�洢ֱ�߻��߶���ζ�������Ľṹ��
typedef struct
{
	//����X����
	float x; 
	//����Y����
	float y;
	//����Z����(�̣߳�Ԥ��)
	float z;

}PointStruct;
/////////////////////////////////


class CDraw :
	public CObject
{
public:
	//DECLARE_SERIAL (CDraw)
	CDraw(void);
	//���캯��
	CDraw(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete);
	///////////////////
	~CDraw(void);
	virtual void Draw(CDC *pDC,int Mode ,int length = 0,int index =0) = 0;
	
	///////////�浵//////////////////
	void Serialize( CArchive& ar ); //���������Object���Ѿ�������
	//////��ȡָ������ָ���ȵ�ID////////
	int GetID();
	//////ȷ����Ӿ����������ֵ//////////
	virtual void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax) = 0 ;
	/////////��ѡ////////////////
	virtual bool IsPoint(CDC *pDC,float px,float py) =0;
	//////////��ѡ////////////////
	virtual bool IsRect(CDC *pDC,CRect rect) = 0;
	///////////ɾ��ͼ��///////////////////
	void Delete(BOOL Is);
	////////////�鿴�Ƿ�ɾ��/////////////
	BOOL IsDelete();


protected:

	// ��ɫ
	COLORREF m_ColorPen;
	// ���ˢ��ɫ
	COLORREF m_ColorBrush;
	// �߿�(����)
	short m_LineWide;
	// ����(����)
	short m_LineType;
	// ͼ��Ԫ��Ψһ�ı�ʶ��
	int m_id_only;
	// �Ƿ���ɾ��״̬
	BOOL b_Delete;


};

#endif

