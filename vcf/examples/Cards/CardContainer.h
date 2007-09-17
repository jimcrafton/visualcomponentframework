#ifndef _VCF_CARDCONTAINER_H__
#define _VCF_CARDCONTAINER_H__
//CardContainer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


enum CardDrawMode {
  FaceUp = 0,       /* Draw card face up, card to draw specified by cd */
  FaceDown,         /* Draw card face down, back specified by cd (cdFaceDownFirst..cdFaceDownLast) */
  Hilite,           /* Same as FaceUp except drawn with NOTSRCCOPY mode */
  Ghost,            /* Draw a ghost card -- for ace piles */
  Remove,           /* draw background specified by rgbBgnd */
  InvisibleGhost,   /* Draw a ghost card transparent*/
  DeckX,            /* Draw X */
  DeckO             /* Draw O */
};

enum CardRank {
  Ace = 0,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Max,
  Nil,
  First = Ace
};

enum CardSuite {
  Club = 0,
  Diamond,
  Heart,
  Spade,
  SMax,
  SFirst = Club
};

enum CardFaceDown {
  FaceDown1 = 54,
  FaceDown2,
  FaceDown3,
  FaceDown4,
  FaceDown5,
  FaceDown6,
  FaceDown7,
  FaceDown8,
  FaceDown9,
  FaceDown10,
  FaceDown11,
  FaceDown12,
  FaceDownFirst = FaceDown1,
  FaceDownLast = FaceDown12
};

inline int getCardValue (const CardRank cRank, const CardSuite cSuite) {
  return (((cRank) << 2)| (cSuite));
}

inline CardRank getCardRank(const int cardValue) {
  return static_cast<CardRank>((cardValue) >> 2);
}

inline CardSuite getCardSuite(const int cardValue) {
  return static_cast<CardSuite>((cardValue) & 0x03);
}

/*
  We are creating lightweight control since there is no
  need for full control.
  Control should be transparent because of possible deck placement.
*/
class CardControl : public VCF::CustomControl {
public:
  CardControl(): VCF::CustomControl(false) {
    doCtrlInit();
    setTransparent(true);
  }
  CardControl(const int cardValue, const int deckValue = FaceDownFirst): VCF::CustomControl(false) {
    doCtrlInit(cardValue, deckValue);
    setTransparent(true);
  }
  void SetCard(const int cardValue) {
    myCardItem = cardValue;
    repaint();
  }
  void SetDeck(const CardFaceDown deckValue) {
    myDeckItem = deckValue;
    if (myDrawMode == FaceDown)
        repaint();
  }

  const int GetCard(void) {
    return myCardItem;
  }
  void SetFaceUp(void) {
    SetDrawMode(FaceUp);
  }
  void SetFaceDown(void) {
    SetDrawMode(FaceDown);
  }
  void SetEmpty() {
    SetDrawMode(Remove);
  }
  void SetGhost() {
    SetDrawMode(InvisibleGhost);
  }
  void SetDrawMode(const CardDrawMode drawMode) {
    myDrawMode = drawMode;
    repaint();
  }

  virtual void paint( VCF::GraphicsContext* ctx ) {
     CustomControl::paint(ctx);
     dnc.cdtDraw( reinterpret_cast<HDC>(ctx->getPeer()->getContextID()),
                  0, 0,
                  (myDrawMode == FaceDown) ? myDeckItem : myCardItem,
                  myDrawMode,
                  getColor()->getColorRef32() );
  }
private:
  void doCtrlInit(const int cardValue = Defaultcard, const int deck = FaceDownFirst) {
    setWidth(dnc.getWidth());
    setHeight(dnc.getHeight());
    myCardItem = cardValue;
    myDrawMode = FaceUp;
    myDeckItem = deck;
  }
  int myCardItem;
  int myDeckItem;
  CardDrawMode myDrawMode;
  static DynoCardLoader dnc;
  static const int Defaultcard; // = 12;
};

DynoCardLoader CardControl::dnc;



#endif //_VCF_CARDCONTAINER_H__

/**
$Id$
*/
