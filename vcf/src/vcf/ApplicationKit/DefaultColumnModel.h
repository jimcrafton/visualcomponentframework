#ifndef _VCF_DEFAULTCOLUMNMODEL_H__
#define _VCF_DEFAULTCOLUMNMODEL_H__
//DefaultColumnModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__

#ifndef _VCF_COLUMNMODELEVENT_H__
#	include "vcf/ApplicationKit/ColumnModelEvent.h"
#endif // _VCF_COLUMNMODELEVENT_H__


#ifndef _VCF_COLUMNITEM_H__
#	include "vcf/ApplicationKit/ColumnItem.h"
#endif // _VCF_COLUMNITEM_H__






#define DEFAULTCOLUMNMODEL_CLASSID		"14b09dc3-777d-48cb-86d9-a311364cc41b"


namespace VCF  {

/**
*Class DefaultColumnModel documentation
*/
class APPLICATIONKIT_API DefaultColumnModel : public ColumnModel, public Persistable {
public:

	DefaultColumnModel();

	virtual ~DefaultColumnModel();

	void init();


    virtual void addModelValidationHandler( EventHandler* handler ) {
		ModelValidate += handler;
	}

	virtual void removeModelValidationHandler( EventHandler* handler ) {
		ModelValidate -= handler;
	}

	virtual void addModelHandler( EventHandler* handler ) {
		ModelEmptied += handler;
	}

	virtual void removeModelHandler( EventHandler* handler ) {
		ModelEmptied -= handler;
	}

    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate();

    /**
    * clears out the model's data
    */
    virtual void empty();

	virtual void removeListModelHandler(EventHandler * handler) {
		ModelEmptied -= handler;
	}

	virtual void addListModelHandler(EventHandler * handler) {
		ModelEmptied += handler;
	}

	/**
	*ColumnModel Handlers
	*/
	DELEGATE(ContentsChanged)
	DELEGATE(ItemAdded)
	DELEGATE(ItemDeleted)

	DELEGATE(ModelValidate)
	DELEGATE(ModelEmptied)

	virtual void addContentsChangedHandler(EventHandler * handler) {
		ContentsChanged += handler;
	}

	virtual void removeContentsChangedHandler(EventHandler * handler) {
		ContentsChanged -= handler;
	}

	virtual void addItemAddedHandler(EventHandler * handler) {
		ItemAdded += handler;
	}

	virtual void removeItemAddedHandler(EventHandler * handler) {
		ItemAdded -= handler;
	}

	virtual void addItemDeletedHandler(EventHandler * handler) {
		ItemDeleted += handler;
	}

	virtual void removeItemDeletedHandler(EventHandler * handler) {
		ItemDeleted -= handler;
	}


    virtual void deleteItem( ColumnItem* item);

    virtual void deleteItem(const unsigned long & index);

    virtual void insertItem(const unsigned long & index, ColumnItem * item);

    virtual void addItem( ColumnItem* item);

	virtual ColumnItem* getItemFromIndex( const unsigned long& index );

	virtual Enumerator<ColumnItem*>* getItems();

	virtual unsigned long getCount();

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );

protected:
	std::vector<ColumnItem*> columnItems_;
	EnumeratorContainer<std::vector<ColumnItem*>, ColumnItem*> columnContainer_;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.2.2  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.7.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.6.2.1  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.6  2003/05/17 20:37:02  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/12 03:09:29  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.1  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.4  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.2  2002/04/27 15:42:00  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.3.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.3  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTCOLUMNMODEL_H__


