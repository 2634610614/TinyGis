
// Cyan_DBA_LihuaView.cpp : CCyan_DBA_LihuaView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Cyan_DBA_Lihua.h"
#endif

#include "Cyan_DBA_LihuaDoc.h"
#include "Cyan_DBA_LihuaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////�ڴ˶���ȫ�����ݣ�extern��/////////////////////////
float m_originX; //ԭ��.x
float m_originY; //ԭ��.y
float m_originXTo;	//��ʱ����ԭ�� �� x
float m_originYTo;	//��ʱ����ԭ�� �� y 
float scale = 1.0;	 //�����ߣ���ʼ��Ϊ1��
float scaleNow = 1.0;
CCyan_DBA_LihuaView* pView;	//view��ָ��(���캯���г�ʼ��Ϊthis)


//�߼�תʵ�ʣ�����  ����
void VPtoDP(int x,int y,float *X,float *Y)
{
	*X=m_originX + x*scale;
	*Y=m_originY + scale*( pView->GetScreenH() -y);
}

//ʵ��ת�߼����������أ� ����
void DPtoVP(float X,float Y,int *x,int *y)
{
   *x =(X-m_originX)/scale;
   *y = pView->GetScreenH() -(Y -m_originY)/scale ;
}

//�߼�תʵ�ʣ�����  ����				  
float VLtoDL(float l)
{
	return scale * l;
}

//ʵ��ת�߼����������أ�  ����
float DLtoVL(float l)
{
	return l/scale;
}

//��ȡ��ǰ����·��
CString GetCurrentPath()
{
	CString strPath;
	TCHAR path[_MAX_PATH];
	TCHAR drv[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];

	GetModuleFileName(NULL, path, _MAX_PATH);
	_tsplitpath(path, drv, dir, NULL, NULL);
	_tmakepath(path, drv, dir, NULL,NULL);

	strPath=path;
	return strPath;
}

///////////////////////////////////////////////



// CCyan_DBA_LihuaView

IMPLEMENT_DYNCREATE(CCyan_DBA_LihuaView, CFormView)

BEGIN_MESSAGE_MAP(CCyan_DBA_LihuaView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_Circle, &CCyan_DBA_LihuaView::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Circle, &CCyan_DBA_LihuaView::OnUpdateDrawCircle)
	ON_COMMAND(ID_DRAW_Point, &CCyan_DBA_LihuaView::OnDrawPoint)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Point, &CCyan_DBA_LihuaView::OnUpdateDrawPoint)
	ON_COMMAND(ID_DRAW_Triangle, &CCyan_DBA_LihuaView::OnDrawTriangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Triangle, &CCyan_DBA_LihuaView::OnUpdateDrawTriangle)
	ON_COMMAND(ID_DRAW_Polyline, &CCyan_DBA_LihuaView::OnDrawPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Polyline, &CCyan_DBA_LihuaView::OnUpdateDrawPolyline)
	ON_COMMAND(ID_DRAW_Polygon, &CCyan_DBA_LihuaView::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Polygon, &CCyan_DBA_LihuaView::OnUpdateDrawPolygon)
	ON_COMMAND(ID_DRAW_Text, &CCyan_DBA_LihuaView::OnDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Text, &CCyan_DBA_LihuaView::OnUpdateDrawText)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_Attributes, &CCyan_DBA_LihuaView::OnAttributes)
	ON_UPDATE_COMMAND_UI(ID_Attributes, &CCyan_DBA_LihuaView::OnUpdateAttributes)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DRAW_NORTH, &CCyan_DBA_LihuaView::OnDrawNorth)
	ON_UPDATE_COMMAND_UI(ID_DRAW_NORTH, &CCyan_DBA_LihuaView::OnUpdateDrawNorth)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_Enlarge, &CCyan_DBA_LihuaView::OnEnlarge)
	ON_UPDATE_COMMAND_UI(ID_Enlarge, &CCyan_DBA_LihuaView::OnUpdateEnlarge)
	ON_COMMAND(ID_2xZoomOut, &CCyan_DBA_LihuaView::On2xzoomout)
	ON_UPDATE_COMMAND_UI(ID_3xZoomOut, &CCyan_DBA_LihuaView::OnUpdate3xzoomout)
	ON_COMMAND(ID_3xZoomOut, &CCyan_DBA_LihuaView::On3xzoomout)
	ON_UPDATE_COMMAND_UI(ID_2xZoomOut, &CCyan_DBA_LihuaView::OnUpdate2xzoomout)
	ON_COMMAND(ID_Pan, &CCyan_DBA_LihuaView::OnPan)
	ON_UPDATE_COMMAND_UI(ID_Pan, &CCyan_DBA_LihuaView::OnUpdatePan)
	ON_COMMAND(ID_FullMap, &CCyan_DBA_LihuaView::OnFullmap)
	ON_UPDATE_COMMAND_UI(ID_FullMap, &CCyan_DBA_LihuaView::OnUpdateFullmap)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_2xEnlargement, &CCyan_DBA_LihuaView::On2xenlargement)
	ON_UPDATE_COMMAND_UI(ID_2xEnlargement, &CCyan_DBA_LihuaView::OnUpdate2xenlargement)
	ON_COMMAND(ID_3xEnlargement, &CCyan_DBA_LihuaView::On3xenlargement)
	ON_UPDATE_COMMAND_UI(ID_3xEnlargement, &CCyan_DBA_LihuaView::OnUpdate3xenlargement)
	ON_COMMAND(ID_ZoomOut, &CCyan_DBA_LihuaView::OnZoomout)
	ON_UPDATE_COMMAND_UI(ID_ZoomOut, &CCyan_DBA_LihuaView::OnUpdateZoomout)
	ON_COMMAND(ID_BeginDraw, &CCyan_DBA_LihuaView::OnBegindraw)
	ON_UPDATE_COMMAND_UI(ID_BeginDraw, &CCyan_DBA_LihuaView::OnUpdateBegindraw)
	ON_COMMAND(ID_EndDraw, &CCyan_DBA_LihuaView::OnEnddraw)
	ON_UPDATE_COMMAND_UI(ID_EndDraw, &CCyan_DBA_LihuaView::OnUpdateEnddraw)
	ON_COMMAND(ID_Select, &CCyan_DBA_LihuaView::OnSelect)
	ON_UPDATE_COMMAND_UI(ID_Select, &CCyan_DBA_LihuaView::OnUpdateSelect)
	ON_COMMAND(ID_ClickToSelect, &CCyan_DBA_LihuaView::OnClicktoselect)
	ON_UPDATE_COMMAND_UI(ID_ClickToSelect, &CCyan_DBA_LihuaView::OnUpdateClicktoselect)
	ON_COMMAND(ID_FrameSelection, &CCyan_DBA_LihuaView::OnFrameselection)
	ON_UPDATE_COMMAND_UI(ID_FrameSelection, &CCyan_DBA_LihuaView::OnUpdateFrameselection)
	ON_COMMAND(ID_SubtractSelected, &CCyan_DBA_LihuaView::OnSubtractselected)
	ON_UPDATE_COMMAND_UI(ID_SubtractSelected, &CCyan_DBA_LihuaView::OnUpdateSubtractselected)
	ON_COMMAND(ID_GraphicDeletion, &CCyan_DBA_LihuaView::OnGraphicdeletion)
	ON_UPDATE_COMMAND_UI(ID_GraphicDeletion, &CCyan_DBA_LihuaView::OnUpdateGraphicdeletion)
	ON_COMMAND(ID_UndoDelete, &CCyan_DBA_LihuaView::OnUndodelete)
	ON_UPDATE_COMMAND_UI(ID_UndoDelete, &CCyan_DBA_LihuaView::OnUpdateUndodelete)
	ON_COMMAND(ID_Uncheck, &CCyan_DBA_LihuaView::OnUncheck)
	ON_UPDATE_COMMAND_UI(ID_Uncheck, &CCyan_DBA_LihuaView::OnUpdateUncheck)
	ON_COMMAND(ID_EmptyTrash, &CCyan_DBA_LihuaView::OnEmptytrash)
	ON_UPDATE_COMMAND_UI(ID_EmptyTrash, &CCyan_DBA_LihuaView::OnUpdateEmptytrash)
	ON_COMMAND(ID_SavePlot, &CCyan_DBA_LihuaView::OnSaveplot)
	ON_COMMAND(ID_RemoveBasemap, &CCyan_DBA_LihuaView::OnRemovebasemap)
	ON_COMMAND(ID_InputBoundary, &CCyan_DBA_LihuaView::OnInputboundary)
	ON_COMMAND(ID_PointOnMap, &CCyan_DBA_LihuaView::OnPointonmap)
	ON_UPDATE_COMMAND_UI(ID_PointOnMap, &CCyan_DBA_LihuaView::OnUpdatePointonmap)
	ON_COMMAND(ID_Position, &CCyan_DBA_LihuaView::OnPosition)
	ON_COMMAND(ID_Buffer, &CCyan_DBA_LihuaView::OnBuffer)
	ON_COMMAND(ID_ReDraw, &CCyan_DBA_LihuaView::OnRedraw)
	ON_COMMAND(ID_MeaSure, &CCyan_DBA_LihuaView::OnMeasure)
	ON_UPDATE_COMMAND_UI(ID_MeaSure, &CCyan_DBA_LihuaView::OnUpdateMeasure)
	ON_COMMAND(ID_SelectAll, &CCyan_DBA_LihuaView::OnSelectall)
	ON_UPDATE_COMMAND_UI(ID_SelectAll, &CCyan_DBA_LihuaView::OnUpdateSelectall)
	ON_COMMAND(ID_ClearAll, &CCyan_DBA_LihuaView::OnClearall)
	ON_COMMAND(ID_bufferSet, &CCyan_DBA_LihuaView::Onbufferset)
	ON_COMMAND(ID_ALLbuffer, &CCyan_DBA_LihuaView::OnAllbuffer)
	ON_COMMAND(ID_PullFrame, &CCyan_DBA_LihuaView::OnPullframe)
	ON_UPDATE_COMMAND_UI(ID_PullFrame, &CCyan_DBA_LihuaView::OnUpdatePullframe)
	ON_COMMAND(ID_FillPullFrame, &CCyan_DBA_LihuaView::OnFillpullframe)
	ON_UPDATE_COMMAND_UI(ID_FillPullFrame, &CCyan_DBA_LihuaView::OnUpdateFillpullframe)
