###########################################################
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
#Revision 1.1.2.5  2003/02/18 19:59:55  catwallader
#Added Condition classes. Also added comments to Thread and Mutex class
#headers.
#
#Revision 1.1.2.4  2003/02/12 19:33:44  catwallader
#Added PosixMutex class.
#
#Revision 1.1.2.3  2003/02/08 17:55:44  ddiego
#modified the makefiles to have cvs Log entries, so we can keepo track of
#whats going on :)
#
#
#
#
#Object files for the FoundationKit 
#
###########################################################



###########################################################
#Debug files
###########################################################


$(OUTDIR_FK_D)/BasicException.o : $(SRC_EXCPT)/BasicException.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_EXCPT)/BasicException.cpp -o $(OUTDIR_FK_D)/BasicException.o

$(OUTDIR_FK_D)/BasicInputStream.o : $(SRC_IO)/BasicInputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/BasicInputStream.cpp -o $(OUTDIR_FK_D)/BasicInputStream.o

$(OUTDIR_FK_D)/BasicOutputStream.o : $(SRC_IO)/BasicOutputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/BasicOutputStream.cpp -o $(OUTDIR_FK_D)/BasicOutputStream.o

$(OUTDIR_FK_D)/Class.o : $(SRC_CORE)/Class.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/Class.cpp -o $(OUTDIR_FK_D)/Class.o

$(OUTDIR_FK_D)/ClassRegistry.o : $(SRC_CORE)/ClassRegistry.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/ClassRegistry.cpp -o $(OUTDIR_FK_D)/ClassRegistry.o

$(OUTDIR_FK_D)/Directory.o : $(SRC_IO)/Directory.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/Directory.cpp -o $(OUTDIR_FK_D)/Directory.o

$(OUTDIR_FK_D)/ErrorLog.o : $(SRC_UTILS)/ErrorLog.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/ErrorLog.cpp -o $(OUTDIR_FK_D)/ErrorLog.o

$(OUTDIR_FK_D)/Event.o : $(SRC_EVENT)/Event.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_EVENT)/Event.cpp -o $(OUTDIR_FK_D)/Event.o

$(OUTDIR_FK_D)/EventHandler.o : $(SRC_EVENT)/EventHandler.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_EVENT)/EventHandler.cpp -o $(OUTDIR_FK_D)/EventHandler.o

$(OUTDIR_FK_D)/File.o : $(SRC_IO)/File.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/File.cpp -o $(OUTDIR_FK_D)/File.o

$(OUTDIR_FK_D)/FilePath.o : $(SRC_UTILS)/FilePath.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/FilePath.cpp -o $(OUTDIR_FK_D)/FilePath.o

$(OUTDIR_FK_D)/FileStream.o : $(SRC_IO)/FileStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/FileStream.cpp -o $(OUTDIR_FK_D)/FileStream.o

$(OUTDIR_FK_D)/FileUtils.o : $(SRC_IO)/FileUtils.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/FileUtils.cpp -o $(OUTDIR_FK_D)/FileUtils.o

$(OUTDIR_FK_D)/FoundationKit.o : $(SRC_CORE)/FoundationKit.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/FoundationKit.cpp -o $(OUTDIR_FK_D)/FoundationKit.o

$(OUTDIR_FK_D)/InterfaceClass.o : $(SRC_CORE)/InterfaceClass.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/InterfaceClass.cpp -o $(OUTDIR_FK_D)/InterfaceClass.o

$(OUTDIR_FK_D)/Library.o : $(SRC_UTILS)/Library.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/Library.cpp -o $(OUTDIR_FK_D)/Library.o

$(OUTDIR_FK_D)/Locales.o : $(SRC_CORE)/Locales.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/Locales.cpp -o $(OUTDIR_FK_D)/Locales.o

$(OUTDIR_FK_D)/MemoryStream.o : $(SRC_IO)/MemoryStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/MemoryStream.cpp -o $(OUTDIR_FK_D)/MemoryStream.o

$(OUTDIR_FK_D)/Mutex.o : $(SRC_UTILS)/Mutex.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/Mutex.cpp -o $(OUTDIR_FK_D)/Mutex.o

