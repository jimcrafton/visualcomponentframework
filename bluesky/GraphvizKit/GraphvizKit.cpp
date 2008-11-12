//GraphvizKit.cpp

#include "GraphvizKit.h"

using namespace VCF;




GVC_t* GraphvizKit::gvCtx = NULL;
GraphicsContext* GraphvizKit::currentCtx = NULL;

static int lastGS = 0;


void GraphvizKit::init( int argc, char** argv )
{
	GraphvizKit::gvCtx = gvContext();
	gvParseArgs(GraphvizKit::gvCtx, argc, argv);
	

	static gvrender_engine_t engine = {
								GraphvizKit::beginJob,
								GraphvizKit::endJob,
								0,							/* begin_graph */
								0,							/* end_graph */
								0,							/* begin_layer */
								0,							/* end_layer */
								GraphvizKit::beginPage,
								GraphvizKit::endPage,
								0,							/* begin_cluster */
								0,							/* end_cluster */
								0,							/* begin_nodes */
								0,							/* end_nodes */
								0,							/* begin_edges */
								0,							/* end_edges */
								0,							/* begin_node */
								0,							/* end_node */
								0,							/* begin_edge */
								0,							/* end_edge */
								GraphvizKit::beginAnchor,
								0,							/* end_anchor */
								GraphvizKit::textpara,
								0,
								GraphvizKit::ellipse,
								GraphvizKit::polygon,
								GraphvizKit::bezier,
								GraphvizKit::polyline,
								0,							/* comment */
								0,							/* library_shape */};

	static gvrender_features_t engineFeatures = {
								GVRENDER_DOES_TRANSFORM, /* flags */
								4.,							/* default pad - graph units */
								NULL,						/* knowncolors */
								0,							/* sizeof knowncolors */
								RGBA_DOUBLE				/* color_type */
							};



	static gvplugin_installed_t renderTypes[] = {
				{0, "vcf", 1, &engine, &engineFeatures},
				{0, NULL, 0, NULL, NULL}, };

	
	static gvdevice_features_t deviceFeatures = {
								GVDEVICE_BINARY_FORMAT
								  | GVDEVICE_DOES_TRUECOLOR,/* flags */
								{0.,0.},                    /* default margin - points */
								{0.,0.},                    /* default page width, height - points */
								{120.,120.}                  /* dpi */
							};

	static gvplugin_installed_t devices[] = {
		{FORMAT_BMP, "graphicsctx:vcf", 8, NULL, &deviceFeatures},
		{0, NULL, 0, NULL, NULL} };


	GraphvizKit::install( GraphvizKit::gvCtx, API_render, "vcf", 0, 
						"vcf", NULL, &renderTypes[0] );

	GraphvizKit::install( GraphvizKit::gvCtx, API_device, "graphicsctx:vcf", 0, 
						"vcf", NULL, &devices[0] );
}

void GraphvizKit::terminate()
{
	gvFreeContext(GraphvizKit::gvCtx);
}


void GraphvizKit::renderGraph( Agraph_t* g, GraphicsContext* ctx )
{
	GraphvizKit::currentCtx = ctx;
	gvRender(GraphvizKit::gvCtx, g, "graphicsctx", NULL);
	GraphvizKit::currentCtx = NULL;
}


void GraphvizKit::beginJob(GVJ_t *job)
{

}

void GraphvizKit::endJob(GVJ_t *job)
{
	
}


void GraphvizKit::beginPage(GVJ_t *job)
{
	if (!job->external_context && !job->context) {
		job->context = GraphvizKit::currentCtx;
		
		
	}

	GraphicsContext* ctx = (GraphicsContext*)job->context;
	if ( NULL != ctx ) {
		lastGS = ctx->saveState();

		Matrix2D mat;// = Matrix2D::translation( 0, job->height );
		mat *= Matrix2D::scaling( job->scale.x, job->scale.y );
		mat *= Matrix2D::rotation( job->rotation );
		mat *= Matrix2D::translation( job->translation.x, job->translation.y );


		Matrix2D adjustedMat = *ctx->getCurrentTransform();
		adjustedMat *= mat;
		ctx->setCurrentTransform( adjustedMat );

	}
}


