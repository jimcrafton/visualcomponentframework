#ifndef XMLPARTICLERESOURCEHANDLER_H
#define XMLPARTICLERESOURCEHANDLER_H
//XMLParticleResourceHandler.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/XMLParser.h"

using namespace VCF;

class XMLParticleResourceHandler{
public:
	ParticleResource *loadResource(VCF::InputStream *in){
		XMLParser parser;
		ParticleResource *r=new ParticleResource();
		parser.parse(in);

		XMLNode *node=parser.getParsedNodes()->nextElement();
		XMLNode *child=0;
		String data;

		child=node->getNodeByName("Type");
		r->mType=(ParticleResource::ParticleType)StringUtils::fromStringAsInt(child->getCDATA());

		child=node->getNodeByName("Alignment");
		r->mAlignment=(ParticleResource::Alignment)StringUtils::fromStringAsInt(child->getCDATA());

		child=node->getNodeByName("Amount");
		r->mAmount=StringUtils::fromStringAsInt(child->getCDATA());

		child=node->getNodeByName("ParticleLife");
		r->mParticleLife=StringUtils::fromStringAsFloat(child->getCDATA());

		child=node->getNodeByName("SystemLife");
		r->mSystemLife=StringUtils::fromStringAsFloat(child->getCDATA());

		child=node->getNodeByName("GradualStart");
		data=child->getCDATA();
		StringUtils::trimWhiteSpaces(data);
		r->mGradualStart=StringUtils::fromStringAsBool(data);

		child=node->getNodeByName("InitialSpeed");
		r->mInitialSpeed=StringUtils::fromStringAsFloat(child->getCDATA());

		child=node->getNodeByName("InitialVariance");
		r->mInitialVariance=StringUtils::fromStringAsFloat(child->getCDATA());

		child=node->getNodeByName("InitialSpeed");
		r->mInitialSpeed=StringUtils::fromStringAsFloat(child->getCDATA());

		child=node->getNodeByName("Gravity");
		r->mGravity=StringUtils::fromStringAsFloat(child->getCDATA());

		child=node->getNodeByName("GravityVariance");
		r->mGravityVariance=StringUtils::fromStringAsFloat(child->getCDATA());

		child=node->getNodeByName("Blending");
		r->mBlending=(ParticleResource::Blending)StringUtils::fromStringAsInt(child->getCDATA());

		child=node->getNodeByName("DepthTest");
		if(child){
			data=child->getCDATA();
			StringUtils::trimWhiteSpaces(data);
			r->mDepthTest=StringUtils::fromStringAsBool(data);
		}

		child=node->getNodeByName("StartColor");
		data=child->getCDATA();
#if 0
		r->mStartColor[0]=StringUtils::fromStringAsFloat(data);
		data=StringUtils::eraseLeftOfChar(data,' ');
		r->mStartColor[1]=StringUtils::fromStringAsFloat(data);
		data=StringUtils::eraseLeftOfChar(data,' ');
		r->mStartColor[2]=StringUtils::fromStringAsFloat(data);
		data=StringUtils::eraseLeftOfChar(data,' ');
		r->mStartColor[3]=StringUtils::fromStringAsFloat(data);
#else
		sscanf(data.ansi_c_str(),"%f %f %f %f",&r->mStartColor[0],&r->mStartColor[1],&r->mStartColor[2],&r->mStartColor[3]);
#endif

		child=node->getNodeByName("EndColor");
		data=child->getCDATA();
#if 0
		r->mEndColor[0]=StringUtils::fromStringAsFloat(data);
		data=StringUtils::eraseLeftOfChar(data,' ');
		r->mEndColor[1]=StringUtils::fromStringAsFloat(data);
		data=StringUtils::eraseLeftOfChar(data,' ');
		r->mEndColor[2]=StringUtils::fromStringAsFloat(data);
		data=StringUtils::eraseLeftOfChar(data,' ');
		r->mEndColor[3]=StringUtils::fromStringAsFloat(data);
#else
		sscanf(data.ansi_c_str(),"%f %f %f %f",&r->mEndColor[0],&r->mEndColor[1],&r->mEndColor[2],&r->mEndColor[3]);
#endif

		child=node->getNodeByName("TrailingSystem");
		if(child){
			data=child->getCDATA();
			StringUtils::trimWhiteSpaces(data);
			r->mTrailingSystem=data;
		}

		child=node->getNodeByName("EndingSystem");
		if(child){
			data=child->getCDATA();
			StringUtils::trimWhiteSpaces(data);
			r->mEndingSystem=data;
		}

		return r;
	}

	void saveResource(ParticleResource *r,VCF::OutputStream *out){
		XMLNode *node=new XMLNode("ParticleResource");
		XMLNode *child=0;
		String data;

		child=new XMLNode("Type");
		child->setCDATA(StringUtils::toString(r->mType));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("Alignment");
		child->setCDATA(StringUtils::toString(r->mAlignment));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("Amount");
		child->setCDATA(StringUtils::toString(r->mAmount));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("ParticleLife");
		child->setCDATA(StringUtils::toString(r->mParticleLife));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("SystemLife");
		child->setCDATA(StringUtils::toString(r->mSystemLife));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("GradualStart");
		child->setCDATA(StringUtils::toString(r->mGradualStart));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("InitialSpeed");
		child->setCDATA(StringUtils::toString(r->mInitialSpeed));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("InitialVariance");
		child->setCDATA(StringUtils::toString(r->mInitialVariance));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("Gravity");
		child->setCDATA(StringUtils::toString(r->mGravity));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("GravityVariance");
		child->setCDATA(StringUtils::toString(r->mGravityVariance));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("Blending");
		child->setCDATA(StringUtils::toString(r->mBlending));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("DepthTest");
		child->setCDATA(StringUtils::toString(r->mDepthTest));
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("StartColor");
		data=StringUtils::toString(r->mStartColor[0])+" "+
					StringUtils::toString(r->mStartColor[1])+" "+
					StringUtils::toString(r->mStartColor[2])+" "+
					StringUtils::toString(r->mStartColor[3]);
		child->setCDATA(data);
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("EndColor");
		data=StringUtils::toString(r->mEndColor[0])+" "+
					StringUtils::toString(r->mEndColor[1])+" "+
					StringUtils::toString(r->mEndColor[2])+" "+
					StringUtils::toString(r->mEndColor[3]);
		child->setCDATA(data);
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("TrailingSystem");
		child->setCDATA(r->mTrailingSystem);
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		child=new XMLNode("EndingSystem");
		child->setCDATA(r->mEndingSystem);
		child->addChildNode(new XMLNode("dummy"));
		node->addChildNode(child);

		// Write it out this way, so the XML doesn't end with a null
		data=node->toString();
		out->write(data.ansi_c_str(),data.size());

		delete node;
	}
};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:18  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.2.1  2004/12/21 01:24:32  marcelloptr
*added cvs log section
*
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


#endif // XMLPARTICLERESOURCEHANDLER_H