END_MESSAGE_MAP()

// CCyan_DBA_LihuaView ����/����
//����������ʾ�Ķ���thisָ�룬������ȫ�ֱ����������
CCyan_DBA_LihuaView::CCyan_DBA_LihuaView(): m_pen(PS_SOLID,1 ,RGB(0,0,0)),m_brush(3,RGB(0,0,0))	//����ϵͳ�ṩ�Ĺ��캯�����õ����б��ʼ����ʽ�������ʼ���б�
	,CFormView(CCyan_DBA_LihuaView::IDD)
{
	// TODO: �ڴ˴���ӹ������
	pView = this;  //��ȫ�ֱ�����ֵ

	this->light = TRUE ;	//��ʼ��ΪTRUE������������
	this->m_index = 0;	//·����key
	this->hash_array = new int[ArraySize];	  //��ʼ�� 1kb �����ݿռ䣬��4kb���ڴ�
	memset(hash_array,0,ArraySize);	   //ȫ����ʼ��Ϊ0
	//////////////
	this->PointXyz = new PointStruct[ArraySize];
	this->m_pColor = RGB(0,0,0); 
	this->m_brushColor = RGB(0,0,0);  
	this->m_LineWide= 2;
	this->m_LineType = 0;
	this->m_index = 0;
	isEmptytrash = true;

	xmove = 0;
	ymove = 0;

	this->mapSet =false;
	this->sumLength = 0;

}

CCyan_DBA_LihuaView::~CCyan_DBA_LihuaView()
{
	delete [] this->PointXyz;	//ɾ��new ���������� delete []
	delete [] this->hash_array;
}

void CCyan_DBA_LihuaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CCyan_DBA_LihuaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CCyan_DBA_LihuaView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CCyan_DBA_LihuaView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCyan_DBA_LihuaView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCyan_DBA_LihuaView ���

#ifdef _DEBUG
void CCyan_DBA_LihuaView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCyan_DBA_LihuaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCyan_DBA_LihuaDoc* CCyan_DBA_LihuaView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCyan_DBA_LihuaDoc)));
	return (CCyan_DBA_LihuaDoc*)m_pDocument;
}
#endif //_DEBUG


// CCyan_DBA_LihuaView ��Ϣ�������
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PushNumΪ�����
//m_DrawCurrentΪ�����

///////////////////////////��Բ��////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawPoint()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=111;
}

void CCyan_DBA_LihuaView::OnUpdateDrawPoint(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==111);
}


///////////////////////////�����ǵ�////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawTriangle()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=112;
}

void CCyan_DBA_LihuaView::OnUpdateDrawTriangle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==112);
}


///////////////////////////������///////////////////////////////
void CCyan_DBA_LihuaView::OnDrawPolyline()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=12;
}

void CCyan_DBA_LihuaView::OnUpdateDrawPolyline(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==12);
}


///////////////////////////�������////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawPolygon()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=13;
}

void CCyan_DBA_LihuaView::OnUpdateDrawPolygon(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==13);
}


///////////////////////////��Բ////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawCircle()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=14;

}

void CCyan_DBA_LihuaView::OnUpdateDrawCircle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==14);

}


///////////////////////////������////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawText()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=15;
}

void CCyan_DBA_LihuaView::OnUpdateDrawText(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==15);
}


///////////////////////////��ָ����////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawNorth()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=16;
}

void CCyan_DBA_LihuaView::OnUpdateDrawNorth(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==16);
}




//////////////////2���Ŵ�///////////////////////////

void CCyan_DBA_LihuaView::On2xenlargement()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent = 411;
}


void CCyan_DBA_LihuaView::OnUpdate2xenlargement(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==411);
}
/////////////////3���Ŵ�///////////////////////////


void CCyan_DBA_LihuaView::On3xenlargement()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent = 412;
}


void CCyan_DBA_LihuaView::OnUpdate3xenlargement(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==412);
}




///////////2����С//////////////////////
void CCyan_DBA_LihuaView::On2xzoomout()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=421;
}

void CCyan_DBA_LihuaView::OnUpdate2xzoomout(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==421);
}


///////////3����С//////////////////////
void CCyan_DBA_LihuaView::On3xzoomout()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=422;
}


void CCyan_DBA_LihuaView::OnUpdate3xzoomout(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==422);
}


////////////////ƽ��//////////////////////
void CCyan_DBA_LihuaView::OnPan()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=43;
}


void CCyan_DBA_LihuaView::OnUpdatePan(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==43);
}

///////////ȫͼ��ʾ//////////////////////
void CCyan_DBA_LihuaView::OnFullmap()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=44;
	float min_x,min_y,max_x,max_y,scale1,scale2,xmove,ymove;
	CCyan_DBA_LihuaDoc* pDoc = GetDocument();	//��ȡDoc��ָ��
	//��Сֵ�����ֵ�ĳ�ʼֵ���ǳ����ף���ȷ���ܸ���
	min_x= FLT_MAX;	    //��С�ĸ����ֵ	  
	min_y= FLT_MAX;
	max_x= FLT_MIN;	   //���ĸ���Сֵ
	max_y= FLT_MIN;	   ////ϵͳ�����float�ĺ�
	SetCapture();
	//�����꣬���ҽ������̬Ϊ�ȴ�״̬
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	BOOL pb= pDoc->GetRect(&min_x,&min_y,&max_x,&max_y);
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	ReleaseCapture();
	if(!pb)
	{
		return;
	}
	else
	{
		scale1 = (max_x - min_x) / (m_wScreen);
		scale2 = (max_y - min_y) / (m_hScreen);
	}
	if(scale1<=scale2)
	{
		scale = scale2;
	}
	else
	{
		scale = scale1;
	}
	m_originX = min_x;
	m_originY = min_y;
	Invalidate();
}


