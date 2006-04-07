#ifndef _PRINTEVENT_H__
#define _PRINTEVENT_H__



namespace VCF {
	class PrintContext;
	/**
	\class PrintEvent PrintEvent.h "vcf/GraphicsKit/PrintEvent.h"
	A PrintEvent is fired by the PrintSession during certain operations.
	*/
	class GRAPHICSKIT_API PrintEvent : public Event{
	public: 		
		PrintEvent( Object* source, PrintContext* ctx, int currentPage, ulong32 type ): Event(source,type),
			currentPage_(currentPage), context_(ctx){
			
			if ( NULL != ctx ) {
				pageBounds_ = ctx->getViewableBounds();
			}
		}
		
		PrintEvent( const PrintEvent& rhs ): 
			Event(rhs),
			currentPage_(rhs.currentPage_),
			context_(rhs.context_), 
			pageBounds_(rhs.pageBounds_) {	}
				

		PrintContext* getPrintContext() {
			return context_;
		}
		
		
		virtual Object* clone( bool deep=false ) {
			return new PrintEvent(*this);
		}
		
		Rect getPageBounds() {
			return pageBounds_;
		}

		int getCurrentPage() {
			return currentPage_;
		}
	protected:
		int currentPage_;
		PrintContext* context_;
		Rect pageBounds_;
		
	};
	
	
	
};




#endif //_PRINTEVENT_H__



