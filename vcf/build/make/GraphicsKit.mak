##ls -1 *.cpp | egrep -v 'Win32|OSX|DrawToolkit.cpp|AlphaGamma.cpp|ArtStroke.cpp|MicroTiles.cpp|PixelBuffer.cpp|RenderPaths.cpp' | sort -u > GraphicsKit.mak

SOURCES = \
AbstractImage.cpp \
BasicFill.cpp \
BasicStroke.cpp \
BezierCurve.cpp \
Color.cpp \
Font.cpp \
GTKContext.cpp \
GTKFont.cpp \
GTKGraphicsToolkit.cpp \
GTKImage.cpp \
GlyphCollection.cpp \
GraphicsContext.cpp \
GraphicsKit.cpp \
GraphicsToolKit.cpp \
ImageEvent.cpp \
Matrix2D.cpp \
MgcBezierCurve2.cpp \
MgcCurve2.cpp \
MgcIntegrate.cpp \
MgcMath.cpp \
MgcSingleCurve2.cpp \
MgcVector2.cpp \
Point.cpp \
Rect.cpp \
Vector2D.cpp