void CCyan_DBA_LihuaView::OnUpdateFullmap(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==44);
}

//////////////////�Ŵ�///////////////////////////

void CCyan_DBA_LihuaView::OnEnlarge()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=45;
	
}


void CCyan_DBA_LihuaView::OnUpdateEnlarge(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==45);

}

///////////��С//////////////////////
void CCyan_DBA_LihuaView::OnZoomout()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=46;
}


void CCyan_DBA_LihuaView::OnUpdateZoomout(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==46);
}

///////////////////��ʼ����////////////////
void CCyan_DBA_LihuaView::OnBegindraw()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=511;
	this->light = FALSE;			//����Ч��
}


void CCyan_DBA_LihuaView::OnUpdateBegindraw(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(light)
	{
		pCmdUI->Enable(1);
	}
	else
	{
		pCmdUI->Enable(0);
	}
	

	

}

///////////////��������///////////////////
void CCyan_DBA_LihuaView::OnEnddraw()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=512;
	this->light = TRUE;
	this->hash_array[m_index - 1] = 0;	   //��hash������ض�ֵ����Ϊ0,��ʵ�ֶ���·��
	Invalidate();	//ʹ�������ڿͻ�����Ч, �����и�����ʾ�ĺ���
}


void CCyan_DBA_LihuaView::OnUpdateEnddraw(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(light)
	{
		pCmdUI->Enable(0);
	}
	else
	{
		pCmdUI->Enable(1);
	}
}





////////////////�������Կ�/////////////////
void CCyan_DBA_LihuaView::OnAttributes()
{
	// TODO: �ڴ���������������
	//�����йر����������ת��
	PushNum=0;
	m_DrawCurrent=31;
	ColorTool colorTool;
	colorTool.m_slider=1;
	if(IDOK==colorTool. DoModal ())
	{
		m_LineType=colorTool.linetype;
		m_LineWide=colorTool.m_slider;
		m_pColor=colorTool.penCo1or;   //��������ֵ
		m_brushColor=colorTool.brushCo1or;
	}
	m_pen.DeleteObject();
	m_pen.CreatePen(this->m_LineType,(int)this->m_LineWide,m_pColor);
}


void CCyan_DBA_LihuaView::OnUpdateAttributes(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==31);
}


//////////////////ִ�в�ѯ����//////////////////////////
void CCyan_DBA_LihuaView::OnSelect()
{
	// TODO: �ڴ���������������
	RouteSelect rs;
	if(IDOK==rs.DoModal ())
	{
		CString p,str;
		int selsetm_index = _ttoi(rs.m_index);		//_ttoi CString ->int
		m_StringMap.Lookup(selsetm_index,str);
		p.Format(_T("%d��λ��"),_ttoi(rs.m_index));	//��λ����Ϣ����p��
		if(!m_StringMap.IsEmpty())
		{
			if(str == "")
			{
				MessageBox(_T("No Message Found"),_T("��ѯʧ��"),MB_ICONWARNING|MB_OK);
			}
			else
			{
				MessageBox(p+_T("\n")+str,_T("��ѯ�ɹ�"),MB_OK);
			}
		}
	}

}


void CCyan_DBA_LihuaView::OnUpdateSelect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������	
}


 ////////////////////////��ѡ//////////////////////////
void CCyan_DBA_LihuaView::OnClicktoselect()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=61;
}


void CCyan_DBA_LihuaView::OnUpdateClicktoselect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==61);
}

///////////////////////��ѡ////////////////////
void CCyan_DBA_LihuaView::OnFrameselection()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=62;
}






void CCyan_DBA_LihuaView::OnUpdateFrameselection(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==62);
}

//////////////////ȫѡ////////////////
 void CCyan_DBA_LihuaView::OnSelectall()
{
	// TODO: �ڴ���������������
	
	//PushNum=0;
	//m_DrawCurrent=68;
	CCyan_DBA_LihuaDoc *pDoc=GetDocument();
	CClientDC client(this);
	if(pDoc->n_GraphSelect == 4096*3)
		{
			AfxMessageBox(_T("���ֻ��ѡ��12288��Ԫ��"));
			return ;
		}
		CRect rect( INT_MIN, INT_MIN, INT_MAX, INT_MAX);
	
		for(int i=1;i<=3; ++i)
		{
			int n=pDoc->GetGraphUpperBound(i);
			for(int j=0;j<=n; ++j)
			{
				BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
				if(a)
				{
					BOOL b = pDoc->AddSelectList(i,j);
					if(b)
					{
						pDoc->GetGraph(i,j)->Draw(&client,1);
					}
				}
			}
		}
	
}

 


void CCyan_DBA_LihuaView::OnUpdateSelectall(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//pCmdUI->SetRadio(m_DrawCurrent==68);
}


////////////////////////////��ѡ//////////////////////
void CCyan_DBA_LihuaView::OnSubtractselected()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=63;
}


void CCyan_DBA_LihuaView::OnUpdateSubtractselected(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==63);
}

////////////////////ȡ��ѡ��///////////////////
void CCyan_DBA_LihuaView::OnUncheck()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=64;
	auto pDoc = GetDocument();
	pDoc->n_GraphSelect = 0;		//ͨ��n_GraphSelect�����ƻ�ͼ��DocDraw
	Invalidate();	//ʹ�������ڿͻ�����Ч, �����и�����ʾ�ĺ���	  ǿ�ƴ����ػ�	
}


void CCyan_DBA_LihuaView::OnUpdateUncheck(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent==64);
}

///////////////////////ͼ��ɾ��/////////////////////
void CCyan_DBA_LihuaView::OnGraphicdeletion()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=65;
	auto pDoc = GetDocument();
	CClientDC clinet(this);
	CDraw* pDraw;
	for(int i = 0;i<pDoc->n_GraphSelect;++i)
	{
		pDraw = pDoc->GetGraph(pDoc->GraphSelect[i].Lb,pDoc->GraphSelect[i].Index);
		pDraw->Delete(true);
		this->isEmptytrash = false;
	    Invalidate();	//ʹ�������ڿͻ�����Ч, �����и�����ʾ�ĺ���	  ǿ�ƴ����ػ�
	}
}


void CCyan_DBA_LihuaView::OnUpdateGraphicdeletion(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(this->isEmptytrash)
	{
		pCmdUI->Enable(1);
	}
	else
	{
		pCmdUI->Enable(0);
	}
}


/////////////////ȡ��ɾ��///////////////////
void CCyan_DBA_LihuaView::OnUndodelete()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=66;
	auto pDoc = GetDocument();
	CClientDC clinet(this);
	CDraw* pDraw;
	for(int i = 0;i<pDoc->n_GraphSelect;++i)
	{
		pDraw = pDoc->GetGraph(pDoc->GraphSelect[i].Lb,pDoc->GraphSelect[i].Index);
		pDraw->Delete(false);
		this->isEmptytrash = true;
	    Invalidate();	//ʹ�������ڿͻ�����Ч, �����и�����ʾ�ĺ���	  ǿ�ƴ����ػ�

	}
}


void CCyan_DBA_LihuaView::OnUpdateUndodelete(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(this->isEmptytrash)
	{
		pCmdUI->Enable(0);
	}
	else
	{
		pCmdUI->Enable(1);
	}
}

