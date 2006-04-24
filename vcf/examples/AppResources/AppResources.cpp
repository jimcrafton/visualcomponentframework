//AppResources.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


class AppResourcesWindow : public Window {
public:
	AppResourcesWindow() {
		setCaption( "AppResources" );		
		background_ = NULL;

		/**
		Get the application's resource bundle
		*/
		GraphicsResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();

		/*
		Extract an image from the resource bundle
		*/
		background_ = resBundle->getImage( "brushed-metal.bmp" );

		/**
		Extract text as raw binary data
		*/
		Resource* textRes = resBundle->getResource( "WhatIsVCF.txt" );
		if ( NULL != textRes ) {
			text_.assign( (const char*)textRes->getData(), textRes->getDataSize() );
			textRes->free();
		}
	}

	virtual ~AppResourcesWindow(){
		delete background_;
	};

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );

		if ( NULL != background_ ) {
			ulong32 w = background_->getWidth();
			ulong32 h = background_->getHeight();
			Rect imgRect(0,0,w,h);
			int colCount = getWidth()/w + 1;

			int rowCount = getHeight()/h + 1;
			for ( int row=0;row<rowCount;row ++ ) {
				for (int col=0;col<colCount;col++ ) {
					ctx->drawImage( imgRect.getTopLeft(), background_ );

					imgRect.offset( w, 0 );
				}

				imgRect.offset( -imgRect.left_, h );
			}
		}

		
		if ( !text_.empty() ) {
			Rect textRect  = getClientBounds();

			textRect.inflate( -20, -20 );

			DrawUIState state;

			state.setActive( isActive() );
			state.setEnabled( isEnabled() );
			state.setFocused( isFocused() );

			ctx->drawThemeEdge( &textRect, state, GraphicsContext::etAllSides, GraphicsContext::etEtched );

			textRect.inflate( -20, -20 );

			ctx->setClippingRect( &textRect );
			ctx->textBoundedBy( &textRect, text_, true );
		}
		
	}

	String text_;
	Image* background_;
};




class AppResourcesApplication : public Application {
public:

	AppResourcesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new AppResourcesWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new AppResourcesApplication( argc, argv );

	Application::main();
	
	return 0;
}


