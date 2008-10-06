//D3DTest.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
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

using namespace VCF;




struct PANELVERTEX
{
    FLOAT x, y, z;
    DWORD color;
    FLOAT u, v;
};

#define D3DFVF_PANELVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)








class D3DTestWindow : public Window {
public:
	IDirect3DDevice9Ptr device;
	IDirect3D9Ptr d3d;
	IDirect3DSurface9Ptr surf;
	IDirect3DTexture9Ptr tex;
	IDirect3DVertexBuffer9Ptr vertBuf;
	ID3DXEffectPtr ppEffect;
	

	D3DXIMAGE_INFO imageInfo;

	bool initialized;

	D3DTestWindow():initialized(false) {
		setCaption( "D3DTest" );
	}

	virtual ~D3DTestWindow(){};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint(ctx);
	}

	virtual void sizeChange( ControlEvent* event ) {
		if ( initialized ) {			
			
			Rect r = getClientBounds();
			
			D3DXMATRIX Ortho2D;	
			D3DXMATRIX Identity;
			
			D3DXMatrixOrthoLH(&Ortho2D, r.getWidth(), r.getHeight(), 
				0.0f, 1.0f);
			
			
			D3DXMatrixIdentity(&Identity);
			
			device->SetTransform(D3DTS_PROJECTION, &Ortho2D);
			device->SetTransform(D3DTS_WORLD, &Identity);
			device->SetTransform(D3DTS_VIEW, &Identity);
		}
	}

	void update() {
		if ( initialized ) {			
		
			Color c = *getColor();
			c.setAlpha(1.0);

			device->Clear( 0, //number of rectangles to clear, 0 for all
								NULL, //rects to be cleared, NULL for entire buffer
								D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, //the buffers to clear
								c.getRGBPack8(Color::cpsARGB),//D3DCOLOR_ARGB(255,0,0,0),//D3DCOLOR_ARGB(255,155,0,155), //the Color to fill the buffer with
								1.0f, //depth for the z-buffer to clear
								0 //stencil buffer clear
								);

			device->BeginScene();

			device->SetFVF(D3DFVF_PANELVERTEX);

			device->SetTexture(0, tex.in());

			device->SetStreamSource(0, vertBuf.in(), 0, sizeof(PANELVERTEX));
			device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

			IDirect3DSurface9Ptr backbuffer;
			device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO, backbuffer.out());


			//ppEffect->SetTexture( PP.m_hTexScene[i], g_pSceneSave[i] );
			//mainWindow->ppEffect
			ppEffect->SetTechnique( "PostProcess" );
			UINT cPasses, p;
			ppEffect->Begin( &cPasses, 0 );
			for( p = 0; p < cPasses; ++p )
			{
				//device->SetRenderTarget( 0, backbuffer.in() );				

				//ppEffect->BeginPass( p );
				//device->SetStreamSource( 0, vertBuf.in(), 0, sizeof( PANELVERTEX ) );
				//device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
				//ppEffect->EndPass();
			}


			

			RECT r = {0};
			r.right = imageInfo.Width;
			r.bottom = imageInfo.Height;


			//device->StretchRect(surf.in(), NULL, backbuffer.in(), &r,  D3DTEXF_NONE);
			POINT pt = {0};
			//HRESULT hr = device->UpdateSurface(surf.in(), &r, backbuffer.in(), &pt);



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

		mainWindow->d3d = Direct3DCreate9(D3D_SDK_VERSION);


		D3DPRESENT_PARAMETERS params = {0};
		params.Windowed = TRUE; //Windowed or Fullscreen
		params.SwapEffect = D3DSWAPEFFECT_COPY; //discards the previous frames
		params.BackBufferFormat = D3DFMT_A8R8G8B8; //The display format
		params.BackBufferCount = 1; //Number of back buffers
		params.BackBufferHeight = 500; //height of the backbuffer
		params.BackBufferWidth = 500; //width of the backbuffer
		params.hDeviceWindow = (HWND)mainWindow->getPeer()->getHandleID(); //handle to our window
		params.AutoDepthStencilFormat = D3DFMT_D16; //The stencil format
		params.EnableAutoDepthStencil = TRUE;
		params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		

		HRESULT res = mainWindow->d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL,
							D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, mainWindow->device.out() );




		Rect r = mainWindow->getClientBounds();

		D3DXMATRIX Ortho2D;	
		D3DXMATRIX Identity;
		
		D3DXMatrixOrthoLH(&Ortho2D, r.getWidth(), r.getHeight(), 
							0.0f, 1.0f);

		D3DXMatrixIdentity(&Identity);
		
		mainWindow->device->SetTransform(D3DTS_PROJECTION, &Ortho2D);
		mainWindow->device->SetTransform(D3DTS_WORLD, &Identity);
		mainWindow->device->SetTransform(D3DTS_VIEW, &Identity);



		String textureFile = "pic2.jpg";

	
		// Get the width and height of the image
		
		res = D3DXGetImageInfoFromFileW(textureFile.c_str(), &mainWindow->imageInfo);



		res = mainWindow->device->CreateOffscreenPlainSurface( mainWindow->imageInfo.Width, //surface width
									 mainWindow->imageInfo.Height, //surface height
									 D3DFMT_A8R8G8B8, //surface format, D3DFMT_A8R8G8B8 is a 32 bit format with      8 alpha bits
									 D3DPOOL_DEFAULT, //create it in the default memory pool
									 mainWindow->surf.out(), //the pointer to our surface
									 NULL
									 );



		res = D3DXLoadSurfaceFromFileW(mainWindow->surf.in(), //the surface we just created
										 NULL, //palette entry, NULL for non 256 color formats
										 NULL, //dest rect, NULL for the whole surface
										 textureFile.c_str(), // the file we wish to load
										 NULL, // Source Rect, NULL for the whole file
										 D3DX_DEFAULT, //Filter
										 0, // Color key, color that should be used as transparent.
										 NULL // pointer to a D3DXIMAGE_INFO structure, for holding info about the      image.
										 );



		int mipLevels = 1;
		DWORD usage = D3DUSAGE_RENDERTARGET;
		D3DFORMAT fmt = D3DFMT_A8R8G8B8;
		D3DPOOL pool = D3DPOOL_DEFAULT;

		D3DXCreateTextureFromFileExW(mainWindow->device.in(), textureFile.c_str(), 0, 0, 0, 0,
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
                            D3DX_DEFAULT , 0, NULL, NULL, mainWindow->tex.out() );



		res = mainWindow->device->CreateVertexBuffer(4 * sizeof(PANELVERTEX), D3DUSAGE_WRITEONLY,
                                 D3DFVF_PANELVERTEX, D3DPOOL_MANAGED, mainWindow->vertBuf.out(), NULL );


		float PanelWidth =  mainWindow->imageInfo.Width;// 250.0f;
		float PanelHeight = mainWindow->imageInfo.Height;//250.0f;


		PANELVERTEX* pVertices = NULL;
		res = mainWindow->vertBuf->Lock(0, 4 * sizeof(PANELVERTEX), (void**)&pVertices, 0);

		Color c = *mainWindow->getColor();
		c.setAlpha(0.990);

		//Set all the colors to white
		pVertices[0].color = pVertices[1].color = 
			pVertices[2].color = pVertices[3].color = c.getRGBPack8(Color::cpsARGB);// 0xffffffff;
		
		//Set positions and texture coordinates
		pVertices[0].x = pVertices[3].x = -PanelWidth / 2.0f;
		pVertices[1].x = pVertices[2].x = PanelWidth / 2.0f;
		
		pVertices[0].y = pVertices[1].y = PanelHeight / 2.0f;
		pVertices[2].y = pVertices[3].y = -PanelHeight / 2.0f;
		
		pVertices[0].z = pVertices[1].z = pVertices[2].z = pVertices[3].z = 1.0f;
		
		pVertices[1].u = pVertices[2].u = 1.0f;
		pVertices[0].u = pVertices[3].u = 0.0f;
		
		pVertices[0].v = pVertices[1].v = 0.0f;
		pVertices[2].v = pVertices[3].v = 1.0f;
		
		res = mainWindow->vertBuf->Unlock();


		res = mainWindow->device->SetRenderState(D3DRS_LIGHTING, FALSE);


		mainWindow->device->SetRenderState(D3DRS_ALPHABLENDENABLE,  TRUE);
		mainWindow->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		mainWindow->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		mainWindow->device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


		
		res = D3DXCreateEffectFromFile( mainWindow->device.in(),
                                       "PP_ColorMonochrome.fx",//"PP_ColorInverse.fx", //"PP_ColorEdgeDetect.fx",//"PP_ColorMonochrome.fx",
                                       NULL,
                                       NULL,
                                       0,
                                       NULL,
                                       mainWindow->ppEffect.out(),
                                       NULL );


		mainWindow->initialized = SUCCEEDED(res) ? true : false;
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<D3DTestApplication>(argc,argv);
}


