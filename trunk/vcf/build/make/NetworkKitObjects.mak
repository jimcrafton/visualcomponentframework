###########################################################
#
#
#CVS Log info
#$Log$
#Revision 1.2  2003/02/26 04:30:25  ddiego
#merge of code in the devmain-0-5-9 branch into the current tree.
#most additions are in the area of the current linux port, but the major
#addition to this release is the addition of a Condition class (currently
#still under development) and the change over to using the Delegate class
#exclusively from the older event handler macros.
#
#Revision 1.1.2.2  2003/02/08 17:55:44  ddiego
#modified the makefiles to have cvs Log entries, so we can keepo track of
#whats going on :)
#
#
#
#Object files for the NetworkKit 
#
###########################################################



###########################################################
#Debug files
###########################################################

$(OUTDIR_NK_D)/DatagramSocket.o : $(SRC_NET)/DatagramSocket.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS_D) $(SRC_NET)/DatagramSocket.cpp -o $(OUTDIR_NK_D)/DatagramSocket.o
	
$(OUTDIR_NK_D)/NetToolkit.o : $(SRC_NET)/NetToolkit.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS_D) $(SRC_NET)/NetToolkit.cpp -o $(OUTDIR_NK_D)/NetToolkit.o

$(OUTDIR_NK_D)/ServerSocketEvent.o : $(SRC_NET)/ServerSocketEvent.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS_D) $(SRC_NET)/ServerSocketEvent.cpp -o $(OUTDIR_NK_D)/ServerSocketEvent.o

$(OUTDIR_NK_D)/Socket.o : $(SRC_NET)/Socket.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS_D) $(SRC_NET)/Socket.cpp -o $(OUTDIR_NK_D)/Socket.o

$(OUTDIR_NK_D)/SocketEvent.o : $(SRC_NET)/SocketEvent.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS_D) $(SRC_NET)/SocketEvent.cpp -o $(OUTDIR_NK_D)/SocketEvent.o

$(OUTDIR_NK_D)/SocketListeningLoop.o : $(SRC_NET)/SocketListeningLoop.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS_D) $(SRC_NET)/SocketListeningLoop.cpp -o $(OUTDIR_NK_D)/SocketListeningLoop.o

$(OUTDIR_NK_D)/URL.o  : $(SRC_NET)/URL.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS_D) $(SRC_NET)/URL.cpp -o $(OUTDIR_NK_D)/URL.o
	
	

###########################################################
#Release files
###########################################################

$(OUTDIR_NK)/DatagramSocket.o : $(SRC_NET)/DatagramSocket.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS) $(SRC_NET)/DatagramSocket.cpp -o $(OUTDIR_NK)/DatagramSocket.o
	
$(OUTDIR_NK)/NetToolkit.o : $(SRC_NET)/NetToolkit.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS) $(SRC_NET)/NetToolkit.cpp -o $(OUTDIR_NK)/NetToolkit.o

$(OUTDIR_NK)/ServerSocketEvent.o : $(SRC_NET)/ServerSocketEvent.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS) $(SRC_NET)/ServerSocketEvent.cpp -o $(OUTDIR_NK)/ServerSocketEvent.o

$(OUTDIR_NK)/Socket.o : $(SRC_NET)/Socket.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS) $(SRC_NET)/Socket.cpp -o $(OUTDIR_NK)/Socket.o

$(OUTDIR_NK)/SocketEvent.o : $(SRC_NET)/SocketEvent.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS) $(SRC_NET)/SocketEvent.cpp -o $(OUTDIR_NK)/SocketEvent.o

$(OUTDIR_NK)/SocketListeningLoop.o : $(SRC_NET)/SocketListeningLoop.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS) $(SRC_NET)/SocketListeningLoop.cpp -o $(OUTDIR_NK)/SocketListeningLoop.o

$(OUTDIR_NK)/URL.o  : $(SRC_NET)/URL.cpp $(NETWORKKIT_HDRS)
	$(CXX) $(NK_CXX_FLAGS) $(SRC_NET)/URL.cpp -o $(OUTDIR_NK)/URL.o
	
	
	
	
	