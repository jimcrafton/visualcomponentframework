//Cards.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/TitledBorder.h"
#include "Cards.h"
#include "Cardclass.h"
#include "CardContainer.h"

using namespace VCF;

const int CardControl::Defaultcard = 12;

class CardsWindow : public Window {
public:
	CardsWindow() {
         setCaption( "VCF Cards sample" );
         setColor(Color::getColor("green"));
         setUseColorForBackground( true );
         	
         internalCreateMenu();
         
         internalCreateControls();
		
	}

	virtual ~CardsWindow(){};

        void onMenuExit(Event* e){
                close();
        }

private:
   typedef GenericEventHandler<CardsWindow> MnuHandler;
   CardControl *card1;
   void internalCreateMenu() {
   	
	MenuBar* menuBar = new MenuBar();
	setMenuBar( menuBar );
	addComponent( menuBar );
	
	MenuItem* root = menuBar->getRootMenuItem();
	
	DefaultMenuItem* Game = new DefaultMenuItem( "&Game", root, menuBar );
	
	DefaultMenuItem* gameDeal = new DefaultMenuItem( "&Deal   F2", Game, menuBar );
	
	DefaultMenuItem* menuSep = new DefaultMenuItem( "", Game, menuBar );
	menuSep->setSeparator( true );
	
	DefaultMenuItem* gameUndo = new DefaultMenuItem( "&Undo", Game, menuBar );
	DefaultMenuItem* gameDeck = new DefaultMenuItem( "De&ck...", Game, menuBar );
	DefaultMenuItem* gameOptions = new DefaultMenuItem( "&Options...", Game, menuBar );
	menuSep = new DefaultMenuItem( "", Game, menuBar );
	menuSep->setSeparator( true );
	DefaultMenuItem* gameExit = new DefaultMenuItem( "E&xit", Game, menuBar );
	
	DefaultMenuItem* help = new DefaultMenuItem( "&Help", root, menuBar );
	
	DefaultMenuItem* helpAbout = new DefaultMenuItem( "&About VCF Solitaire", help, menuBar );
	//actions

	Action* gameQuit = new Action();
	addComponent( gameQuit );
	gameQuit->addTarget(gameExit);
	gameQuit->Performed += new MnuHandler(this,&CardsWindow::onMenuExit,"Exit Application");
		
   }
   
   void internalCreateControls () {
      CardControl* cctrl = NULL;
      //Top deck
      int count, icount;
      for (count = 0; count < 3; ++count) {
           cctrl = new CardControl();
           cctrl->setTop(5 + count);
           cctrl->setLeft(11 + (count*2));
           cctrl->SetFaceDown();
           add(cctrl);	     
      }                
      
      int topDistance = 11 + cctrl->getHeight();
      int cardWidth = cctrl->getWidth();
      for (count = 0; count < 7; ++count) {
      	for (icount = 0; icount < (count+1); ++icount) {
   	        cctrl = new CardControl();
   	        cctrl->setTop(topDistance + (3*icount));
   	        cctrl->setLeft((count+1)*11 + count*cardWidth);
   	        if ((icount != count) && (count > 0)) {
   	          cctrl->SetFaceDown();
   	        }
   	        add(cctrl);
   	}
      }                
      
      int startLeft = 3*(11 + cardWidth); 
      for (count = 0; count < 4; ++count) {
           cctrl = new CardControl();
           cctrl->setTop(5);
           cctrl->setLeft(startLeft + (count+1)*11 + count*cardWidth);
           cctrl->SetGhost();
           add(cctrl);	     
      }                
   
   }
};


class CardsApplication : public Application {
public:
  CardsApplication( int argc, char** argv ) : Application(argc, argv) {;}

  virtual bool initRunningApplication(){
          bool result = Application::initRunningApplication();

          Window* mainWindow = new CardsWindow();
          setMainWindow(mainWindow);
          mainWindow->setBounds( 100.0, 100.0, 593, 441 );
          mainWindow->show();

          return result;
  }
};

int main(int argc, char** argv)
{
  try {
    
    Application* app = new CardsApplication( argc, argv );

    Application::main();
  }
  catch( const VCF::BasicException& ) {
    return -1;
  } 
  return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:14  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.3  2005/05/05 14:15:43  marcelloptr
*standard VCF formatting
*
*/


