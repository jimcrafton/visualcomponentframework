//Win32InternetToolkit.cpp


#include "vcf/InternetKit/InternetKit.h"
#include "vcf/InternetKit/Win32InternetToolkit.h"


using namespace VCF;



class Authenticater : public IAuthenticate  {
public:
	STDMETHODIMP QueryInterface(REFIID  riid, void** ppObj ) {
		if ( riid == IID_IAuthenticate ) {
			*ppObj = (void*) (IAuthenticate*)this;
			return S_OK;
		}
		else if ( riid == IID_IUnknown ) {
			*ppObj = (void*) (IUnknown*)this;
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG) AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG) Release() {
		return 0;
	}

	STDMETHODIMP Authenticate( 
            /* [out] */ HWND __RPC_FAR *phwnd,
            /* [out] */ LPWSTR __RPC_FAR *pszUsername,
            /* [out] */ LPWSTR __RPC_FAR *pszPassword) {

		String userName;
		String password;

		URLAuthenticationEvent e(url_);
		

		url_->AuthenticationRequested( &e );

		userName = e.getUserName();
		password = e.getPassword();

		if ( userName.empty() ) {
			return E_ACCESSDENIED;
		}
		
		*phwnd = NULL;

		*pszUsername = (LPWSTR) CoTaskMemAlloc( userName.size_in_bytes() + sizeof(WCHAR) );
		memset( *pszUsername, 0, userName.size_in_bytes() + sizeof(WCHAR) );
		userName.copy( *pszUsername, userName.size() );

		

		*pszPassword = (LPWSTR) CoTaskMemAlloc( password.size_in_bytes() + sizeof(WCHAR) );
		memset( *pszPassword, 0, password.size_in_bytes() + sizeof(WCHAR) );
		password.copy( *pszPassword, password.size() );


		return S_OK;
	}

	URL* url_;
};


class StatCB : public IBindStatusCallback {
public:

	URL* url_;
	OutputStream* stream_;
	Authenticater authenticater;
	uint32 downloadBytes;

	StatCB(URL* url, OutputStream* stream ):url_(url), stream_(stream){
		authenticater.url_ = url_;
		downloadBytes = 0;
	}


	STDMETHODIMP QueryInterface(REFIID  riid, void** ppObj ) {
		if ( riid == IID_IBindStatusCallback ) {
			*ppObj = (void*) (IBindStatusCallback*)this;
			return S_OK;
		}
		else if ( riid == IID_IUnknown ) {
			*ppObj = (void*) (IUnknown*)this;
			return S_OK;
		}
		else  {
			return authenticater.QueryInterface( riid, ppObj );
		}

		

		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG) AddRef() {
		return 0;
	}

	STDMETHODIMP_(ULONG) Release() {
		return 0;
	}

	STDMETHODIMP GetBindInfo( DWORD *pgrfBINDF, BINDINFO *pbindinfo ) {
		StringUtils::trace("GetBindInfo\n");
		*pgrfBINDF |= BINDF_NOWRITECACHE  |BINDF_GETNEWESTVERSION;
		return S_OK;
	}

	STDMETHODIMP OnStartBinding( DWORD  dwReserved, IBinding *pbinding ) {
		StringUtils::trace("OnStartBinding\n");
		return E_NOTIMPL;
	}

	STDMETHODIMP GetPriority( LONG *pnPriority ) {
		StringUtils::trace("GetPriority\n");
		return E_NOTIMPL;
	}

	STDMETHODIMP OnProgress( ULONG  ulProgress, ULONG  ulProgressMax, ULONG  ulStatusCode, 
								LPCWSTR  szStatusText  ) {


		String s;
		if ( szStatusText ) {
			s = szStatusText;
		}
		StringUtils::trace( Format("OnProgress\n\tulProgress: %u\n\tulProgressMax:%u\n\tulStatusCode:%u\n\tszStatusText:%s\n") %
								ulProgress % ulProgressMax % ulStatusCode % s );


		URLEvent e(url_, URL::evStatusChanged );
					
		e.setStatusText( s );

		url_->StatusChanged( &e );

		if ( e.shouldCancelDataTransfer() ) {
			return E_ABORT;
		}

		switch ( ulStatusCode ) {
			case BINDSTATUS_ENDDOWNLOADDATA : {
				downloadBytes = ulProgressMax;
				
			}
			break;
		};

		return S_OK;
	}


