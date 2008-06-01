//OSXProcessPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/OSXProcessPeer.h"
#include <sys/wait.h>


namespace VCF {

OSXProcessPeer::OSXProcessPeer():
	processTerminated_(false)
{
	memset( &processHandle_, 0, sizeof(processHandle_) );
	memset( &processHandle_.launchBlock, 0, sizeof(processHandle_.launchBlock) );
}

OSXProcessPeer::~OSXProcessPeer()
{

}


int OSXProcessPeer::getProcessThreadID()
{
	return 0;
}

bool OSXProcessPeer::createProcess( const String& processName, const String& arguments )
{
	bool result = false;
	processTerminated_ = false;

	memset( &processHandle_, 0, sizeof(processHandle_) );
	memset( &processHandle_.launchBlock, 0, sizeof(processHandle_.launchBlock) );
	processHandle_.pid = 0;
	
	CFTextString pName(processName);
	CFRefObject<CFURLRef> url = (CFURLRef)pName;
	
	LSItemInfoRecord itemInfo;
	
	String tmp = processName;
	tmp += " " + arguments;
	
	CommandLine cmdLine;
	cmdLine.splitLine( tmp );
	
	const std::vector<String>& args = cmdLine.getOriginalCommandLine();
	
	CFRefObject<CFURLRef> docURL = NULL;
	
	if ( args.size() > 1 ) {		
		CFTextString docName(args[1]);
		docURL = (CFURLRef)docName;
	}
	
	//is this app a Bundle based (OSX) app, or a unix app (default)?
	processHandle_.isUnixProcess = true;
	if ( LSCopyItemInfoForURL( url, kLSRequestAllInfo, &itemInfo ) == noErr ) {
		if ( (itemInfo.flags & kLSItemInfoIsApplication) ) {
			processHandle_.isUnixProcess = false;
		}
	}
	
	if ( !processHandle_.isUnixProcess ) {
		//use LaunchApplication
		FSRef fsRef;
		if ( CFURLGetFSRef( url, &fsRef ) ) {
			FSSpec    fsSpec;
			if ( noErr == FSGetCatalogInfo( &fsRef, kFSCatInfoNone, NULL, NULL, &fsSpec, NULL ) ) {
				FSSpec    doc_fsSpec;
				FSRef doc_fsRef;
				if ( docURL != NULL ) {
					
					if ( !CFURLGetFSRef( docURL, &doc_fsRef ) ) {
						return -1;
					}
					
					if ( noErr != FSGetCatalogInfo( &doc_fsRef, kFSCatInfoNone, NULL, NULL, &doc_fsSpec, NULL ) ) {
						return -1;
					}
				}
				
				
				static const EventTypeSpec events[] ={
												{ kEventClassApplication, kEventAppTerminated }
											};
											

				//install event handler for appl close!
				InstallApplicationEventHandler(OSXProcessPeer::osxProcessTerminated, 
												sizeof(events) / sizeof(EventTypeSpec), 
												events, this, NULL);

				
				
				/**
				AE vars
				*/
				AEAddressDesc appAddr;
				AEDescList fileList;
				AEDesc fileListElt, paraDesc;
				AppleEvent theEvent;
				AppleEvent eventReply;
				Size paraSize;
				AppParametersPtr paraData;
				
				if ( docURL != NULL ) {
					CFDataRef theData;
					theData = CFURLCreateData(nil, docURL, kCFStringEncodingUTF8, true);
					
					
					
					AECreateDesc(typeNull, NULL, 0, &appAddr);
					AECreateDesc(typeNull, NULL, 0, &fileList);
					AECreateDesc(typeNull, NULL, 0, &fileListElt);
					AECreateDesc(typeNull, NULL, 0, &theEvent);
					AECreateDesc(typeNull, NULL, 0, &eventReply);
					AECreateDesc(typeNull, NULL, 0, &paraDesc);
					
					/* create an open documents Apple Event */
					OSStatus err = AECreateDesc(typeApplSignature,	(Ptr)&itemInfo.creator, 
												sizeof(OSType), &appAddr);
					
					//create the event!
					err = AECreateAppleEvent(kCoreEventClass, kAEOpenDocuments,
											 &appAddr, kAutoGenerateReturnID, 
											 kAnyTransactionID, &theEvent);
					
					//create a single list
					err = AECreateList(NULL, 0, false, &fileList);			
					
					////create one element for the doc file name
					//err = AECreateDesc('furl', CFDataGetBytePtr(theData),CFDataGetLength(theData), &fileListElt);
					
					//CFRelease(theData);
					
					err = AECreateDesc(typeFSRef, (Ptr) (&doc_fsRef),  sizeof(FSRef), &fileListElt);
					
					err = AEPutDesc(&fileList, 0, &fileListElt);
					
					err = AEPutParamDesc(&theEvent, keyDirectObject, &fileList);
					
					
					//send the open doc event
					err = AESend(&theEvent, &eventReply, kAENoReply,kAENormalPriority, kNoTimeOut, NULL, NULL);
					
					
					/* ask the Apple Event Manager to coerce the Apple
						event into a launch application parameter block
						record. */
					err = AECoerceDesc(&theEvent, typeAppParameters,
									   &paraDesc);
					
					paraSize = AEGetDescDataSize(&paraDesc);
					paraData = (AppParametersPtr) NewPtr(paraSize);
					err = AEGetDescData(&paraDesc, paraData, paraSize );
				}
				else {
					paraData = NULL;
				}
				
		
				
				
				processHandle_.launchBlock.launchBlockID = extendedBlock;
				processHandle_.launchBlock.launchEPBLength = extendedBlockLen;
				processHandle_.launchBlock.launchFileFlags = 0;
				processHandle_.launchBlock.launchControlFlags = launchNoFileFlags | launchContinue | launchDontSwitch;
				processHandle_.launchBlock.launchAppSpec = &fsSpec;
				processHandle_.launchBlock.launchAppParameters = paraData;				
				LaunchApplication( &processHandle_.launchBlock );
				
				pid_t pid = 0;
				if ( noErr == GetProcessPID( &processHandle_.launchBlock.launchProcessSN, &pid ) ) {
					processHandle_.pid = pid;								
				}
				
				
				if (paraData != NULL) DisposePtr((Ptr) paraData);
				
				if ( docURL != NULL ) {
					AEDisposeDesc(&paraDesc);
					AEDisposeDesc(&appAddr);
					AEDisposeDesc(&fileListElt);
					AEDisposeDesc(&fileList);
					AEDisposeDesc(&theEvent);
					AEDisposeDesc(&eventReply);
				}
				/*
				EventRef theRecvdEvent;				
				while  (ReceiveNextEvent(0, NULL,kEventDurationForever,true,
										 
										 &theRecvdEvent)== noErr)
					
				{	
					SendEventToEventTarget (theRecvdEvent, GetEventDispatcherTarget());
					
					ReleaseEvent(theRecvdEvent);
					if ( processQuit ) {
						printf( "Process quit!\n" );
						break;
					}
				}
				*/
				
				//printf("Launch done!\n") ;
			}
		}
	}
	else {
		//use unix style
		int pid = 0;
		
		char** unixArgs = new char*[args.size()];
		for (size_t i=0;i<args.size();i++ ) {
			AnsiString s = args[i];
			char* arg = new char[s.size()+1];
			s.copy( arg, s.size() );
			arg[s.size()] = 0;
			unixArgs[i] = arg;
		}
		
		//fork child process		
		pid = fork();
		if ( pid < 0 ) {
			printf( "fork failed!!\n");			
		}		
		
		
		//child executes the code
		if (pid == 0) {
			execvp(unixArgs[0], unixArgs);			
			exit(1);
		}
		
		processHandle_.pid = pid;
		
		//clean up args
		for (size_t i=0;i<args.size();i++ ) {			
			delete [] unixArgs[i];
		}
		delete [] unixArgs;
		
		//block and spin - not very efficient???
		//while (wait(&waitStatus) != pid); 		
	}

	return result;
}

String OSXProcessPeer::getProcessFileName()
{
	return processFileName_;
}


uint32 OSXProcessPeer::terminate()
{
	if ( processHandle_.isUnixProcess ) {
		kill( processHandle_.pid, SIGKILL );
	}
	else {
		AEAddressDesc appPSN;
		AppleEvent quitEvent;	
		
		OSStatus err = AECreateDesc(typeProcessSerialNumber,
									(Ptr)&processHandle_.launchBlock.launchProcessSN, 
									sizeof(processHandle_.launchBlock.launchProcessSN), 
									&appPSN);
		
		//create the event!
		err = AECreateAppleEvent(kCoreEventClass, kAEQuitApplication ,
								 &appPSN, kAutoGenerateReturnID, 
								 kAnyTransactionID, &quitEvent);
		
		
		
		//send the open doc event
		err = AESend(&quitEvent, NULL, kAENoReply,kAENormalPriority, kNoTimeOut, NULL, NULL);
		
		AEDisposeDesc(&appPSN);
		AEDisposeDesc(&quitEvent);
	}
    return 0;
}


Waitable::WaitResult OSXProcessPeer::wait( uint32 milliseconds )
{
	Waitable::WaitResult result = Waitable::wrWaitFinished;
	
	return result;
}

Waitable::WaitResult OSXProcessPeer::wait()
{
	Waitable::WaitResult result = Waitable::wrWaitFinished;
	
	//the following is probably wrong, we need another solution???
	if ( processHandle_.isUnixProcess ) {
	}
	else {		
		EventRef theRecvdEvent;				
		while  (ReceiveNextEvent(0, NULL,kEventDurationForever,true,
								 
								 &theRecvdEvent)== noErr)
			
		{	
			
			SendEventToEventTarget (theRecvdEvent, GetEventDispatcherTarget());
			
			ProcessSerialNumber psn = {0};
			OSStatus err = GetEventParameter( theRecvdEvent,
                                        kEventParamProcessID,
                                        typeProcessSerialNumber,
                                        NULL,
                                        sizeof(psn),
                                        NULL,
                                        &psn );
			
			ReleaseEvent(theRecvdEvent);
			if ( processTerminated_ && (psn.highLongOfPSN == processHandle_.launchBlock.launchProcessSN.highLongOfPSN) &&
					(psn.lowLongOfPSN == processHandle_.launchBlock.launchProcessSN.lowLongOfPSN) ) {
				printf( "Process quit!\n" );
				break;
			}
		}
	}
	
	return result;
}

OSStatus OSXProcessPeer::osxProcessTerminated( EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void * inUserData )
{
	OSXProcessPeer* thisPtr = (OSXProcessPeer*)inUserData;
	thisPtr->processTerminated_ = true;
	
	return noErr;
}

};


/**
$Id$
*/