void GraphvizKit::endPage(GVJ_t *job)
{
	GraphicsContext* ctx = (GraphicsContext*)job->context;
	if ( NULL != ctx ) {
		ctx->restoreState(lastGS);
	}
}

void GraphvizKit::beginAnchor(GVJ_t *job, char *url, char *tooltip, char *target)
{

}

void GraphvizKit::textpara(GVJ_t *job, pointf p, textpara_t *para)
{
	GraphicsContext* ctx = (GraphicsContext*)job->context;

	int gcs = ctx->saveState();

	String text = para->str;

	/* adjust text position */
	switch (para->just) {
		case 'r': {
			p.x -= para->width;
		}			
		break;

		case 'l': {
			p.x -= 0.0;
		}
		break;

		case 'n': default: {
			p.x -= para->width / 2.0;
		}
		break;
	}

	p.y -=  para->yoffset_centerline;

	Font f( para->fontname, para->fontsize );

	ctx->setCurrentFont( &f);

	ctx->textAt( p.x, p.y, text );


	ctx->restoreState(gcs);
}

void GraphvizKit::ellipse(GVJ_t *job, pointf *A, int filled)
{
	GraphicsContext* ctx = (GraphicsContext*)job->context;

	Rect r;
	r.left_ = A[0].x - (A[1].x - A[0].x)/2.0;
	r.right_ = A[0].x + (A[1].x - A[0].x)/2.0;

	r.top_ = A[0].y - (A[1].y - A[0].y)/2.0;
	r.bottom_ = A[0].y + (A[1].y - A[0].y)/2.0;

	ctx->ellipse( r.left_, r.top_, r.right_, r.bottom_ );

	if (filled) {
		Color c(job->obj->fillcolor.u.RGBA [0], job->obj->fillcolor.u.RGBA [1], job->obj->fillcolor.u.RGBA [2], job->obj->fillcolor.u.RGBA [3] );

		ctx->setColor(&c);

		ctx->fillPath();
	}

	Color c2(job->obj->pencolor.u.RGBA [0], job->obj->pencolor.u.RGBA [1], job->obj->pencolor.u.RGBA [2], job->obj->pencolor.u.RGBA [3] );
	ctx->setColor(&c2);

	ctx->strokePath();
}

void GraphvizKit::polygon(GVJ_t *job, pointf *A, int n, int filled)
{
	GraphicsContext* ctx = (GraphicsContext*)job->context;

	std::vector<Point> pts(n);

	for (int i=0;i<n;i++ ) {
		pts[i].x_ = A[i].x;
		pts[i].y_ = A[i].y;
	}

	ctx->polyline(pts);
	ctx->closePath(pts[0]);



	if (filled) {
		Color c(job->obj->fillcolor.u.RGBA [0], job->obj->fillcolor.u.RGBA [1], job->obj->fillcolor.u.RGBA [2], job->obj->fillcolor.u.RGBA [3] );

		ctx->setColor(&c);

		ctx->fillPath();
	}

	Color c2(job->obj->pencolor.u.RGBA [0], job->obj->pencolor.u.RGBA [1], job->obj->pencolor.u.RGBA [2], job->obj->pencolor.u.RGBA [3] );
	ctx->setColor(&c2);

	ctx->strokePath();
}

void GraphvizKit::bezier(GVJ_t *job, pointf *A, int n, int arrow_at_start, int arrow_at_end, int filled)
{
	GraphicsContext* ctx = (GraphicsContext*)job->context;

	

	for (int i=0;i<n;i++ ) {
		if ( i> 0 && (i%3 == 0)) {
			ctx->curve( A[i-3].x, A[i-3].y,
						A[i-2].x, A[i-2].y,
						A[i-1].x, A[i-1].y,
						A[i].x, A[i].y );

		}
	}	



	if (filled) {
		Color c(job->obj->fillcolor.u.RGBA [0], job->obj->fillcolor.u.RGBA [1], job->obj->fillcolor.u.RGBA [2], job->obj->fillcolor.u.RGBA [3] );

		ctx->setColor(&c);

		ctx->fillPath();
	}

	Color c2(job->obj->pencolor.u.RGBA [0], job->obj->pencolor.u.RGBA [1], job->obj->pencolor.u.RGBA [2], job->obj->pencolor.u.RGBA [3] );
	ctx->setColor(&c2);

	ctx->strokePath();
}