/////////////��ջ���վ/////////////////
void CCyan_DBA_LihuaView::OnEmptytrash()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent=67;
	auto pDoc = GetDocument();
	pDoc->OnPack();
	Invalidate();	//ʹ�������ڿͻ�����Ч, �����и�����ʾ�ĺ���	  ǿ�ƴ����ػ�
	this->isEmptytrash = true;

}
 
void CCyan_DBA_LihuaView::OnUpdateEmptytrash(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(this->isEmptytrash)
	{
		pCmdUI->Enable(0);
	}
	else
	{
		pCmdUI->Enable(1);
	}
}


/////////////////////�����ͼ////////////////
void CCyan_DBA_LihuaView::OnSaveplot()
{
	// TODO: �ڴ���������������
	CClientDC   SHDC(this);
	CDC   memDC; 
	CRect   rect; 
	GetClientRect(rect); 
	memDC.CreateCompatibleDC(&SHDC); 
	CBitmap   bm; 
	int   Width   =   rect.Width();
	int   Height   =   rect.Height();
	bm.CreateCompatibleBitmap(&SHDC,Width,Height); 
	CBitmap*     pOld   =   memDC.SelectObject(&bm); 
	memDC.BitBlt(0,0,Width,Height,&SHDC,0,0,SRCCOPY); 
	memDC.SelectObject(pOld); 
	BITMAP     btm; 
	bm.GetBitmap(&btm); 
	DWORD     size   =   btm.bmWidthBytes*btm.bmHeight; 
	LPSTR   lpData   =(LPSTR)GlobalAllocPtr(GPTR,size); 
	BITMAPFILEHEADER       bfh; 
	bfh.bfReserved1   =   bfh.bfReserved2   =   0; 
	bfh.bfType   =   ((WORD)( 'M'<<8)|'B'); 
	bfh.bfSize   =   54   +   size; 
	bfh.bfOffBits   =   54; 
	BITMAPINFOHEADER     bih; 
	bih.biBitCount   =   btm.bmBitsPixel; 
	bih.biClrImportant   =   0; 
	bih.biClrUsed   =   0; 
	bih.biCompression   =   0; 
	bih.biHeight   =   btm.bmHeight; 
	bih.biPlanes   =   1; 
	bih.biSize   =   sizeof(BITMAPINFOHEADER); 
	bih.biSizeImage   =   size; 
	bih.biWidth   =   btm.bmWidth; 
	bih.biXPelsPerMeter   =   0; 
	bih.biYPelsPerMeter   =   0; 
	GetDIBits(GetDC()->GetSafeHdc(),bm,0,bih.biHeight,lpData,(BITMAPINFO*)&bih,DIB_RGB_COLORS); 
	CFileDialog  dlg(FALSE,_T(""),_T(""),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("*.bmp|*.bmp")); 
	if(dlg.DoModal()==IDOK) 
	{	CFile     bf; 
	CString   ss=dlg.GetPathName(); 
	if(bf.Open(ss,CFile::modeCreate|CFile::modeWrite)) 
	{ 
		bf.Write(&bfh,sizeof(BITMAPFILEHEADER)); 
		bf.Write(&bih,sizeof(BITMAPINFOHEADER)); 
		bf.Write(lpData,size); 
		bf.Close(); 
	} 
	GlobalFreePtr(lpData);
	}	

}



///////////////ɾ����ͼ////////////////
void CCyan_DBA_LihuaView::OnRemovebasemap()
{
	// TODO: �ڴ���������������
	CCyan_DBA_LihuaDoc* pDoc = GetDocument();
	pDoc->GetPDib()->Empty();
	isAdd = false;
	Invalidate();	//ǿ�ƴ����ػ�
}


////////////////����߽�////////////
void CCyan_DBA_LihuaView::OnInputboundary()
{
	// TODO: �ڴ���������������
	float x1,y1,x2,y2,scale1,scale2;
	BaseMapSet dig;
	dig.minLongitude= "������С����";
	dig.minLatitude = "γ����С����";
	dig.maxLongitude= "�����������";
	dig.maxLatitude = "γ���������";
	
	if(IDOK == dig.DoModal())
	{
		x1=(_ttoi(dig.m1)/60.0+_ttoi(dig.f1))/60.0+_ttoi(dig.d1);
		y1=(_ttoi(dig.m2)/60.0+_ttoi(dig.f2))/60.0+_ttoi(dig.d2);
		x2=(_ttoi(dig.m3)/60.0+_ttoi(dig.f3))/60.0+_ttoi(dig.d3);
		y2=(_ttoi(dig.m4)/60.0+_ttoi(dig.f4))/60.0+_ttoi(dig.d4);
		m_originX=x1;
		m_originY=y1;
		scale1= (x2-x1)/(m_wScreen);
		scale2= (y2-y1)/(m_hScreen);
		if(scale1>scale2)
		{
			scale=scale1;
		}
		else
		{
			scale=scale2;
		}
	 }
	 m_originXTo=m_originX;
	 m_originYTo=m_originY;
	 scaleNow=scale;
	 mapSet = true;
}






////////////�����һ����//////////////
void CCyan_DBA_LihuaView::OnPointonmap()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent = 232;
	MessageBox(_T("����ͼ������������֪��γ�ȵ�������"),_T("����˵��"),MB_OK);
}

void CCyan_DBA_LihuaView::OnUpdatePointonmap(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_DrawCurrent == 232);
}



//////////////��λ////////
void CCyan_DBA_LihuaView::OnPosition()
{
	// TODO: �ڴ���������������
	if(mapSet)
	{
		int x, y;	
		//scale = scaleNow;
		m_originX =	  m_originXTo;
		m_originY =	  m_originYTo;
		xmove = 0;
		ymove = 0;
		Invalidate();	//ǿ�ƴ����ػ�
		Position dlg;
		if(IDOK == dlg.DoModal())
		{
			DPtoVP(_ttof(dlg.longitude),_ttof(dlg.latitude),&x,&y);
			CClientDC client(this);
			CBrush brush1(RGB(0,0,0));
			client.SelectObject(&brush1);
			client.Ellipse(x-7,y-7,x+7,y+7);
		}
	}
	else MessageBox(_T("ֻ��ѯ�������λ�ã��������õ�ͼ�����������"),_T("ע��"),MB_ICONWARNING);

}



///////////////������//////////
void CCyan_DBA_LihuaView::OnBuffer()
{
	// TODO: �ڴ���������������
	MessageBox(_T("��ע�⣬��ǰ�Ƕ������ѡ���ͼ��Ԫ�ؽ��л�����������"));
	CCyan_DBA_LihuaDoc* pDoc=GetDocument();
	if(pDoc->n_GraphSelect==0||pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb==3)
	{
		MessageBox(_T("��ѡ�����ͼ��Ԫ��"));
		return;					
	}
	MapBuffer dlg;
	if(dlg.DoModal()==IDOK)
	{
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].buff=_ttoi(dlg.bufferLong);
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].sumbuf= 0;
		int x=DLtoVL(_ttoi(dlg.bufferLong));
		CClientDC client(this);
		pDoc->GetGraph(pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb,pDoc->GraphSelect[pDoc->n_GraphSelect-1].Index)->Draw(&client, 2, x);
	}

}





///////////////�����////////�Դ�
void CCyan_DBA_LihuaView::Onbufferset()
{
	// TODO: �ڴ���������������
		// TODO: �ڴ���������������
	MessageBox(_T("��ע�⣬��ǰ�Ƕ������ѡ���ͼ��Ԫ�ؽ��л�����������"));
	CCyan_DBA_LihuaDoc* pDoc=GetDocument();
	if(pDoc->n_GraphSelect==0||pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb==3)
	{
		MessageBox(_T("��ѡ�����ͼ��Ԫ��"));
		return;					
	}
	MapBuffer dlg;
	if(dlg.DoModal()==IDOK)
	{
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].buff=_ttoi(dlg.bufferLong);
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].sumbuf=_ttoi(dlg.bufferNumber);
		int x=DLtoVL(_ttoi(dlg.bufferLong));
		int y = DLtoVL(_ttoi(dlg.bufferNumber));
		CClientDC client(this);
		pDoc->GetGraph(pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb,pDoc->GraphSelect[pDoc->n_GraphSelect-1].Index)->Draw(&client, 3, x,y);
	}

}



