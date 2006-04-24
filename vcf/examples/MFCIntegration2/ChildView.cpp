// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFCIntegration2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


using namespace VCF;


/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	GraphicsContext ctx ( (OSHandleID) dc.GetSafeHdc() );

	ctx.textAt( 100, 200, "Hell World!!!" );
	
	CRect r;
	GetClientRect(r);

	Rect drawingRect(0,0,r.Width(),r.Height());

	ctx.setDrawingArea( drawingRect );

	GraphicsContext* paintCtx = ctx.getDrawingArea()->getImageContext();


	paintCtx->setColor( Color::getColor("white") );
	paintCtx->rectangle( &drawingRect );
	paintCtx->fillPath();

	BezierCurve curve;

	std::vector<Point> pts(5);
	pts[0].x_ = 20;
	pts[0].y_ = 20;

	pts[1].x_ = 100;
	pts[1].y_ = 60;

	pts[2].x_ = 10;
	pts[2].y_ = 256;

	pts[3].x_ = 200;
	pts[3].y_ = 10;

	pts[4].x_ = 40;
	pts[4].y_ = 80;

	
	curve.polyline( pts );

	BasicStroke stroke;

	stroke.setColor( Color::getColor("red") );
	stroke.setWidth( 5 );

	paintCtx->setCurrentStroke( &stroke );

	paintCtx->draw( &curve );


	stroke.setColor( Color::getColor("blue") );	
	paintCtx->setRotation( 90 );
	paintCtx->setTranslation( 200, 100 );
	paintCtx->draw( &curve );



	ctx.flushDrawingArea();

	ctx.deleteDrawingArea();

	ctx.textAt( 100, 200, "More Hell World!!!" );
}

