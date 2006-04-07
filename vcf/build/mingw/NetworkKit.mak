##ls -1 *.cpp | egrep -v 'Win32' > NetworkKit.mak

SOURCES = \
DatagramSocket.cpp \
NetToolkit.cpp \
ServerSocketEvent.cpp \
Socket.cpp \
SocketEvent.cpp \
SocketListeningLoop.cpp \
URL.cpp