//////��������

void CCyan_DBA_LihuaView::OnAllbuffer()
{
	// TODO: �ڴ���������������
	MessageBox(_T("��ע�⣬��ǰ�Ƕ�����ѡ�е�ͼ��Ԫ�ؽ��л�����������"));
	CCyan_DBA_LihuaDoc* pDoc=GetDocument();
	if(pDoc->n_GraphSelect==0||pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb==3)
	{
		MessageBox(_T("��ѡ�����ͼ��Ԫ��"));
		return;					
	}
	MapBuffer dlg;
	if(dlg.DoModal()==IDOK)
	{
		for(int i =0;i<pDoc->n_GraphSelect ;++i)
		{
			pDoc->GraphSelect[i].buff=_ttoi(dlg.bufferLong);
			pDoc->GraphSelect[i].sumbuf=_ttoi(dlg.bufferNumber);
			int x=DLtoVL(_ttoi(dlg.bufferLong));
			int y = DLtoVL(_ttoi(dlg.bufferNumber));
			CClientDC client(this);
			pDoc->GetGraph(pDoc->GraphSelect[i].Lb,pDoc->GraphSelect[i].Index)->Draw(&client, 3, x,y);
		}
		
	}
}



/////////��ͼ�ػ�/////////////
void CCyan_DBA_LihuaView::OnRedraw()
{
	// TODO: �ڴ���������������
	xmove = 0;
	ymove = 0;
	Invalidate();	//ǿ�ƴ����ػ�

}





//////////����////////////
void CCyan_DBA_LihuaView::OnMeasure()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent = 71;
}


void CCyan_DBA_LihuaView::OnUpdateMeasure(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(71 == m_DrawCurrent);
}




///����///////////

void CCyan_DBA_LihuaView::OnClearall()
{
	// TODO: �ڴ���������������
	if( IDOK == MessageBox(_T("��ȷ���𣬲����ֻ��ˣ�"),_T("����"),MB_ICONWARNING|MB_OKCANCEL))
	{
		auto pDoc = GetDocument();
		pDoc->n_GraphSelect = 0;
		pDoc->clearAll();
		this->Invalidate();
	}
	else 
	{
		 MessageBox(_T("��Ϊ���㣬���������"),_T("������"),MB_OK);
	}

}


///////////////����/////////////
void CCyan_DBA_LihuaView::OnPullframe()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent = 72;

}


void CCyan_DBA_LihuaView::OnUpdatePullframe(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(72 == m_DrawCurrent);
}




void CCyan_DBA_LihuaView::OnFillpullframe()
{
	// TODO: �ڴ���������������
	PushNum=0;
	m_DrawCurrent = 73;
}


 
void CCyan_DBA_LihuaView::OnUpdateFillpullframe(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(73 == m_DrawCurrent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








/////�������////////
void CCyan_DBA_LihuaView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CCyan_DBA_LihuaDoc *pDoc=GetDocument();
	CClientDC client(this);
	short lb,id_only;
	//////////////////��������///////////////////////
	if( m_DrawCurrent==15 )
	{
		float m_FontHeight ,m_FontWide ,m_TextAngle ,m_FontWeight;
		float m_TextX,m_TextY;
		CString m_TextString;
		int TextLong;
		CTextDlg textdlg;
		//��ɫ����
		textdlg.pColor = this->m_pColor;

		if(IDOK == textdlg.DoModal())
		{
			//��������йص�����������Ϊʵ�����괫��

			//m_FontHeight = textdlg.m_high;
			//m_FontWide =  textdlg.m_width;
			//m_FontWeight = textdlg.m_weight;
			m_TextString = textdlg.m_text;
			m_TextAngle = textdlg.m_angle;
			m_FontHeight = VLtoDL(textdlg.m_high);
			m_FontWide   = VLtoDL(textdlg.m_width);
			m_FontWeight = VLtoDL(textdlg.m_weight);
			TextLong = textdlg.m_text.GetLength();


			if(TextLong>0)
			{
				///////����ת��////////////
				float m_TextX;
				float m_TextY;
				VPtoDP(point.x,point.y,&m_TextX,&m_TextY);
			   ////////////////////////////////
				id_only=pDoc->GetGraphID(3);
				pDoc->AddText(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,m_TextX,m_TextY,
				  				m_TextAngle,VLtoDL(m_FontHeight*scaleNow/scale),VLtoDL(m_FontWide*scaleNow/scale),m_FontWeight, m_TextString)->Draw(&client,0);

			}

		}
	}
	//////////////////����Բ���㣬���͵�//////////////////////
	else if( m_DrawCurrent==14||m_DrawCurrent==111||m_DrawCurrent==112)
	{
		if(0==PushNum)
		{
			mPointOrign=point;
			mPointOld=point;
			//////////����ת��/////////////
			VPtoDP(point.x,point.y,&pstOrign.x,&pstOrign.y);	//��ȡԲ������
			PushNum++;
			SetCapture();

			if(m_DrawCurrent==111||m_DrawCurrent==112)
			{
				id_only=pDoc->GetGraphID(1);
				//mPointOrign.x��Բ�ĵ�x���꣬mPointOrign.y��Բ�ĵ�y���꣬5�ǰ뾶��ֵ

				pDoc->AddCircle(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,pstOrign.x,pstOrign.y,VLtoDL(3*scaleNow/scale),m_DrawCurrent)->Draw(&client,0);//���������һ��ʱ�������ǵ�
				PushNum=0;
				ReleaseCapture();
			}
		}else if(1==PushNum)
		{
			
			if(m_DrawCurrent==14) //Բ
			{
				//��ȡID
				id_only=pDoc->GetGraphID(1);
				//��뾶 
				float r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2)+pow((float)(mPointOrign.y-mPointOld.y),2));
				//View->Doc->Circle���캯��->Circle Draw����
				//��ֵʱ  VLtoDL(r)   x,y,r��Ϊʵ������
				pDoc->AddCircle(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,pstOrign.x,pstOrign.y,VLtoDL(r*scaleNow/scale),m_DrawCurrent)->Draw(&client,0);
			}
			PushNum =0;
			ReleaseCapture();
		}
      
		
	}
	////////////////////�������ߺͶ����////////////////////////////////////////
	else if(m_DrawCurrent==12||m_DrawCurrent==13)
	{

		//PointXyz[PushNum].x=point.x;
		//PointXyz[PushNum].y=point.y;
		//////////����ת��/////////////
		VPtoDP(point.x,point.y,&PointXyz[PushNum].x,&PointXyz[PushNum].y);
		if(0==PushNum)
		{
			SetCapture();
			mPointOld = point;
		}
		mPointOrign = mPointOld;
		++PushNum;
	}





	//////////////////���ָ����//////////////////////
	else if(m_DrawCurrent==16)
	{
		if(0==PushNum)
		{
			CString path = GetCurrentPath();
			m_image.Load( path +_T("..\\Cyan_DBA_Lihua\\res\\compass.png"));
			if(m_image.IsNull())
			{
				MessageBox(_T("δ�ҵ������Դ"));
			}
			if(m_image.GetBPP()==32)
			{
				int i ,j;
				for(i=0;i<m_image.GetWidth();i++)
				{
					for(j=0;j<m_image.GetHeight();j++)
					{
						byte *pByte=(byte *) m_image.GetPixelAddress(i,j);
						pByte[0]=pByte[0]*pByte[3]/255;
						pByte[1]=pByte[1]*pByte[3]/255;
						pByte[2]=pByte[2]*pByte[3]/255;
					}
				}
			}
			m_image.Draw(client.m_hDC,point.x-10,point.y-10);
			m_image.Destroy();
			++PushNum;//һ��ͼ�����һöָ����
		}
	}

