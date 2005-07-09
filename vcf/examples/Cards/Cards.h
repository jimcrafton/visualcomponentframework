#ifndef CARDS_H
#define CARDS_H

#ifdef __cplusplus
extern "C"  {
#endif
/*
Static linking definitions
*/
BOOL WINAPI cdtInit(int *pdxCard, int *pdyCard);
void WINAPI cdtTerm(void);
BOOL WINAPI cdtDraw (HDC hdc, int x, int y, int cd, int md, DWORD rgbBgnd);
BOOL WINAPI cdtDrawExt(HDC hdc, int x, int y, int dx, int dy,  int cd, int md, DWORD rgbBgnd);
BOOL WINAPI cdtAnimate(HDC hdc, int cd, int x, int y, int ispr);

#ifdef __cplusplus
}
#endif

/*
Dynamic linking definitions
*/
typedef BOOL (WINAPI *dcdtInit   )(int*,int*);
typedef void (WINAPI *dcdtTerm   )(void);
typedef BOOL (WINAPI *dcdtDraw   )(HDC, int, int, int, int, DWORD);
typedef BOOL (WINAPI *dcdtDrawExt)(HDC, int, int, int, int,  int, int, DWORD);
typedef BOOL (WINAPI *dcdtAnimate)(HDC, int, int, int, int);

#endif //CARDS_H
 