$(OUTDIR_FK_D)/Condition.o : $(SRC_UTILS)/Condition.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/Condition.cpp -o $(OUTDIR_FK_D)/Condition.o

$(OUTDIR_FK_D)/Object.o : $(SRC_CORE)/Object.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/Object.cpp -o $(OUTDIR_FK_D)/Object.o

$(OUTDIR_FK_D)/ObjectWithEvents.o : $(SRC_CORE)/ObjectWithEvents.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/ObjectWithEvents.cpp -o $(OUTDIR_FK_D)/ObjectWithEvents.o

$(OUTDIR_FK_D)/Parser.o : $(SRC_UTILS)/Parser.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/Parser.cpp -o $(OUTDIR_FK_D)/Parser.o

$(OUTDIR_FK_D)/Point.o : $(SRC_CORE)/Point.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/Point.cpp -o $(OUTDIR_FK_D)/Point.o

$(OUTDIR_FK_D)/PropertyChangeEvent.o : $(SRC_EVENT)/PropertyChangeEvent.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_EVENT)/PropertyChangeEvent.cpp -o $(OUTDIR_FK_D)/PropertyChangeEvent.o

$(OUTDIR_FK_D)/Rect.o : $(SRC_CORE)/Rect.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/Rect.cpp -o $(OUTDIR_FK_D)/Rect.o

$(OUTDIR_FK_D)/Registry.o : $(SRC_UTILS)/Registry.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/Registry.cpp -o $(OUTDIR_FK_D)/Registry.o

$(OUTDIR_FK_D)/Stream.o : $(SRC_IO)/Stream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/Stream.cpp -o $(OUTDIR_FK_D)/Stream.o

$(OUTDIR_FK_D)/StringUtils.o : $(SRC_UTILS)/StringUtils.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/StringUtils.cpp -o $(OUTDIR_FK_D)/StringUtils.o

$(OUTDIR_FK_D)/System.o : $(SRC_UTILS)/System.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/System.cpp -o $(OUTDIR_FK_D)/System.o

$(OUTDIR_FK_D)/SystemToolkit.o : $(SRC_UTILS)/SystemToolkit.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/SystemToolkit.cpp -o $(OUTDIR_FK_D)/SystemToolkit.o

$(OUTDIR_FK_D)/TextInputStream.o : $(SRC_IO)/TextInputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/TextInputStream.cpp -o $(OUTDIR_FK_D)/TextInputStream.o

$(OUTDIR_FK_D)/TextOutputStream.o : $(SRC_IO)/TextOutputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IO)/TextOutputStream.cpp -o $(OUTDIR_FK_D)/TextOutputStream.o

$(OUTDIR_FK_D)/Thread.o : $(SRC_UTILS)/Thread.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/Thread.cpp -o $(OUTDIR_FK_D)/Thread.o

$(OUTDIR_FK_D)/ThreadEvent.o : $(SRC_EVENT)/ThreadEvent.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_EVENT)/ThreadEvent.cpp -o $(OUTDIR_FK_D)/ThreadEvent.o

$(OUTDIR_FK_D)/VCFMath.o : $(SRC_CORE)/VCFMath.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_CORE)/VCFMath.cpp -o $(OUTDIR_FK_D)/VCFMath.o

$(OUTDIR_FK_D)/VCFProcess.o : $(SRC_UTILS)/VCFProcess.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/VCFProcess.cpp -o $(OUTDIR_FK_D)/VCFProcess.o

$(OUTDIR_FK_D)/XMLParser.o : $(SRC_UTILS)/XMLParser.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_UTILS)/XMLParser.cpp -o $(OUTDIR_FK_D)/XMLParser.o

$(OUTDIR_FK_D)/LinuxPeer.o : $(SRC_IMPLKIT)/LinuxPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxPeer.cpp -o $(OUTDIR_FK_D)/LinuxPeer.o

$(OUTDIR_FK_D)/LinuxFilePeer.o : $(SRC_IMPLKIT)/LinuxFilePeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxFilePeer.cpp -o $(OUTDIR_FK_D)/LinuxFilePeer.o

