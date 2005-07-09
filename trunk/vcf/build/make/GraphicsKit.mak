##ls -1 *.cpp | egrep -v 'Win32|OSX|DrawToolkit.cpp|AlphaGamma.cpp|ArtStroke.cpp|MicroTiles.cpp|PixelBuffer.cpp|RenderPaths.cpp' | sort -u > GraphicsKit.mak

SOURCES = \
GraphicsKit.cpp \
GraphicsToolKit.cpp \
AbstractImage.cpp \
BasicFill.cpp \
BasicStroke.cpp \
BezierCurve.cpp \
Color.cpp \
Font.cpp \
GlyphCollection.cpp \
GraphicsContext.cpp \
GraphicsResourceBundle.cpp \
ImageEvent.cpp \
Matrix2D.cpp \
Point.cpp \
PrintSession.cpp \
Rect.cpp \
GTKContext.cpp \
GTKFont.cpp \
GTKGraphicsToolkit.cpp \
GTKImage.cpp \
GTKPrintSession.cpp \
GTKGraphicsResourceBundle.cpp