/////////////////////ͼ�β���/////////////////////////////////////////////////////////////////////////////////////
	
	//////////2���Ŵ�////////////
	else if(m_DrawCurrent==411)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		x=a+m_wScreen/4;
		y=b-m_hScreen/4;
		VPtoDP(x,y,&m_originX,&m_originY);
		scale=scale/2;
		Invalidate();

	}
	//////////3���Ŵ�////////////
	else if(m_DrawCurrent==412)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		x=a+m_wScreen/3;
		y=b-m_hScreen/3;
		VPtoDP(x,y,&m_originX,&m_originY);
		scale=scale/3;
		Invalidate();
	}
	
	//////////2����С////////////
	else if(m_DrawCurrent==421)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		scale=scale*2;
		x=a-m_wScreen/4;
		y=b+m_hScreen/4;
		VPtoDP(x,y,&m_originX,&m_originY);
		Invalidate();

	}

	//////////3����С////////////
	else if(m_DrawCurrent==422)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		scale=scale*3;
		x=a-m_wScreen/3;
		y=b+m_hScreen/3;
		VPtoDP(x,y,&m_originX,&m_originY);
		Invalidate();
	}

	///////////////////////ƽ��//////////////////////
	else if(m_DrawCurrent==43)
	{
		if(0==PushNum)	//��һ�ΰ���
		{
			mPointOrign = point;
			//mPointOld = point;			//�����õ��Ļ�ͼģʽ��ʹ������£����Բ��������㣬һ���͹���

			++PushNum;
			SetCapture();	//��ȡ���
		}
	}

	/////////////////��ѡ�Ŵ�//////////////
	else if(m_DrawCurrent== 45)
	{
		int x0,y0;
		int x, y;
		if(PushNum==0)
		{
			mPointOrign=point;
			mPointOld=point;
			SetCapture();
			++PushNum;
		}
		else if(PushNum==1)
		{
			x0=min(mPointOrign.x,point.x);
			y0=max(mPointOrign.y,point.y);
			x=max(mPointOrign.x,point.x);
			y=min(mPointOrign.y,point.y);
			//x����Ŵ�ı�����
			float scale1=(float)(x-x0)/(float)m_wScreen;
			//y����Ŵ�ı�����
			float scale2=(float)(y-y0)/(float)m_hScreen;
			VPtoDP(x0,y0,&m_originX,&m_originY);
			if(scale1>=scale2) //ѡ������и����
			{
				scale = scale * scale1;
			}		
			else
			{
				scale = scale * scale2;
			}		
			ReleaseCapture();
			PushNum=0;
			Invalidate();	//ʹ�������ڿͻ�����Ч, �����и�����ʾ�ĺ���
			
		}

	}

	///////////////��ѡ��С//////////////
	///////////��ȫ���ŵ�����/////////////
	else if(m_DrawCurrent== 46)
	{
		int x0,y0;
		int x1,y1;
		int x ,y ;
		if(PushNum==0)
		{
			mPointOrign=point;
			mPointOld=point;
			SetCapture();
			++PushNum;
		}
		else if(PushNum==1)
		{
			x0=min(mPointOrign.x,point.x);
			y0=max(mPointOrign.y,point.y);
			x1=max(mPointOrign.x,point.x);
			y1=min(mPointOrign.y,point.y);
			//x������С�ı�����
			float scale1=(float)(x1-x0)/(float)m_wScreen;
			//y������С�ı�����
			float scale2=(float)(y0-y1)/(float)m_hScreen;
			if(scale1<=scale2) //ѡ������и�С��
			{
				scale = scale / scale1;
			}		
			else
			{
				scale = scale / scale2;
			}

			//m_originX = m_originX - scale*x0;
			//m_originY = m_originY -	scale*(m_wScreen -y0);
			x = -x0; //x = x0-x0;
			y =	m_hScreen +(m_hScreen - y0);
			VPtoDP(x,y,&m_originX,&m_originY);

			ReleaseCapture();
			PushNum=0;
			Invalidate();	//ʹ�������ڿͻ�����Ч, �����и�����ʾ�ĺ���	  ǿ�ƴ����ػ�
			
		}

	}

	//��ʼ·������
    else if(m_DrawCurrent== 511 && light == FALSE)
	{
		 CString str;
		 MapMessage message;
		 if(message.DoModal()== IDOK)
		 {
			 str = message.message;
			 CPoint p; 
			 float x, y;
			 VPtoDP(point.x,point.y,&x,&y);		//�߼�תʵ��
			 p.x = x;	
			 p.y = y;
			 m_PointMap[m_index] = p;
			 m_StringMap[m_index] = str;	//���ַ�������Map��
			 hash_array[m_index] = 1;	//�ѹ�ϣֵ����Ϊ1
			 ++m_index;
		 }
	}

	///////////////��ѡ///////////////
	else if(m_DrawCurrent == 61)
	{
		if(pDoc->n_GraphSelect == 4096*3)
		{
			AfxMessageBox(_T("���ֻ��ѡ��12288��Ԫ��"));
			return ;
		}
		for(int i = 1;i<=3;++i)
		{	
			int n = pDoc->GetGraphUpperBound(i);
			for(int j = 0;j<= n;++j)	
			{
				BOOL a = pDoc->GetGraph(i,j)->IsPoint(&client,point.x,point.y);
				if(a)
				{
					BOOL b = pDoc->AddSelectList(i,j);
					if(b)
					{
						pDoc->GetGraph(i,j)->Draw(&client,1);
					}
				}
			}
		}
	}
	

	////////////////��ѡ/////////////////////
	else if(m_DrawCurrent==62) 
	{	
		if(pDoc->n_GraphSelect == 4096*3)
		{
			AfxMessageBox(_T("���ֻ��ѡ��12288��Ԫ��"));
			return ;
		}
		int x1,y1,x2,y2;//��װ�߽������ֵ 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
	
		for(int i=1;i<=3; ++i)
		{
			int n=pDoc->GetGraphUpperBound(i);
			for(int j=0;j<=n; ++j)
			{
				BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
				if(a)
				{
					BOOL b = pDoc->AddSelectList(i,j);
					if(b)
					{
						pDoc->GetGraph(i,j)->Draw(&client,1);
					}
				}
			}
		}
	} 

	////////////////��ѡ/////////////////////
	else if(m_DrawCurrent==63) 
	{	
		int x1,y1,x2,y2;//��װ�߽������ֵ 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
	
		for(int i=1;i<=3; ++i)
		{
			int n= pDoc->GetGraphUpperBound(i);
			for(int j=0;j<=n; ++j)
			{
				BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
				if(a)
				{
					pDoc->DelSelectList(i,j);					
				}
			}
		}
		
		Invalidate();
	} 


	//////////ȫѡ////////////	�Ѿ��ڵ���¼�ʵ��
	//else if(m_DrawCurrent==68)
	//{
	//	
	//	if(pDoc->n_GraphSelect == 4096*3)
	//	{
	//		AfxMessageBox(_T("���ֻ��ѡ��12288��Ԫ��"));
	//		return ;
	//	}
	//	CRect rect( INT_MIN, INT_MIN, INT_MAX, INT_MAX);
	//
	//	for(int i=1;i<=3; ++i)
	//	{
	//		int n=pDoc->GetGraphUpperBound(i);
	//		for(int j=0;j<=n; ++j)
	//		{
	//			BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
	//			if(a)
	//			{
	//				BOOL b = pDoc->AddSelectList(i,j);
	//				if(b)
	//				{
	//					pDoc->GetGraph(i,j)->Draw(&client,1);
	//				}
	//			}
	//		}
	//	}
	//}














	///�����ȷ��������//////////
	else if(m_DrawCurrent == 232)
	{
		if(PushNum == 0)
		{
			PushNum++;
			mPointOrign=point;
		}
		else if(PushNum == 1)
		{
			PushNum++;
			mPointOld=point;
			float x1,y1,x2,y2,scale1,scale2;
			BaseMapSet dig;
			dig.minLongitude = "һ�ŵ�ľ���";
			dig.minLatitude = "һ�ŵ��γ��";
			dig.maxLongitude = "���ŵ�ľ���";
			dig.maxLatitude = "���ŵ��γ��";
		
			if(dig.DoModal()==IDOK)
			{
				x1=(_ttoi(dig.m1)/60.0+_ttoi(dig.f1))/60.0+_ttoi(dig.d1);
				y1=(_ttoi(dig.m2)/60.0+_ttoi(dig.f2))/60.0+_ttoi(dig.d2);
				x2=(_ttoi(dig.m3)/60.0+_ttoi(dig.f3))/60.0+_ttoi(dig.d3);
				y2=(_ttoi(dig.m4)/60.0+_ttoi(dig.f4))/60.0+_ttoi(dig.d4);
				scale1 = fabs((x2-x1))/(1.0*fabs((double)(mPointOld.x-mPointOrign.x)));
				scale2 = fabs((y2-y1))/(1.0*fabs((double)(mPointOld.y-mPointOrign.y)));
				if(scale1>scale2)
				{
		    		scale=scale1;
				}
				else
				{
		    		scale=scale2;
				}
				m_originX = x1-mPointOrign.x*scale;
				m_originY = y1-scale*(m_hScreen-mPointOrign.y);
			}
			m_originXTo =m_originX;
			m_originYTo=m_originY;
			scale1=scale;
			mapSet = true; 
		}
	}
	////////////////����//////////////
	else if(m_DrawCurrent == 71)
	{


		
		if(0==PushNum)
		{
			SetCapture();
			mPointOld = point;
		}
		if(PushNum!=0)
		{
			//if(isAdd==true)
			//{
			//	float x1,y1,x2,y2;
			//	VPtoDP(point.x,point.y,&x1,&y1);
			//	VPtoDP(mPointOrign.x,mPointOrign.y,&x2,&y2);
			//	//sumLength += GetDistance(point.x ,point.y,mPointOrign.x,mPointOrign.y);
			//	sumLength += GetDistance(x1,y1,x2,y2);
			//}
			//else
			//{  
				sumLength += (int)sqrt((float)(point.x - mPointOrign.x)*(point.x - mPointOrign.x)+(float)(point.y - mPointOrign.y)*(point.y - mPointOrign.y));	
			//}
		}
		mPointOrign = mPointOld;
		++PushNum;
	}
   /////////////////����///////////////////
	else if(m_DrawCurrent == 72)
	{
		int x1,y1,x2,y2;//��װ�߽������ֵ 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
		client.SelectStockObject(NULL_BRUSH);
		client.Rectangle(x1,y1,x2,y2);
		
	}

	else if(m_DrawCurrent == 73)
	{
		int x1,y1,x2,y2;//��װ�߽������ֵ 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
		client.SelectObject(&m_pen);
		client.Rectangle(x1,y1,x2,y2);
		
	}