$(OUTDIR_FK_D)/LinuxFileStream.o : $(SRC_IMPLKIT)/LinuxFileStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxFileStream.cpp -o $(OUTDIR_FK_D)/LinuxFileStream.o

$(OUTDIR_FK_D)/PosixThread.o : $(SRC_IMPLKIT)/PosixThread.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/PosixThread.cpp -o $(OUTDIR_FK_D)/PosixThread.o

$(OUTDIR_FK_D)/LinuxLibraryPeer.o : $(SRC_IMPLKIT)/LinuxLibraryPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxLibraryPeer.cpp -o $(OUTDIR_FK_D)/LinuxLibraryPeer.o

$(OUTDIR_FK_D)/PosixMutex.o : $(SRC_IMPLKIT)/PosixMutex.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/PosixMutex.cpp -o $(OUTDIR_FK_D)/PosixMutex.o

$(OUTDIR_FK_D)/PosixCondition.o : $(SRC_IMPLKIT)/PosixCondition.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/PosixCondition.cpp -o $(OUTDIR_FK_D)/PosixCondition.o

$(OUTDIR_FK_D)/LinuxProcessPeer.o : $(SRC_IMPLKIT)/LinuxProcessPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxProcessPeer.cpp -o $(OUTDIR_FK_D)/LinuxProcessPeer.o

$(OUTDIR_FK_D)/LinuxRegistry.o : $(SRC_IMPLKIT)/LinuxRegistry.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxRegistry.cpp -o $(OUTDIR_FK_D)/LinuxRegistry.o

$(OUTDIR_FK_D)/LinuxSemaphorePeer.o : $(SRC_IMPLKIT)/LinuxSemaphorePeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxSemaphorePeer.cpp -o $(OUTDIR_FK_D)/LinuxSemaphorePeer.o

$(OUTDIR_FK_D)/LinuxSystemPeer.o : $(SRC_IMPLKIT)/LinuxSystemPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxSystemPeer.cpp -o $(OUTDIR_FK_D)/LinuxSystemPeer.o

$(OUTDIR_FK_D)/LinuxSystemToolkit.o : $(SRC_IMPLKIT)/LinuxSystemToolkit.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxSystemToolkit.cpp -o $(OUTDIR_FK_D)/LinuxSystemToolkit.o

$(OUTDIR_FK_D)/LinuxProcessIORedirector.o : $(SRC_IMPLKIT)/LinuxProcessIORedirector.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS_D) $(SRC_IMPLKIT)/LinuxProcessIORedirector.cpp -o $(OUTDIR_FK_D)/LinuxProcessIORedirector.o


###########################################################
#Release files
###########################################################


$(OUTDIR_FK)/BasicException.o : $(SRC_EXCPT)/BasicException.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_EXCPT)/BasicException.cpp -o $(OUTDIR_FK)/BasicException.o

$(OUTDIR_FK)/BasicInputStream.o : $(SRC_IO)/BasicInputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/BasicInputStream.cpp -o $(OUTDIR_FK)/BasicInputStream.o

$(OUTDIR_FK)/BasicOutputStream.o : $(SRC_IO)/BasicOutputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/BasicOutputStream.cpp -o $(OUTDIR_FK)/BasicOutputStream.o

$(OUTDIR_FK)/Class.o : $(SRC_CORE)/Class.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/Class.cpp -o $(OUTDIR_FK)/Class.o

$(OUTDIR_FK)/ClassRegistry.o : $(SRC_CORE)/ClassRegistry.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/ClassRegistry.cpp -o $(OUTDIR_FK)/ClassRegistry.o

$(OUTDIR_FK)/Directory.o : $(SRC_IO)/Directory.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/Directory.cpp -o $(OUTDIR_FK)/Directory.o

$(OUTDIR_FK)/ErrorLog.o : $(SRC_UTILS)/ErrorLog.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/ErrorLog.cpp -o $(OUTDIR_FK)/ErrorLog.o

