#ifndef _VCF_GRAPHVIZKIT_H__
#define _VCF_GRAPHVIZKIT_H__

#define WITH_CODEGENS 1

#include "gvc.h"
#include "memory.h"
#include "types.h"
#include "gvplugin.h"
#include "gvcjob.h"
#include "gvcint.h"
#include "gvplugin_device.h"
#include "gvplugin_render.h"
#include "graph.h"


// We don't need any of this if we've disabled pragma linking
#ifndef VCF_DISABLE_PRAGMA_LINKING

/**
Handle the extension based on the compiler
*/
# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80"
#   elif (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
#  ifdef __BORLANDC__
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif


#ifdef _DEBUG 
	#define GRAPHVIZKIT_LIBDLL	"GraphvizKit_"_LIB_CPLVERNUM"_d.lib"
	#define GRAPHVIZKIT_LIBS	"GraphvizKit_"_LIB_CPLVERNUM"_sd.lib"
#else
	#define GRAPHVIZKIT_LIBDLL	"GraphvizKit_"_LIB_CPLVERNUM".lib"
	#define GRAPHVIZKIT_LIBS	"GraphvizKit_"_LIB_CPLVERNUM"_s.lib"
#endif



//auto link stuff
#if defined(_MSC_VER) || defined(__BORLANDC__)
	#ifdef USE_GRAPHVIZKIT_DLL
		#pragma message( "linking to " GRAPHVIZKIT_LIBDLL )
		#define GRAPHVIZKIT_DLL
		// using dynamic link library		
		#pragma comment(lib, GRAPHVIZKIT_LIBDLL)
	#elif defined USE_GRAPHVIZKIT_LIB
		#pragma message( "linking to " GRAPHVIZKIT_LIBS )
		// using statically linked library
		#pragma comment(lib, GRAPHVIZKIT_LIBS)
	#endif

#endif //VCF_MSC





//this sets up a "dependencies" set of defines

#ifdef USE_GRAPHVIZKIT_DLL
# 	ifndef GRAPHVIZKIT_DLL
#		define GRAPHVIZKIT_DLL
# 	endif
#elif defined (USE_GRAPHVIZKIT_LIB)
# 	ifndef GRAPHVIZKIT_LIB
#		define GRAPHVIZKIT_LIB
# 	endif
#endif

#ifdef GRAPHVIZKIT_DLL
# 	ifndef USE_GRAPHICSKIT_DLL
#		define USE_GRAPHICSKIT_DLL
# 	endif
#elif defined (GRAPHVIZKIT_LIB)
# 	ifndef USE_GRAPHICSKIT_LIB
#		define USE_GRAPHICSKIT_LIB
# 	endif
#endif


#endif // VCF_DISABLE_PRAGMA_LINKING

//export crap
#ifdef GRAPHVIZKIT_DLL
	#if defined(GRAPHVIZKIT_EXPORTS)
		#define GRAPHVIZKIT_API __declspec(dllexport)
	#else
		#define GRAPHVIZKIT_API __declspec(dllimport)
	#endif
#else
	#define GRAPHVIZKIT_API
#endif //GRAPHVIZKIT_DLL



#include "vcf/GraphicsKit/GraphicsKit.h"




namespace VCF {



	
enum {
	FORMAT_BMP = 1
};


	class GRAPHVIZKIT_API GraphvizKit {
	public:

		static void init( int argc, char** argv );
		static void terminate();

		static GVC_t* getContext() {
			return GraphvizKit::gvCtx;
		}

		static void renderGraph( Agraph_t* g, GraphicsContext* ctx );
	private:
		static GVC_t* gvCtx;
		static GraphicsContext* currentCtx;



		static void beginJob(GVJ_t *job);
		static void endJob(GVJ_t *job);
		static void beginPage(GVJ_t *job);
		static void endPage(GVJ_t *job);
		static void beginAnchor(GVJ_t *job, char *url, char *tooltip, char *target);
		static void textpara(GVJ_t *job, pointf p, textpara_t *para);
		static void path(GVJ_t *job, int filled);
		static void ellipse(GVJ_t *job, pointf *A, int filled);
		static void polygon(GVJ_t *job, pointf *A, int n, int filled);
		static void bezier(GVJ_t *job, pointf *A, int n, int arrow_at_start, int arrow_at_end, int filled);
		static void polyline(GVJ_t *job, pointf *A, int n);

		static boolean install(GVC_t* gvc, api_t api, char* typestr, int quality, 
								char* packagename, char *path, gvplugin_installed_t* typeptr);

	};



	typedef SmartPtr<Agraph_t>::Shared AgraphPtr;

	class GRAPHVIZKIT_API AGraph {
	public:

		AGraph() {
		}

		AGraph( Agraph_t* g ):graph_(g,&AGraph::freeGraph) {}

		AGraph(const AGraph& rhs){
			graph_ = rhs.graph_;
		}

		

		AGraph& operator=(const AGraph& rhs) {
			graph_ = rhs.graph_;
			return *this;
		}		

		void layout();

		void render( GraphicsContext* ctx );		
	

		void load( const String& graph );

		void loadFromFile( const String& filename );

		Agraph_t* get() {
			return graph_.get();
		}    

		bool null() const {
			return graph_.get() == NULL ? true : false;
		}

		Size getBoundsSize() const;
		Rect getBoundingBox() const;
	protected:
		AgraphPtr graph_;

		static void freeGraph( Agraph_t* g );

	private:
		
	};





};


#endif //_VCF_GRAPHVIZKIT_H__
