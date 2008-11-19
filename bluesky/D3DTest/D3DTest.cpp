//D3DTest.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Panel.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9tex.h>


#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )



#include "thirdparty/win32/comet/threading.h"
#include "thirdparty/win32/comet/uuid.h"
#include "thirdparty/win32/comet/bstr.h"
#include "thirdparty/win32/comet/safearray.h"
#include "vcf/ApplicationKit/Win32HResult.h"


#define COM_PTR(ifc) \
namespace comet { \
template<> struct comtype<ifc> { \
	static const IID& uuid() { \
        static const IID iid = IID_##ifc; \
        return iid; \
	} \
    typedef nil base;\
};\
};\
typedef comet::com_ptr<ifc> ifc##Ptr;\
\



COM_PTR(IDirect3D9)
COM_PTR(IDirect3DDevice9)
COM_PTR(IDirect3DSurface9)
COM_PTR(IDirect3DTexture9)
COM_PTR(IDirect3DVertexBuffer9)
COM_PTR(ID3DXEffect)





struct PANELVERTEX
{
    FLOAT x, y, z;
	float rhw;
    DWORD color;
    FLOAT u, v;
};

#define D3DFVF_PANELVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

namespace VCF {


class StackCallback {
public:
	StackCallback():callback_(NULL){}

	~StackCallback(){
		if ( NULL != callback_ ) {
			callback_->free();
		}
	}

	operator CallBack* () {
		return callback_;
	}

	CallBack *operator->() {
		return callback_;
	}

	StackCallback& operator=( CallBack* rhs ) {
		callback_ = rhs;
		return *this;
	}
private:
	CallBack* callback_;
};

class ImageKit {
public:
	static void init( int argc, char** argv );
	static void terminate();

	static void attachControl( Control* c );
	static void detachControl( Control* c );
protected:
	static ImageKit* instance;
	IDirect3D9Ptr d3d_;
	typedef std::map<Control*,IDirect3DDevice9Ptr> DeviceMap;
	DeviceMap devices_;
	
	StackCallback onResize_;
	static void controlResized(Event* e);
private:
	ImageKit();
	~ImageKit();
};

class IKImage : public Object {
public:
	IKImage();
	IKImage( Image* image );
	IKImage( const uchar* data, const size_t& size, const MIMEType& type  );
	IKImage( const uchar* data, const size_t& size );
	IKImage( const uchar* data, const Size& dimensions );
	IKImage( const String& fileName );