/////////////////////////////////////////////////////////
	CFormView::OnLButtonDown(nFlags, point);
}



/////////////���̧��/////////////////////
void CCyan_DBA_LihuaView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	////////���ƽ��////////////
	if(m_DrawCurrent==43&&PushNum>0)
	{
		PushNum =0;
		ReleaseCapture();	//�ͷ����
	}
	CFormView::OnLButtonUp(nFlags, point);
}


/////////////���˫��///////////
void CCyan_DBA_LihuaView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CCyan_DBA_LihuaDoc* pDoc =GetDocument(); //ͨ���������������ͼ���ĵ��Ľ���,��ȡ�ĵ���ָ��
	CFormView::OnLButtonDblClk(nFlags, point);
	CClientDC client(this);
	int id_only;
	/////////////������ߺͶ����////////////////////
	if((m_DrawCurrent==12||m_DrawCurrent==13)&&PushNum>0)
	{
		id_only = pDoc->GetGraphID(2);
		VPtoDP(point.x,point.y,&PointXyz[PushNum].x,&PointXyz[PushNum].y);
		++PushNum;
		//PointXyz�ڵ���ʱ�Ѿ�ȫ���������ϵת��
		pDoc->AddPLine(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,
							PushNum,PointXyz,m_DrawCurrent)->Draw(&client,0);			  
		ReleaseCapture();
		PushNum=0;
	}
	///////////����//////////////
	else if(71 ==  m_DrawCurrent)
	{
		//VPtoDP(point.x,point.y,&PointXyz[PushNum].x,&PointXyz[PushNum].y);
		++PushNum;
		//PointXyz�ڵ���ʱ�Ѿ�ȫ���������ϵת��
		CString str;
		if(isAdd == true)
		{
			sumLength = VLtoDL(sumLength)*100;
			str.Format(_T("�ܳ���Ϊ��%lf KM"),sumLength);
		}
		else
		{
			str.Format(_T("�ܳ���Ϊ��%lf "),sumLength);
		}
		
		MessageBox(str,_T("��������"),MB_OK);
		sumLength = 0;
		ReleaseCapture();
		PushNum=0;
		Invalidate();
		
	}
}