$(OUTDIR_FK)/Event.o : $(SRC_EVENT)/Event.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_EVENT)/Event.cpp -o $(OUTDIR_FK)/Event.o

$(OUTDIR_FK)/EventHandler.o : $(SRC_EVENT)/EventHandler.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_EVENT)/EventHandler.cpp -o $(OUTDIR_FK)/EventHandler.o

$(OUTDIR_FK)/File.o : $(SRC_IO)/File.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/File.cpp -o $(OUTDIR_FK)/File.o

$(OUTDIR_FK)/FilePath.o : $(SRC_UTILS)/FilePath.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/FilePath.cpp -o $(OUTDIR_FK)/FilePath.o

$(OUTDIR_FK)/FileStream.o : $(SRC_IO)/FileStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/FileStream.cpp -o $(OUTDIR_FK)/FileStream.o

$(OUTDIR_FK)/FileUtils.o : $(SRC_IO)/FileUtils.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/FileUtils.cpp -o $(OUTDIR_FK)/FileUtils.o

$(OUTDIR_FK)/FoundationKit.o : $(SRC_CORE)/FoundationKit.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/FoundationKit.cpp -o $(OUTDIR_FK)/FoundationKit.o

$(OUTDIR_FK)/InterfaceClass.o : $(SRC_CORE)/InterfaceClass.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/InterfaceClass.cpp -o $(OUTDIR_FK)/InterfaceClass.o

$(OUTDIR_FK)/Library.o : $(SRC_UTILS)/Library.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/Library.cpp -o $(OUTDIR_FK)/Library.o

$(OUTDIR_FK)/Locales.o : $(SRC_CORE)/Locales.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/Locales.cpp -o $(OUTDIR_FK)/Locales.o

$(OUTDIR_FK)/MemoryStream.o : $(SRC_IO)/MemoryStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/MemoryStream.cpp -o $(OUTDIR_FK)/MemoryStream.o

$(OUTDIR_FK)/Mutex.o : $(SRC_UTILS)/Mutex.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/Mutex.cpp -o $(OUTDIR_FK)/Mutex.o

$(OUTDIR_FK)/Object.o : $(SRC_CORE)/Object.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/Object.cpp -o $(OUTDIR_FK)/Object.o

$(OUTDIR_FK)/ObjectWithEvents.o : $(SRC_CORE)/ObjectWithEvents.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/ObjectWithEvents.cpp -o $(OUTDIR_FK)/ObjectWithEvents.o

$(OUTDIR_FK)/Parser.o : $(SRC_UTILS)/Parser.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/Parser.cpp -o $(OUTDIR_FK)/Parser.o

$(OUTDIR_FK)/Point.o : $(SRC_CORE)/Point.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/Point.cpp -o $(OUTDIR_FK)/Point.o

$(OUTDIR_FK)/PropertyChangeEvent.o : $(SRC_EVENT)/PropertyChangeEvent.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_EVENT)/PropertyChangeEvent.cpp -o $(OUTDIR_FK)/PropertyChangeEvent.o

$(OUTDIR_FK)/Rect.o : $(SRC_CORE)/Rect.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/Rect.cpp -o $(OUTDIR_FK)/Rect.o

$(OUTDIR_FK)/Registry.o : $(SRC_UTILS)/Registry.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/Registry.cpp -o $(OUTDIR_FK)/Registry.o

$(OUTDIR_FK)/Stream.o : $(SRC_IO)/Stream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/Stream.cpp -o $(OUTDIR_FK)/Stream.o

$(OUTDIR_FK)/StringUtils.o : $(SRC_UTILS)/StringUtils.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/StringUtils.cpp -o $(OUTDIR_FK)/StringUtils.o

$(OUTDIR_FK)/System.o : $(SRC_UTILS)/System.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/System.cpp -o $(OUTDIR_FK)/System.o

$(OUTDIR_FK)/SystemToolkit.o : $(SRC_UTILS)/SystemToolkit.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/SystemToolkit.cpp -o $(OUTDIR_FK)/SystemToolkit.o