	void initFromImage( Image* image );
	void initFromData( const uchar* data, const size_t& size, const MIMEType& type );
	void initFromData( const uchar* data, const size_t& size );
	void initFromBits( const uchar* data, const Size& dimensions );
	void initFromFile( const String& fileName );
protected:
	uint32 imageHandle_;
};



ImageKit* ImageKit::instance = NULL;

ImageKit::ImageKit()
{
	d3d_ = Direct3DCreate9(D3D_SDK_VERSION);
}

ImageKit::~ImageKit()
{
	d3d_ = NULL;
}

void ImageKit::init( int argc, char** argv )
{
	ImageKit::instance = new ImageKit();
}

void ImageKit::terminate()
{
	delete ImageKit::instance;
}

void ImageKit::controlResized(Event* e)
{
	Control* c = (Control*)e->getSource();

	DeviceMap::iterator found = ImageKit::instance->devices_.find( c );
	if ( found != ImageKit::instance->devices_.end() ) {

	}

}

void ImageKit::attachControl( Control* c )
{
	DeviceMap::iterator found = ImageKit::instance->devices_.find( c );
	if ( found == ImageKit::instance->devices_.end() ) {
		IDirect3DDevice9Ptr device;

		Rect r = c->getClientBounds();

		D3DPRESENT_PARAMETERS params = {0};

		params.Windowed = TRUE; //Windowed or Fullscreen
		params.SwapEffect = D3DSWAPEFFECT_COPY; //discards the previous frames
		params.BackBufferFormat = D3DFMT_A8R8G8B8; //The display format
		params.BackBufferCount = 1; //Number of back buffers
		params.BackBufferHeight = r.getHeight(); //height of the backbuffer
		params.BackBufferWidth = r.getWidth(); //width of the backbuffer
		params.hDeviceWindow = (HWND)c->getPeer()->getHandleID(); //handle to our window
		params.AutoDepthStencilFormat = D3DFMT_D16; //The stencil format
		params.EnableAutoDepthStencil = TRUE;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		

		HRESULT res = 
			ImageKit::instance->d3d_->CreateDevice( D3DADAPTER_DEFAULT, 
													D3DDEVTYPE_HAL, 
													NULL,
													D3DCREATE_HARDWARE_VERTEXPROCESSING, 
													&params, 
													device.out() );


		res = device->SetRenderState(D3DRS_LIGHTING, FALSE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE,  TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


		ImageKit::instance->onResize_ = new Procedure1<Event*>(ImageKit::controlResized);
		c->ControlSized += ImageKit::instance->onResize_;

		ImageKit::instance->devices_[c] = device;
	}
}

void ImageKit::detachControl( Control* c )
{
	DeviceMap::iterator found = ImageKit::instance->devices_.find( c );
	if ( found != ImageKit::instance->devices_.end() ) {
		IDirect3DDevice9Ptr device = found->second;
		ImageKit::instance->devices_.erase( found );
		device = NULL;
	}
}




IKImage::IKImage()
{

}

IKImage::IKImage( Image* image )
{

}

IKImage::IKImage( const uchar* data, const size_t& size, const MIMEType& type  )
{

}

IKImage::IKImage( const uchar* data, const size_t& size )
{

}

IKImage::IKImage( const uchar* data, const Size& dimensions )
{

}

IKImage::IKImage( const String& fileName )
{

}

void IKImage::initFromImage( Image* image )
{

}

void IKImage::initFromData( const uchar* data, const size_t& size, const MIMEType& type )
{

}

void IKImage::initFromData( const uchar* data, const size_t& size )
{

}

void IKImage::initFromBits( const uchar* data, const Size& dimensions )
{

}

void IKImage::initFromFile( const String& fileName )
{

}



};



using namespace VCF;



class D3DTestWindow : public Window {
public:
	IDirect3DDevice9Ptr device;
	IDirect3D9Ptr d3d;
	IDirect3DSurface9Ptr renderSurf;
	IDirect3DTexture9Ptr tex;
	IDirect3DVertexBuffer9Ptr vertBuf;
	ID3DXEffectPtr ppEffect;

	IDirect3DTexture9Ptr renderTex;
	IDirect3DVertexBuffer9Ptr renderVertBuf;
	
	D3DPRESENT_PARAMETERS params;

	D3DXIMAGE_INFO imageInfo;


	String textureFile;

	bool initialized;

	D3DTestWindow():initialized(false) {
		setCaption( "D3DTest" );

		setDoubleBuffered(false);
		
		textureFile = "logo.png";//"Lotus2mq.jpg";
	}

	virtual ~D3DTestWindow(){};

	virtual void paint( GraphicsContext* ctx ) {
		//Window::paint(ctx);
		update();
	}


	void initD3D() {
		d3d = Direct3DCreate9(D3D_SDK_VERSION);

		Rect r = getClientBounds();


		memset( &params, 0, sizeof(params) );

		params.Windowed = TRUE; //Windowed or Fullscreen
		params.SwapEffect = D3DSWAPEFFECT_COPY; //discards the previous frames
		params.BackBufferFormat = D3DFMT_A8R8G8B8; //The display format
		params.BackBufferCount = 1; //Number of back buffers
		params.BackBufferHeight = r.getHeight(); //height of the backbuffer
		params.BackBufferWidth = r.getWidth(); //width of the backbuffer
		params.hDeviceWindow = (HWND)getPeer()->getHandleID(); //handle to our window
		params.AutoDepthStencilFormat = D3DFMT_D16; //The stencil format
		params.EnableAutoDepthStencil = TRUE;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		

		HRESULT res = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL,
							D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, device.out() );




		/*

		D3DXMATRIX Ortho2D;	
		D3DXMATRIX Identity;
		
		D3DXMatrixOrthoLH(&Ortho2D, r.getWidth(), r.getHeight(), 
							0.0f, 1.0f);

		D3DXMatrixIdentity(&Identity);
		
		device->SetTransform(D3DTS_PROJECTION, &Ortho2D);
		device->SetTransform(D3DTS_WORLD, &Identity);
		device->SetTransform(D3DTS_VIEW, &Identity);
*/




