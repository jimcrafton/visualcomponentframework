##ls -1 *.cpp | egrep -v 'Win32|OSX|DrawToolkit.cpp|AlphaGamma.cpp|ArtStroke.cpp|MicroTiles.cpp|PixelBuffer.cpp|RenderPaths.cpp' | sort -u > GraphicsKit.mak

SOURCES = \
AbstractImage.cpp \
BasicFill.cpp \
BasicStroke.cpp \
BezierCurve.cpp \
Color.cpp \
Font.cpp \
GlyphCollection.cpp \
GraphicsContext.cpp \
GraphicsKit.cpp \
GraphicsResourceBundle.cpp \
GraphicsToolKit.cpp \
GTKContext.cpp \
GTKFont.cpp \
GTKGraphicsToolkit.cpp \
GTKImage.cpp \
ImageEvent.cpp \
Matrix2D.cpp \
Point.cpp \
PrintSession.cpp \
Rect.cpp