$(OUTDIR_FK)/TextInputStream.o : $(SRC_IO)/TextInputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/TextInputStream.cpp -o $(OUTDIR_FK)/TextInputStream.o

$(OUTDIR_FK)/TextOutputStream.o : $(SRC_IO)/TextOutputStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IO)/TextOutputStream.cpp -o $(OUTDIR_FK)/TextOutputStream.o

$(OUTDIR_FK)/Thread.o : $(SRC_UTILS)/Thread.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/Thread.cpp -o $(OUTDIR_FK)/Thread.o

$(OUTDIR_FK)/ThreadEvent.o : $(SRC_EVENT)/ThreadEvent.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_EVENT)/ThreadEvent.cpp -o $(OUTDIR_FK)/ThreadEvent.o

$(OUTDIR_FK)/VCFMath.o : $(SRC_CORE)/VCFMath.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_CORE)/VCFMath.cpp -o $(OUTDIR_FK)/VCFMath.o

$(OUTDIR_FK)/VCFProcess.o : $(SRC_UTILS)/VCFProcess.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/VCFProcess.cpp -o $(OUTDIR_FK)/VCFProcess.o

$(OUTDIR_FK)/XMLParser.o : $(SRC_UTILS)/XMLParser.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_UTILS)/XMLParser.cpp -o $(OUTDIR_FK)/XMLParser.o

$(OUTDIR_FK)/LinuxPeer.o : $(SRC_IMPLKIT)/LinuxPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxPeer.cpp -o $(OUTDIR_FK)/LinuxPeer.o

$(OUTDIR_FK)/LinuxFilePeer.o : $(SRC_IMPLKIT)/LinuxFilePeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxFilePeer.cpp -o $(OUTDIR_FK)/LinuxFilePeer.o

$(OUTDIR_FK)/LinuxFileStream.o : $(SRC_IMPLKIT)/LinuxFileStream.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxFileStream.cpp -o $(OUTDIR_FK)/LinuxFileStream.o

$(OUTDIR_FK)/PosixThread.o : $(SRC_IMPLKIT)/PosixThread.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/PosixThread.cpp -o $(OUTDIR_FK)/PosixThread.o

$(OUTDIR_FK)/LinuxLibraryPeer.o : $(SRC_IMPLKIT)/LinuxLibraryPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxLibraryPeer.cpp -o $(OUTDIR_FK)/LinuxLibraryPeer.o

$(OUTDIR_FK)/LinuxMutex.o : $(SRC_IMPLKIT)/LinuxMutex.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxMutex.cpp -o $(OUTDIR_FK)/LinuxMutex.o

$(OUTDIR_FK)/LinuxProcessPeer.o : $(SRC_IMPLKIT)/LinuxProcessPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxProcessPeer.cpp -o $(OUTDIR_FK)/LinuxProcessPeer.o

$(OUTDIR_FK)/LinuxRegistry.o : $(SRC_IMPLKIT)/LinuxRegistry.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxRegistry.cpp -o $(OUTDIR_FK)/LinuxRegistry.o

$(OUTDIR_FK)/LinuxSemaphorePeer.o : $(SRC_IMPLKIT)/LinuxSemaphorePeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxSemaphorePeer.cpp -o $(OUTDIR_FK)/LinuxSemaphorePeer.o

$(OUTDIR_FK)/LinuxSystemPeer.o : $(SRC_IMPLKIT)/LinuxSystemPeer.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxSystemPeer.cpp -o $(OUTDIR_FK)/LinuxSystemPeer.o

$(OUTDIR_FK)/LinuxSystemToolkit.o : $(SRC_IMPLKIT)/LinuxSystemToolkit.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxSystemToolkit.cpp -o $(OUTDIR_FK)/LinuxSystemToolkit.o

$(OUTDIR_FK)/LinuxProcessIORedirector.o : $(SRC_IMPLKIT)/LinuxProcessIORedirector.cpp $(FOUNDATIONKIT_HDRS)
	$(CXX) $(CXX_FLAGS) $(SRC_IMPLKIT)/LinuxProcessIORedirector.cpp -o $(OUTDIR_FK)/LinuxProcessIORedirector.o


