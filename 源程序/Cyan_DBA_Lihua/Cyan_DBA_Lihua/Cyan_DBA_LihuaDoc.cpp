
// Cyan_DBA_LihuaDoc.cpp : CCyan_DBA_LihuaDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Cyan_DBA_Lihua.h"
#endif

#include "Cyan_DBA_LihuaDoc.h"
#include "Cyan_DBA_LihuaView.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////�ڴ˶���ȫ�����ݣ�extern��/////////////////////////
CString name;			//��ͼ����
BOOL isAdd = false ;	//�Ƿ��Ѿ���ӵ�ͼ����ʼ��Ϊδ��ӵ�ͼ

////////////////////////////////////////////////////////////




// CCyan_DBA_LihuaDoc

IMPLEMENT_DYNCREATE(CCyan_DBA_LihuaDoc, CDocument)

BEGIN_MESSAGE_MAP(CCyan_DBA_LihuaDoc, CDocument)
	ON_COMMAND(ID_LoadBasemap, &CCyan_DBA_LihuaDoc::OnLoadbasemap)
END_MESSAGE_MAP()


// CCyan_DBA_LihuaDoc ����/����

CCyan_DBA_LihuaDoc::CCyan_DBA_LihuaDoc()
{
	// TODO: �ڴ����һ���Թ������
	this->m_index = new int[MAXSize0fArray];	//��ɸ�Ĺ�������
	this->GraphSelect = new GraphSelectStruct[MAXSize0fArray*3];	//����1.2M*sizeof(GraphSelectStruct)��С�Ŀռ�
	this->select_array = new int[MAXSize0fArray*3];	//����1.2M*sizeof(int)��С�Ŀռ�
	this->n_GraphSelect = 0;
}

CCyan_DBA_LihuaDoc::~CCyan_DBA_LihuaDoc()
{
	delete [] this->m_index;		//ɾ��new ���������� delete []
	delete [] this->GraphSelect;
	delete [] this->select_array;
}

BOOL CCyan_DBA_LihuaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCyan_DBA_LihuaDoc ���л�

void CCyan_DBA_LihuaDoc::Serialize(CArchive& ar)
{
	m_CircleArray.Serialize(ar);
	m_PLineArray.Serialize(ar);
	m_TextArray.Serialize(ar);
	
	 if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		ar << m_originX << m_originY << m_originXTo << m_originYTo  << scale << scaleNow;
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		ar >> m_originX >> m_originY >> m_originXTo >> m_originYTo  >> scale >> scaleNow;
	}
	this->SetModifiedFlag(0);
}


///////////////////����ͼ��Ԫ��///////////////////////

//����PLine
CPLine* CCyan_DBA_LihuaDoc::AddPLine(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
		int m_Numble,PointStruct *m_PointList,int m_Lb)
{
	CPLine* p_PLine = new CPLine(m_ColorPen,m_ColorBrush,m_LineWide,m_LineType,m_id_only,0,
									m_Numble,m_PointList,m_Lb);
	m_PLineArray.Add(p_PLine);
	return p_PLine;
}

//����Text
CText* CCyan_DBA_LihuaDoc::AddText(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
		float m_StartX,float m_StartY,float m_Angle,float m_TextHeight,float m_TextWide,float m_FontWeight,CString m_Text)
{
	CText* p_Text = new CText(m_ColorPen,m_ColorBrush,m_LineWide,m_LineType,m_id_only,0,
								m_StartX,m_StartY,m_Angle,m_TextHeight,m_TextWide,m_FontWeight,m_Text);
	m_TextArray.Add(p_Text);
	return p_Text;
}

//����Circle
CCircle* CCyan_DBA_LihuaDoc::AddCircle(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
		float CircleX,float CircleY,float CircleR,short Lb)
{
	CCircle* p_Circle = new CCircle(m_ColorPen,m_ColorBrush,m_LineWide,m_LineType,m_id_only,0,
										CircleX,CircleY,CircleR,Lb);
	m_CircleArray.Add(p_Circle);
	return p_Circle;
}


//////////////////��ȡָ�������е�ֵ//////////////////////

CDraw* CCyan_DBA_LihuaDoc::GetGraph(short Lb,int Index)
{
	switch(Lb)
	{
	case 1:		//Circle
		if(Index<0||Index>m_CircleArray.GetUpperBound())
		{
			return NULL;
		}
		
		return m_CircleArray.GetAt(Index);
		break;
	case 2:		//PLine
		if(Index<0||Index>m_PLineArray.GetUpperBound())
		{
			return NULL;
		}
		return m_PLineArray.GetAt(Index);
		break;
	case 3:		//Text
		if(Index<0||Index>m_TextArray.GetUpperBound())
		{
			return NULL;
		}
		return m_TextArray.GetAt(Index);
		break;
	default:
		return NULL;
	}
}

