//LinuxRunLoopPeer.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/RunLoop.h"
#include "vcf/FoundationKit/RunLoopTimer.h"
#include "vcf/FoundationKit/LinuxRunLoopPeer.h"
#include "vcf/FoundationKit/LinuxRunLoopTimerPeer.h"
#include "vcf/FoundationKit/LinuxRunLoopSourcePeer.h"

#include <sys/epoll.h>
#include <sys/syscall.h>

using namespace VCF;

namespace
{
	int gMaxNumOfEvents = 32;
}

LinuxRunLoopPeer::LinuxRunLoopPeer( RunLoop* runLoop )
	: owner_( runLoop )
	, epollfd_( ::epoll_create( gMaxNumOfEvents ) )
	, done_( false ) 
{
	if( epollfd_ == -1 ) {
		throw RuntimeException( strerror( errno ) );
	}

	wakeupEventfd_ = ::syscall( __NR_eventfd, 0 );
	if( wakeupEventfd_ == -1 ) {
		throw RuntimeException( strerror( errno ) );
	}	
	
	epoll_event ep;
	memset( &ep, 0, sizeof(epoll_event) );
	ep.events = EPOLLIN;
	ep.data.fd = wakeupEventfd_;
	
	int result = ::epoll_ctl( epollfd_, EPOLL_CTL_ADD, wakeupEventfd_, &ep );
	if( result != 0 ) {
		throw RuntimeException( strerror( errno ) );	
	}	
}

LinuxRunLoopPeer::~LinuxRunLoopPeer()
{
	int result = ::close( epollfd_ );
	if( result != 0 ) {
			// some error occured, but how to handle it?
			perror( "Couldn't close epoll file descriptor." );
	}
}

void LinuxRunLoopPeer::run()
{
	typedef std::vector<epoll_event> EventVec;
	EventVec events;
	events.resize(gMaxNumOfEvents);
	
	while( !done_ ) {
		int count = ::epoll_wait( epollfd_, &events[0], events.size(), -1 );
		if( count > 0 ) {
			events.resize( count );
			for( EventVec::iterator it = events.begin(); it != events.end(); ++it ) {
				FileDescCallBackMap::iterator cit = callbackMap_.find( it->data.fd );
				if( cit != callbackMap_.end() ) {
					SmartPtr<Procedure>::Shared procedure = cit->second;
					procedure->invoke();
				}
			}
		}
		else if( count == 0 ) {
			// nothing todo 
		}
		else {
			// some error occured, but how to handle it?
			perror( "epoll_wait failed." );
		}
	}
}

void LinuxRunLoopPeer::stop()
{
	done_ = true;
	int result = ::close( epollfd_ );
	if( result != 0 ) {
		throw RuntimeException( strerror( errno ) );	
	}		
}

bool LinuxRunLoopPeer::isStopped() const
{
	return done_;
}

void LinuxRunLoopPeer::addTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    LinuxRunLoopTimerPeer *linuxPeer = static_cast<LinuxRunLoopTimerPeer*>( peer.get() );

	int fd = linuxPeer->getFileDesc();

	epoll_event ep;
	memset( &ep, 0, sizeof(epoll_event) );
	ep.events = EPOLLIN;
	ep.data.fd = fd;
	
	int result = ::epoll_ctl( epollfd_, EPOLL_CTL_ADD, fd, &ep );
	if( result != 0 ) {
		throw RuntimeException( strerror( errno ) );	
	}
	
    Procedure *callback = new ClassProcedure<LinuxRunLoopTimerPeer>(linuxPeer, &LinuxRunLoopTimerPeer::perform);    
    callbackMap_[fd] = SmartPtr<Procedure>::Shared(callback);	
}

void LinuxRunLoopPeer::removeTimer( RunLoopTimerPtr::Shared timer )
{
    RunLoopTimerPeerPtr::Shared peer = timer->getPeer();
    LinuxRunLoopTimerPeer *linuxPeer = static_cast<LinuxRunLoopTimerPeer*>( peer.get() );

	int fd = linuxPeer->getFileDesc();
	
	int result = ::epoll_ctl( epollfd_, EPOLL_CTL_DEL, fd, NULL );
	if( result != 0 ) {
		throw RuntimeException( strerror( errno ) );
	}
	callbackMap_.erase( fd ) ;
}

void LinuxRunLoopPeer::addSource( RunLoopSourcePtr::Shared source )
{
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    LinuxRunLoopSourcePeer *linuxPeer = static_cast<LinuxRunLoopSourcePeer*>( peer.get() );

	int fd = linuxPeer->getFileDesc();

	epoll_event ep;
	memset( &ep, 0, sizeof(epoll_event) );
	ep.events = EPOLLIN;
	ep.data.fd = fd;
	
	int result = ::epoll_ctl( epollfd_, EPOLL_CTL_ADD, fd, &ep );
	if( result != 0 ) {
		throw RuntimeException( strerror( errno ) );	
	}
	
    Procedure *callback = new ClassProcedure<LinuxRunLoopSourcePeer>(linuxPeer, &LinuxRunLoopSourcePeer::perform);    
    callbackMap_[fd] = SmartPtr<Procedure>::Shared(callback);
}

void LinuxRunLoopPeer::removeSource( RunLoopSourcePtr::Shared source )
{
	source->internal_cancel();
    RunLoopSourcePeerPtr::Shared peer = source->getPeer();
    LinuxRunLoopSourcePeer *linuxPeer = static_cast<LinuxRunLoopSourcePeer*>( peer.get() );

	int fd = linuxPeer->getFileDesc();
	
	int result = ::epoll_ctl( epollfd_, EPOLL_CTL_DEL, fd, NULL );
	if( result != 0 ) {
		throw RuntimeException( strerror( errno ) );
	}
	callbackMap_.erase( fd ) ;	
}

/**
$Id$
*/