		// Get the width and height of the image
		res = D3DXGetImageInfoFromFileW(textureFile.c_str(), &imageInfo);


		int mipLevels = 1;
		DWORD usage = D3DUSAGE_RENDERTARGET;
		D3DFORMAT fmt = D3DFMT_A8R8G8B8;
		D3DPOOL pool = D3DPOOL_DEFAULT;

		res = D3DXCreateTextureFromFileExW(device.in(), textureFile.c_str(), 0, 0, 0, 0,
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR,
                            D3DX_FILTER_LINEAR , 0, NULL, NULL, tex.out() );



		res = device->CreateVertexBuffer(4 * sizeof(PANELVERTEX), D3DUSAGE_WRITEONLY,
                                 D3DFVF_PANELVERTEX, D3DPOOL_MANAGED, vertBuf.out(), NULL );


		float PanelWidth =  imageInfo.Width;// 250.0f;
		float PanelHeight = imageInfo.Height;//250.0f;


		PANELVERTEX* pVertices = NULL;
		res = vertBuf->Lock(0, 4 * sizeof(PANELVERTEX), (void**)&pVertices, 0);

		Color c = *getColor();
		c.setAlpha(1);
		pVertices[0].color = pVertices[1].color = 
			pVertices[2].color = pVertices[3].color = c.getRGBPack8(Color::cpsARGB);// 0xffffffff;
		
		pVertices[0].rhw = pVertices[1].rhw = 
				pVertices[2].rhw = pVertices[3].rhw = 1.0f;

		pVertices[0].z = pVertices[1].z = 
				pVertices[2].z = pVertices[3].z = 0.0f;

		pVertices[0].x = 0.0f - 0.5f;
		pVertices[0].y = 0.0f - 0.5f;
		pVertices[0].u = 0.0f;
		pVertices[0].v = 0.0f;

		pVertices[1].x = PanelWidth - 0.5f;
		pVertices[1].y = 0.0f - 0.5f;
		pVertices[1].u = 1.0f;
		pVertices[1].v = 0.0f;

		pVertices[2].x = PanelWidth - 0.5f;
		pVertices[2].y = PanelHeight - 0.5f;
		pVertices[2].u = 1.0f;
		pVertices[2].v = 1.0f;

		pVertices[3].x = 0.0f - 0.5f;
		pVertices[3].y = PanelHeight - 0.5f;
		pVertices[3].u = 0.0f;
		pVertices[3].v = 1.0f;

		res = vertBuf->Unlock();


		res = device->SetRenderState(D3DRS_LIGHTING, FALSE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE,  TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


		res = D3DXCreateEffectFromFile( device.in(),
                                       "PP_ColorMonochrome.fx",//"PP_ColorInverse.fx", //"PP_ColorEdgeDetect.fx",//"PP_ColorMonochrome.fx",
                                       NULL,
                                       NULL,
                                       0,
                                       NULL,
                                       ppEffect.out(),
                                       NULL );


		initialized = SUCCEEDED(res) ? true : false;
	}