	STDMETHODIMP OnDataAvailable( DWORD  grfBSCF, DWORD  dwSize, FORMATETC *fmtetc, STGMEDIUM *stgmed ) {
		
		StringUtils::trace( "OnDataAvailable\n" );

		URLEvent e(url_, URL::evDataReceiving );
		e.setBytesReceived( dwSize );

		url_->DataReceiving( &e );

		if ( e.shouldCancelDataTransfer() ) {
			return E_ABORT;
		}

		if ( stgmed ) {
			if ( stgmed->pstm ) {
				
				

				ULONG bytesRead = 0;
				
				BYTE *data = new BYTE[ dwSize ];
				
				HRESULT res = stgmed->pstm->Read( data, dwSize, &bytesRead );
				
				if ( SUCCEEDED(res) ) {


					URLEvent e2(url_, URL::evDataReceived );
					
					e2.setBytesReceived( bytesRead );

					url_->DataReceived( &e2 );

					if ( e.shouldCancelDataTransfer() ) {
						return E_ABORT;
					}

					stream_->write( data, bytesRead );	
					

					switch ( grfBSCF ) {
						case BSCF_LASTDATANOTIFICATION : {
							StringUtils::trace("BSCF_LASTDATANOTIFICATION\n");
						}
						break;
					}
				}
				else {
					URLEvent e2(url_, URL::evDataError );
					url_->DataError( &e2 );
				}

				delete[] data;
				
				return res;
			}
		}
		
		return S_OK;//E_NOTIMPL;
	}

	STDMETHODIMP OnObjectAvailable( REFIID  riid, IUnknown* punk ) {
		StringUtils::trace("OnObjectAvailable\n");
		return E_NOTIMPL;
	}

	STDMETHODIMP OnLowResource( DWORD  dwReserved ) {
		StringUtils::trace("OnLowResource\n");
		return E_NOTIMPL;
	}

	STDMETHODIMP OnStopBinding( HRESULT  hrStatus, LPCWSTR  szStatusText ) {

		StringUtils::trace("OnStopBinding\n");

		//if ( NULL != m_dlg ) {
		//	m_dlg->m_downloadStatus = szStatusText;		
		//}

		if ( !SUCCEEDED(hrStatus) ) {
			URLEvent e(url_, URL::evDataError );
			url_->DataError( &e );
		}
		else {
			URLEvent done(url_, URL::evDataComplete );
			done.setBytesReceived( downloadBytes );

			url_->DataComplete( &done );
		}

		return S_OK;
	}
};







Win32InternetToolkit::Win32InternetToolkit()
{
	OleInitialize( NULL );
}

Win32InternetToolkit::~Win32InternetToolkit()
{
	OleUninitialize();
}

void Win32InternetToolkit::internal_getDataFromURL( URL* url, OutputStream* stream )
{	
	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

	StatCB cb(url,stream);

	HRESULT res = URLOpenStreamW( NULL, url->getURLString().c_str(), 0, &cb );

	if ( !SUCCEEDED(res) ) {
		
		::CoUninitialize();

		switch (res) {
			case INET_E_AUTHENTICATION_REQUIRED : {
				throw URLAuthenticationException( "Unable to access content because some form of authentication is required." );
			}
			break;

			case INET_E_DATA_NOT_AVAILABLE : {
				throw URLDataException( "Data is unavailable. Check to see if the URL is actually correct." );
			}
			break;

			case INET_E_RESOURCE_NOT_FOUND  : {
				throw URLDataException( "The server or proxy specified could not be found." );
			}
			break;

			case INET_E_DOWNLOAD_FAILURE  : {
				throw URLDataException( "The download failed, possibly due to an incorrect username/password combination." );
			}
			break;

		
			default : {
				throw URLException( "Unable to complete the download for the requested URL." );
			}
			break;
		
		}

		//
	}

	::CoUninitialize();
}


/**
$Id$
*/