//////////////////��ȡָ�����������±� Size -1//////////////////////
int CCyan_DBA_LihuaDoc::GetGraphUpperBound(short Lb)
{
	switch(Lb)
	{
	case 1:		//Circle
		return m_CircleArray.GetUpperBound();
		break;
	case 2:		//PLine
		return m_PLineArray.GetUpperBound();
		break;
	case 3:		//Text
		return m_TextArray.GetUpperBound();
		break;
	default:
		return -1;
	}
}


//////////////////��ȡָ�������Size(����)//////////////////////
int CCyan_DBA_LihuaDoc::GetGraphNumb(short Lb)
{
	switch(Lb)
	{
	case 1:		//Circle
		return m_CircleArray.GetSize();
		break;
	case 2:		//PLine
		return m_PLineArray.GetSize();
		break;
	case 3:		//Text
		return m_TextArray.GetSize();
		break;
	default:
		return 0;
	}
}

/////////////////ɾ��ָ�������ָ��Ԫ��///////////////////////
void CCyan_DBA_LihuaDoc::DeleteGraph(short Lb,int Index)
{
	switch(Lb)
	{
	case 1:		//Circle
		if(Index<0||Index>m_CircleArray.GetUpperBound())
		{
			return ;
		}
		m_CircleArray.RemoveAt(Index);
		break;
	case 2:		//PLine
		if(Index<0||Index>m_PLineArray.GetUpperBound())
		{
			return ;
		}
		m_PLineArray.RemoveAt(Index);
		break;
	case 3:		//Text
		if(Index<0||Index>m_TextArray.GetUpperBound())
		{
			return ;
		}
		m_TextArray.RemoveAt(Index);
		break;
	default:
		return ;
	}
}

/////////////////�����������//////////////////////////////
void CCyan_DBA_LihuaDoc::clearAll()
{
	m_CircleArray.RemoveAll();
	m_PLineArray.RemoveAll();
	m_TextArray.RemoveAll();
}

/////////////////��ȡָ���������С����ID///////////////////////////
int CCyan_DBA_LihuaDoc::GetGraphID(short Lb)
{
	for(int i=0;i<MAXSize0fArray;++i)
	{
		m_index[i]=0;
	}
	for(int i =0;i<=GetGraphUpperBound(Lb);++i)
	{
		if(GetGraph(Lb,i))
		{
			//m_index[i]=1;
			m_index[GetGraph(Lb,i)->GetID()] =1;
		}
	}
	for(int i =0;i<MAXSize0fArray;++i)
	{
		if(m_index[i]==0)
		{
			return i;
		}
	}
	return -1;
	
}

///////////ȫͼ��ʾ////////////
BOOL CCyan_DBA_LihuaDoc::GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax)
{
	float m_minX,m_minY,m_maxX,m_maxY;
	BOOL docIsEmpty = 0;
	for(int i=1;i<=3;i++)
	{
		int Size=GetGraphUpperBound(i);
		for(int j=0;j<=Size;j++)
		{
			docIsEmpty = 1;
			if(GetGraph(i,j))
			{
				GetGraph(i,j)->GetRect(&m_minX,&m_minY,&m_maxX,&m_maxY);
			}
			else
			{
				continue;
			}
			if(m_minX < *m_Xmin)
			{
				*m_Xmin = m_minX;
			}
			if(*m_Xmax < m_maxX)
			{
				*m_Xmax = m_maxX;
			}
			if(m_minY < *m_Ymin)
			{
				*m_Ymin = m_minY;
			}
			if(*m_Ymax < m_maxY)
			{
				*m_Ymax = m_maxY;
			}
		}	
	}
	return docIsEmpty;
}


///////////////////��ӵ���ѯ�б�//////////////////////////
BOOL CCyan_DBA_LihuaDoc::AddSelectList(int Lb,int Index)
{
	for(int i = 0; i<this->n_GraphSelect;++i)
	{
		if(Lb == this->GraphSelect[i].Lb && Index == this->GraphSelect[i].Index)
		{
			return FALSE;
		}
	}
	this->GraphSelect[n_GraphSelect].Lb = Lb;	//n_GraphSelect��Զָ����һ��
	this->GraphSelect[n_GraphSelect++].Index = Index;
	return TRUE;
}