	void resetD3D( double w, double h ) {

		if ( !initialized ) {
			return;
		}

		renderTex = NULL;
		renderVertBuf = NULL;
		renderSurf = NULL;

		ppEffect = NULL;

		//tex = NULL;

		vertBuf = NULL;
		



		params.BackBufferHeight = h; //height of the backbuffer
		params.BackBufferWidth = w; //width of the backbuffer
		device->Reset( &params );


		device->SetRenderState(D3DRS_LIGHTING, FALSE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE,  TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		D3DXCreateEffectFromFile( device.in(),
                                       "PP_ColorMonochrome.fx",//"PP_ColorInverse.fx", //"PP_ColorEdgeDetect.fx",//"PP_ColorMonochrome.fx",
                                       NULL,
                                       NULL,
                                       0,
                                       NULL,
                                       ppEffect.out(),
                                       NULL );

		PANELVERTEX* pVertices = NULL;
		Color c = *getColor();
		c.setAlpha(1.0);



		HRESULT res = 0;

		res = D3DXGetImageInfoFromFileW(textureFile.c_str(), &imageInfo);


		int mipLevels = 1;
		DWORD usage = D3DUSAGE_RENDERTARGET;
		D3DFORMAT fmt = D3DFMT_A8R8G8B8;
		D3DPOOL pool = D3DPOOL_DEFAULT;
/*
		D3DXCreateTextureFromFileExW(device.in(), textureFile.c_str(), 0, 0, 0, 0,
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
                            D3DX_DEFAULT , 0, NULL, NULL, tex.out() );

*/

		res = device->CreateVertexBuffer(4 * sizeof(PANELVERTEX), D3DUSAGE_WRITEONLY,
                                 D3DFVF_PANELVERTEX, D3DPOOL_MANAGED, vertBuf.out(), NULL );


		float PanelWidth =  imageInfo.Width;// 250.0f;
		float PanelHeight = imageInfo.Height;//250.0f;


		
		res = vertBuf->Lock(0, 4 * sizeof(PANELVERTEX), (void**)&pVertices, 0);

		
		pVertices[0].color = pVertices[1].color = 
			pVertices[2].color = pVertices[3].color = c.getRGBPack8(Color::cpsARGB);// 0xffffffff;
		
		pVertices[0].rhw = pVertices[1].rhw = 
				pVertices[2].rhw = pVertices[3].rhw = 1.0f;

		pVertices[0].z = pVertices[1].z = 
				pVertices[2].z = pVertices[3].z = 0.0f;

		pVertices[0].x = 0.0f - 0.5f;
		pVertices[0].y = 0.0f - 0.5f;
		pVertices[0].u = 0.0f;
		pVertices[0].v = 0.0f;

		pVertices[1].x = PanelWidth - 0.5f;
		pVertices[1].y = 0.0f - 0.5f;
		pVertices[1].u = 1.0f;
		pVertices[1].v = 0.0f;

		pVertices[2].x = PanelWidth - 0.5f;
		pVertices[2].y = PanelHeight - 0.5f;
		pVertices[2].u = 1.0f;
		pVertices[2].v = 1.0f;

		pVertices[3].x = 0.0f - 0.5f;
		pVertices[3].y = PanelHeight - 0.5f;
		pVertices[3].u = 0.0f;
		pVertices[3].v = 1.0f;

		res = vertBuf->Unlock();

		device->CreateTexture(w, h,
                                 1,
                                 D3DUSAGE_RENDERTARGET,
                                 D3DFMT_A8R8G8B8,
                                 D3DPOOL_DEFAULT,
                                 renderTex.out(),
                                 NULL);


		renderTex->GetSurfaceLevel( 0, renderSurf.out() );


		device->CreateVertexBuffer(4 * sizeof(PANELVERTEX), D3DUSAGE_WRITEONLY,
                             D3DFVF_PANELVERTEX, D3DPOOL_MANAGED, renderVertBuf.out(), NULL );




		pVertices = NULL;
		renderVertBuf->Lock(0, 4 * sizeof(PANELVERTEX), (void**)&pVertices, 0);
		
		
		
		c = *getColor();
		c.setAlpha(1.0);
		
		//Set all the colors to white
		pVertices[0].color = pVertices[1].color = 
			pVertices[2].color = pVertices[3].color = c.getRGBPack8(Color::cpsARGB);// 0xffffffff;
		
		pVertices[0].rhw = pVertices[1].rhw = 
			pVertices[2].rhw = pVertices[3].rhw = 1.0f;
		//Set positions and texture coordinates
		
		pVertices[0].x = 0.0f - 0.5f;
		pVertices[0].y = 0.0f - 0.5f;
		pVertices[0].u = 0.0f;
		pVertices[0].v = 0.0f;

		pVertices[1].x = w - 0.5f;
		pVertices[1].y = 0.0f - 0.5f;
		pVertices[1].u = 1.0f;
		pVertices[1].v = 0.0f;

		pVertices[2].x = w - 0.5f;
		pVertices[2].y = h - 0.5f;
		pVertices[2].u = 1.0f;
		pVertices[2].v = 1.0f;

		pVertices[3].x = 0.0f - 0.5f;
		pVertices[3].y = h - 0.5f;
		pVertices[3].u = 0.0f;
		pVertices[3].v = 1.0f;
		

		pVertices[0].z = pVertices[1].z = 
			pVertices[2].z = pVertices[3].z = 0.0f;			

		
		renderVertBuf->Unlock();
	}

	virtual void sizeChange( ControlEvent* event ) {
		if ( initialized ) {			
			
			Rect r = getClientBounds();

			resetD3D( r.getWidth(), r.getHeight() );
			update();
		}
	}

	

	void update() {
		if ( initialized ) {	
			
			Color c = *getColor();
			c.setAlpha(1.0);
			

			IDirect3DSurface9Ptr backbuffer;
			HRESULT res = device->GetRenderTarget(0,backbuffer.out());

			res = device->SetRenderTarget( 0, renderSurf.in() );

			device->Clear( 0, //number of rectangles to clear, 0 for all
								NULL, //rects to be cleared, NULL for entire buffer
								D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, //the buffers to clear
								c.getRGBPack8(Color::cpsARGB),//D3DCOLOR_ARGB(255,0,0,0),//D3DCOLOR_ARGB(255,155,0,155), //the Color to fill the buffer with
								1.0f, //depth for the z-buffer to clear
								0 //stencil buffer clear
								);

			device->BeginScene();

			res = device->SetFVF(D3DFVF_PANELVERTEX);
			res = device->SetTexture(0, tex.in());
			res = device->SetStreamSource(0, vertBuf.in(), 0, sizeof(PANELVERTEX));
			res = device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);


			res = device->EndScene();


			
			Rect r = getClientBounds();

			D3DXMATRIX Ortho2D;	
			D3DXMATRIX Identity;
			
			D3DXMatrixOrthoLH(&Ortho2D, r.getWidth(), r.getHeight(), 
				0.0f, 1.0f);
			
			
			D3DXMatrixIdentity(&Identity);
			
			//device->SetTransform(D3DTS_PROJECTION, &Ortho2D);
			//device->SetTransform(D3DTS_WORLD, &Identity);
			//device->SetTransform(D3DTS_VIEW, &Identity);


			device->SetRenderTarget( 0, backbuffer.in() );
			device->Clear( 0, //number of rectangles to clear, 0 for all
								NULL, //rects to be cleared, NULL for entire buffer
								D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, //the buffers to clear
								D3DCOLOR_ARGB(255,255,0,0),//c.getRGBPack8(Color::cpsARGB),//D3DCOLOR_ARGB(255,0,0,0),//D3DCOLOR_ARGB(255,155,0,155), //the Color to fill the buffer with
								1.0f, //depth for the z-buffer to clear
								0 //stencil buffer clear
								);

			device->BeginScene();

			device->SetTexture(0, renderTex.in());


			device->SetStreamSource(0, renderVertBuf.in(), 0, sizeof(PANELVERTEX));
			device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);



			

			ppEffect->SetTechnique( "PostProcess" );

			static float timer = 0.0f;

			float amt = 0.00461f;

			ppEffect->SetFloat("amt",amt);
			ppEffect->SetFloat("timer",timer);

			timer += 0.150f;
/*
			UINT cPasses, p;
			ppEffect->Begin( &cPasses, 0 );
			for( p = 0; p < cPasses; ++p )
			{
				//device->SetRenderTarget( 0, backbuffer.in() );				
				
				ppEffect->BeginPass( p );
	

				//device->SetStreamSource( 0, vertBuf.in(), 0, sizeof( PANELVERTEX ) );
				//device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
				
				ppEffect->EndPass();
			}

*/
			

//			RECT r = {0};
			//r.right = imageInfo.Width;
			//r.bottom = imageInfo.Height;


			//device->StretchRect(renderSurf.in(), NULL, backbuffer.in(), &r,  D3DTEXF_NONE);
			//POINT pt = {0};
			//HRESULT hr = device->UpdateSurface(renderSurf.in(), &r, backbuffer.in(), &pt);



			device->EndScene();

			


			device->Present(NULL, NULL, NULL, NULL );

		}
	}
};


class D3DTestApplication : public Application {
public:

	
	

	D3DTestApplication( int argc, char** argv ) : Application(argc, argv) {

		
	}

	virtual void idleTime() {
		Application::idleTime();

		D3DTestWindow* wnd = (D3DTestWindow*)getMainWindow();
		if ( wnd ) {
			wnd->update();
		}
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		

		

		


		D3DTestWindow* mainWindow = new D3DTestWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );

		mainWindow->show();

		mainWindow->initD3D();
		

		

	
		

		//mainWindow->device->SetVertexShader( NULL );



		
		






		
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<D3DTestApplication>(argc,argv);
}