void GraphvizKit::polyline(GVJ_t *job, pointf *A, int n)
{
	GraphicsContext* ctx = (GraphicsContext*)job->context;

	std::vector<Point> pts(n);

	for (int i=0;i<n;i++ ) {
		pts[i].x_ = A[i].x;
		pts[i].y_ = A[i].y;
	}
	
	Color c2(job->obj->pencolor.u.RGBA [0], job->obj->pencolor.u.RGBA [1], job->obj->pencolor.u.RGBA [2], job->obj->pencolor.u.RGBA [3] );
	ctx->setColor(&c2);

	ctx->strokePath();
}



boolean GraphvizKit::install(GVC_t * gvc, api_t api,
	char *typestr, int quality, char *packagename, char *path,
	gvplugin_installed_t * typeptr)
{
	gvplugin_available_t *plugin, **pnext;
#define TYPSIZ 63
	char *p, pins[TYPSIZ+1], pnxt[TYPSIZ+1];
	
	if (api < 0)
		return FALSE;
	
	strncpy(pins, typestr, TYPSIZ);
	if ((p = strchr(pins, ':')))
		*p = '\0';
	
	/* point to the beginning of the linked list of plugins for this api */
	pnext = &(gvc->apis[api]);
	
	/* keep alpha-sorted and insert new duplicates ahead of old */
	while (*pnext) {
		strncpy(pnxt, (*pnext)->typestr, TYPSIZ);
		if ((p = strchr(pnxt, ':')))
			*p = '\0';
		if (strcmp(pins, pnxt) <= 0)
			break;
		pnext = &((*pnext)->next);
	}
	
	/* keep quality sorted within type and insert new duplicates ahead of old */
	while (*pnext) {
		strncpy(pnxt, (*pnext)->typestr, TYPSIZ);
		if ((p = strchr(pnxt, ':')))
			*p = '\0';
		if (strcmp(pins, pnxt) != 0)
			break;
		if (quality >= (*pnext)->quality)
			break;
		pnext = &((*pnext)->next);
	}
	
	plugin = GNEW(gvplugin_available_t);
	plugin->next = *pnext;
	*pnext = plugin;
	plugin->typestr = typestr;
	plugin->quality = quality;
	plugin->packagename = packagename;	/* packagename,  all packages */
	plugin->path = path;	/* filepath for .so, or NULL for builtins */
	plugin->typeptr = typeptr;	/* null if not loaded */
	
	return TRUE;
}

void AGraph::freeGraph( Agraph_t* g ) 
{
	agclose(g);
}
void AGraph::layout()  
{
	GVC_t* gvc = GraphvizKit::getContext();
	
	gvLayout( gvc, graph_.get(), "dot" );			
}

void AGraph::render( GraphicsContext* ctx ) 
{
	
	GraphvizKit::renderGraph( graph_.get(), ctx );
	
	GVC_t* gvc = GraphvizKit::getContext();
}

void AGraph::load( const String& graph )
{
	AnsiString tmp(graph);
	std::vector<char> data(tmp.size()+1);
	data.assign( tmp.begin(), tmp.end() );

	graph_ = AgraphPtr( agmemread( &data.front() ), &AGraph::freeGraph );
}	

void AGraph::loadFromFile( const String& filename )
{
	FILE* f = fopen( filename.ansi_c_str(), "rb" );
	if ( NULL != f ) {
		graph_ = AgraphPtr( agread( f ), &AGraph::freeGraph );

		fclose(f);
	}
}