/////////////����ƶ��¼�////////////////////////////
void CCyan_DBA_LihuaView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC client(this);
	//CPen pen;
	//pen.CreatePen(this->m_LineType,(int)this->m_LineWide,m_pColor);
	//client.SelectObject(&pen);
	client.SelectObject(&m_pen);
	client.SetROP2(R2_NOTXORPEN); //ѡ�񻭱ʷ�ɫ�Ļ滭ģʽ
	float x ;
	float y;
	VPtoDP(point.x,point.y,&x,&y);
	CString str; 
	str.Format(_T("�߼����꣺x=%d,y=%d   �����ߣ�%f                ʵ�����꣺ x = %f y =%f"),point,scale,x,y);
	CMainFrame* pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;                                                                        // ���������ָ��
	CMFCStatusBar* pStatus=&pFrame->m_wndStatusBar;
	pStatus->SetPaneText(0,str);

	//////////////����Բ������///////////////////////////
	if((14==m_DrawCurrent)&&PushNum>0)//����ǻ���Բ��Բ�����򣬲����Ѿ����µ�һ��
	{
		//����ƶ��¼�����ֵ��ֱ��������ģʽ�������ɶ�̬Ч��
		if(mPointOld!=point)
		{
			//��̬��ͼ�Ĳ���
			//��mPointOrign->mPointOld ���� mPointOld��ǰһ��,����Ҫ���
			//���»�һ��mPointOrign ��point
			float r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2)+pow((float)(mPointOrign.y-mPointOld.y),2));
			client.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
			r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2)+pow((float)(mPointOrign.y-point.y),2));
			client.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);//�ӵڶ��ο�ʼ�������Ȳ����ٻ�ͼ
			mPointOld=point;
		}
	}

	////////////////////�������ߺͶ����////////////////////
	else if((12==m_DrawCurrent||13==m_DrawCurrent)&&PushNum>0)	//����һ�κ�
	{
		/****************************
		MoveTo:���Ϊ�߶ε�һ����
		LineTo:�ӵ�һ���㻭�ߵ��ڶ�����
		�������ڻ�ͼģʽ����Ϊ	R2_NOTXORPEN
		���Ե�һ�����԰�ɫ����
			�ڶ������Ա�ɫ����
			�������񶯻�
		****************************/
		if(mPointOrign!=point)
		{
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
			mPointOld =point;
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
		}
	}

	////////////����////////
	else if(71==m_DrawCurrent&&PushNum>0)
	{
		if(mPointOrign!=point)
		{
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
			mPointOld =point;
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
		}
	}

	////////////////////ƽ��////////////////////
	else if(43==m_DrawCurrent&&PushNum>0)
	{
		/*****************************
		  SetCursor(LoadCursor(NULL,IDC_ARROW));

		LoadCursor
		��һ����������Ҫ������ĳ����ʵ��.
			��ʹ��ϵͳԤ�������ʱ��Ҫ����Ϊ�ա�
			��Ҫʹ���Զ������ʱ������ΪAfxGetInstanceHandle()
		�ڶ���������
			����һ������ΪNULLʱ
				DC_APPSTARTING ��׼�ļ�ͷ��Сɳ©
				IDC_ARROW ��׼�ļ�ͷ
				IDC_CROSS ʮ�ֹ��
				IDC_HELP ��׼�ļ�ͷ���ʺ�
				IDC_IBEAM ���ֹ��
				IDC_NO ��ֹȦ
				IDC_SIZEALL �����ͷָ�򶫡������ϡ���
				IDC_SIZENESW ˫��ͷָ�򶫱�������
				IDC_SIZENS ˫��ͷָ���ϱ�
				IDC_SIZENWSE ˫��ͷָ�������Ͷ���
				IDC_SIZEWE ˫��ͷָ����
				IDC_UPARROW ��ֱ��ͷ
				IDC_WAIT ɳ©	���ȴ�Ȧ��
				IDC_NULL ��
				IDC_HAND ��
				IDC_APPSTARTING ��ͷ��ɳ©
			���ڶ�������ΪAfxGetInstanceHandle()ʱ������Դ�л���
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(��������ID)));
		*************************/
		if(mPointOrign!=point)
		{
			SetCursor(LoadCursor(NULL,IDC_SIZEALL));
			VPtoDP(xmove,ymove,&xmoveTo,&ymoveTo);
			m_originX = m_originX - scale*(point.x - mPointOrign.x);
			m_originY = m_originY + scale*(point.y - mPointOrign.y);

			////��ͼƽ��
			
			if(isAdd)
			{
				DPtoVP(xmoveTo,ymoveTo,&xmove,&ymove);
			}
			


			mPointOrign = point;
			Invalidate();	//ʹͼ���ػ�
			ReleaseCapture();
		}


	}


	////////////////////��ѡ�Ŵ�////////////////////
	else if(45==m_DrawCurrent&&PushNum>0)
	{
		if(mPointOld!=point)
		{

			client.Rectangle(mPointOrign.x,mPointOrign.y,mPointOld.x,mPointOld.y);
			client.Rectangle(mPointOrign.x,mPointOrign.y,point.x,point.y);
			mPointOld=point;
		}
	}


	////////////////////��ѡ��С////////////////////
	else if(46==m_DrawCurrent&&PushNum>0)
	{
		if(mPointOld!=point)
		{
			client.Rectangle(mPointOrign.x,mPointOrign.y,mPointOld.x,mPointOld.y);
			client.Rectangle(mPointOrign.x,mPointOrign.y,point.x,point.y);
			mPointOld=point;
		}
	}
	/////////////////////////////////////////////////
	CFormView::OnMouseMove(nFlags, point);
}








///////////////�Ҽ�����/////////////////////////////
void CCyan_DBA_LihuaView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC client(this);
	int x,y;
	float r;
	///////////////////////////
	//CPen pen;
	////�����͸�Ϊʵ�ߣ���ֹ��Ϊ���߲�������
	//pen.CreatePen( PS_SOLID,(int)this->m_LineWide,m_pColor);
	//client.SelectObject(pen);
	//////////////////////////////////////
	client.SelectObject(&m_pen);
	client.SetROP2(R2_NOTXORPEN);
	////����ʵ�ʲ�����Add��������������ֱ�ӻ�
	////////////����Բ/////////////////
	if((14==m_DrawCurrent)&&PushNum>0)
	{
		r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2)+pow((float)(mPointOrign.y-point.y),2));
		client.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
		////ǿ�ƴ����ػ�////// ������ֱ���ػ�Ϳ�����,���ϴ��붼����ʡ��
		//Invalidate();
		PushNum=0;
		ReleaseCapture();
	}

	///////////////�������߶����//////////////////////
	else if((12==m_DrawCurrent||13==m_DrawCurrent)&&PushNum>0)
	{
		//��
		CPoint *pointArray;
		pointArray = new CPoint[PushNum];
		for(int i =0;i<this->PushNum;++i)  //��������洢���۵��ֵ����Щ�۵㶼�ڰ���L���󱻼���PointXyz��
		{

			 DPtoVP(PointXyz[i].x,PointXyz[i].y,(int *)&pointArray[i].x,(int *)&pointArray[i].y);
		}
		client.Polyline(pointArray,this->PushNum);
		client.MoveTo(mPointOrign);
		client.LineTo(mPointOld);
		////ǿ�ƴ����ػ�////// ������ֱ���ػ�Ϳ����� ,���ϴ��붼����ʡ��
		Invalidate();
		/////////
		PushNum=0;
		//memset(PointXyz,0,ArraySize);//�������
		ReleaseCapture();
	}
	///////////////////////////////////
	CFormView::OnRButtonDown(nFlags, point);
}






////////////�ػ�//////////////////////////////
void CCyan_DBA_LihuaView::OnPaint()
{
	//ԭʼͼ���ػ�
	CPaintDC paintDc(this); // device context for painting
	OnDraw(&paintDc);

	//·���ػ�
	CString str;
	CPoint p;
	paintDc.SetBkMode(TRANSPARENT);
	paintDc.SelectObject(m_pen);
	
	for(int i = 0; i<m_index; ++i)
	{
		m_PointMap.Lookup(i,p);
		int x,y;
		DPtoVP(p.x,p.y,&x,&y);
		if( i == 0 || ( hash_array[i-1] == 0)) //��0��ʼ���ո�Ϊ����
		{
			paintDc.MoveTo(x,y);
		}
		else
		{
			paintDc.LineTo(x,y);
		}
		str.Format(_T("%d"),i);
		paintDc.TextOut(x,y,str);

	}
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
}

void CCyan_DBA_LihuaView::OnDraw(CDC *pDC)
{
	CCyan_DBA_LihuaDoc* pDoc =GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	{
		return;
	}
	//����ͼ
	ImgCenterDib *pDib = pDoc->GetPDib();
	//CSize sizeFileDib = pDib->GetDimensions();
	//imgWidth = sizeFileDib.cx;
	//imgHeight = sizeFileDib.cy;
	
	//pDib->Draw(pDC,CPoint(xmove,ymove),sizeFileDib);
	CSize size;
	size.cx = m_wScreen;
	size.cy = m_hScreen;
	pDib->Draw(pDC,CPoint(xmove,ymove),size);
	//��ʸ��ͼ��
	pDoc->DocDraw(pDC,0);

	
}

/////////////(Ĭ���Զ�����)ȡ��Ļ��С///////////////////
void CCyan_DBA_LihuaView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_wScreen=cx;	
	m_hScreen=cy;
}

//////////////��ȡ��Ļ�߶�/////////////////
int CCyan_DBA_LihuaView::GetScreenH()
{
	return this->m_hScreen;
}

//////////////��ȡ��Ļ���///////////////
int CCyan_DBA_LihuaView::GetScreenW()
{
	return this->m_wScreen;
}


double CCyan_DBA_LihuaView::rad(double d)	//��ȡ����
{
	return d * pi * 180.0;
}

//////////���뾭γ��///////////
double CCyan_DBA_LihuaView::GetDistance(double lng1,double lat1,double lng2,double lat2)	//��ȡ����
{
	double radLat1 = rad(lat1);
	double radLat2 = rad(lat2);
	double a = radLat1 - radLat2;
	double b = rad(lng1) - rad(lng2);
	double s = asin(sqrt(pow(sin(a/2),2) + cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
	s = s * EARTH_RADIUS;
	return s;
}