//////////ɾ��ָ����ѯ����////////////////////
void CCyan_DBA_LihuaDoc::DelSelectList(int Lb,int Index)  
{
	//int selectArray[1024];
	//for(int i =0;i<1024;++i)
	//{
	//	selectArray[i] = 0;
	//}
	//int number = 0;
	
	//for(int i = 0;i<number;++i)
	//{
	//	for(int j = selectArray[i]- i;j< n_GraphSelect;++j)
	//	{
	//		GraphSelect[j] =  GraphSelect[j+1];
	//		++j;
	//	}
	//}
	
	//n_GraphSelect -= number;

	int x  = 0;
	int sign = 0;
	for(int i = 0 ;i<this->n_GraphSelect;++i)
	{
		if(Lb == this->GraphSelect[i].Lb && Index == this->GraphSelect[i].Index)
		{
			x = i;
			sign = 1;
		}
	}
	if(sign == 0)
	{
		return;
	}

	
	//for(int i = x;i< n_GraphSelect-1;++i)
	//{
	//	GraphSelect[i] =  GraphSelect[i+1];
	//	--n_GraphSelect;
	//}
	if(x == n_GraphSelect -1)
	{
		--n_GraphSelect;
	}
	else
	{
		GraphSelect[x] =  GraphSelect[n_GraphSelect -1];
		-- n_GraphSelect;
	}	
}

////////////////DOC�е�Draw///////////////////////////
void CCyan_DBA_LihuaDoc::DocDraw(CDC *pDC,int m_DrawMode)
{
	for(int i=1;i<=3;++i)
	{
		int Size=GetGraphUpperBound(i);
		for(int j=0;j<=Size;++j)
		{
			GetGraph(i,j)->Draw(pDC,m_DrawMode);
		}
	}
	//ͨ��n_GraphSelect�����ƻ�ͼ
	for(int i = 0;i<this->n_GraphSelect;++i)
	{
		GetGraph(GraphSelect[i].Lb,GraphSelect[i].Index)->Draw(pDC,1);
		if(GraphSelect[i].buff!=0&&GraphSelect[i].sumbuf == 0)
		{
			int x = DLtoVL(GraphSelect[i].buff);
			int y = DLtoVL(GraphSelect[i].sumbuf);
			GetGraph(GraphSelect[i].Lb,GraphSelect[i].Index)->Draw(pDC,2,x,y);
		}
		if(GraphSelect[i].buff!=0&&GraphSelect[i].sumbuf> 0)
		{
			int x = DLtoVL(GraphSelect[i].buff);
			int y = DLtoVL(GraphSelect[i].sumbuf);
			GetGraph(GraphSelect[i].Lb,GraphSelect[i].Index)->Draw(pDC,3,x,y);
		}

	}
}



////////////����ɾ��///////
void CCyan_DBA_LihuaDoc::OnPack()
{
	for(int i=1;i<=3;++i)
	{
		int Size=this->GetGraphUpperBound(i);
		for(int j=0;j<=Size;++j)
		{
			//�ж��Ƿ����
			if(this->GetGraph(i,j))
			{
				//�ж��Ƿ񱻼������վ
				if(this->GetGraph(i,j)->IsDelete())
				{
					//ɾ��
					this->DeleteGraph(i,j);
				}
			}
		}
	}
	this->n_GraphSelect = 0;	//�����n_GraphSelect��Ϊ0
	this->SetModifiedFlag(1);
	this->UpdateAllViews(NULL);
}


/////////////���ص�ͼ�������׵�ַ////////////
ImgCenterDib* CCyan_DBA_LihuaDoc::GetPDib() 
{
	return &(this->m_dib);
}

////////////��ӵ�ͼ/////////////
void CCyan_DBA_LihuaDoc::OnLoadbasemap()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK)
	{
		name=dlg.GetPathName();
		if(m_dib.Read(dlg.GetPathName())==TRUE)
		{
			SetModifiedFlag(FALSE);		//֪ͨ���ݷ������
			this->UpdateAllViews(NULL);		//��ͼ�����仯��ǿ�д����ػ�	
			isAdd =true;
			CCyan_DBA_LihuaView *pview;
			POSITION pos = GetFirstViewPosition();
			pview = (CCyan_DBA_LihuaView*)GetNextView (pos);
			pview->OnRedraw();
		}
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCyan_DBA_LihuaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CCyan_DBA_LihuaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CCyan_DBA_LihuaDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCyan_DBA_LihuaDoc ���

#ifdef _DEBUG
void CCyan_DBA_LihuaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCyan_DBA_LihuaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCyan_DBA_LihuaDoc ����


