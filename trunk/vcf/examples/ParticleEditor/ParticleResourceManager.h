#ifndef PARTICLERESOURCEMANAGER_H
#define PARTICLERESOURCEMANAGER_H

#include "XMLParticleResourceHandler.h"

#include <map>

class ParticleResourceManager{
public:
	static ParticleResource *loadResource(const std::string &name){
		std::map<std::string,ParticleResource*>::iterator it=getMap().find(name);
		if(it==getMap().end()){
			FileInputStream *in=0;
			try{
				in=new VCF::FileInputStream(name);
			}
			catch(std::exception &e){
				e; // Get rid of warning
			}

			if(in){
				XMLParticleResourceHandler handler;

				ParticleResource *r=handler.loadResource(in);
				delete in;
				if(r){
					getMap()[name]=r;
					return r;
				}
			}
		}
		else{
			return it->second;
		}

		return 0;
	}

	static void reset(){
		getMap().clear();
	}

	static std::map<std::string,ParticleResource*> &getMap(){
		static std::map<std::string,ParticleResource*> m;
		return m;
	}
};

#endif

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:15:10  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/11/01 17:19:00  marcelloptr
*just added few lines at the end of file
*
*Revision 1.1.2.1  2004/11/01 14:38:59  pallindo
*Initial checkin of the particle editor example.  Just shows off a more complex opengl application using the VCF.
*
*/



