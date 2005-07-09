#ifndef CARDCLASS_H
#define CARDCLASS_H

class DynoCardLoader {
public:
  DynoCardLoader(void)
  : libHandle_(NULL),
    cdtInit_(NULL),
    cdtTerm_(NULL),
    cdtDraw_(NULL),
    cdtDrawExt_(NULL),
    cdtAnimate_(NULL),
    cardHeight(0),
    cardWidth(0),
    isInit(false) {
    Init();
  }
  ~DynoCardLoader(void) {
    Term();
  }

  bool cdtDraw (HDC hdc, int x, int y, int cd, int md, DWORD rgbBgnd) {
    return ( cdtDraw_(hdc, x, y, cd, md, rgbBgnd) != 0 );
  }
  bool cdtDrawExt(HDC hdc, int x, int y, int dx, int dy,  int cd, int md, DWORD rgbBgnd) {
    return ( cdtDrawExt_(hdc, x, y, dx, dy, cd, md, rgbBgnd) != 0 );
  }
  bool cdtAnimate(HDC hdc, int cd, int x, int y, int ispr) {
    return ( cdtAnimate_(hdc, cd, x, y, ispr) != 0 );
  }
  int getWidth() {return cardWidth;}
  int getHeight() {return cardHeight;}
private:
  HINSTANCE   libHandle_ ;
  dcdtInit    cdtInit_   ;
  dcdtTerm    cdtTerm_   ;
  dcdtDraw    cdtDraw_   ;
  dcdtDrawExt cdtDrawExt_;
  dcdtAnimate cdtAnimate_;
  int cardHeight;
  int cardWidth;
  bool isInit;

  void Init(void) {
    libHandle_ = ::LoadLibrary("cards.dll");
    if (NULL == libHandle_) {
      libHandle_ = ::LoadLibrary("cards32.dll");
      if (NULL == libHandle_) {
       //error
       return;
      } //end if
    }// end if

    if (NULL != libHandle_) {
      cdtInit_ = reinterpret_cast<dcdtInit>(::GetProcAddress(libHandle_,"cdtInit"));
      cdtTerm_ = reinterpret_cast<dcdtTerm>(::GetProcAddress(libHandle_,"cdtTerm"));
      cdtDraw_ = reinterpret_cast<dcdtDraw>(::GetProcAddress(libHandle_,"cdtDraw"));
      cdtDrawExt_ = reinterpret_cast<dcdtDrawExt>(::GetProcAddress(libHandle_,"cdtDrawExt"));
      cdtAnimate_ = reinterpret_cast<dcdtAnimate>(::GetProcAddress(libHandle_,"cdtAnimate"));
    }

    DoInitCheck();
  }

  void DoInitCheck(void) {
    if (!isInit) {
      isInit = ( cdtInit_(&cardWidth, &cardHeight) != 0 );
    }
  }

  void Term(void) {
    if (NULL != libHandle_) {
      if (isInit) {
         cdtTerm_();
         isInit = false;
      }
      ::FreeLibrary(libHandle_);
      libHandle_ = NULL;
    }
  }
};
#endif //CARDCLASS_H
 