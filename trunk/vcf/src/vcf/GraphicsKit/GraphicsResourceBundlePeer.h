#ifndef _GRAPHICSRESOURCEBUNDLEPEER_H__
#define _GRAPHICSRESOURCEBUNDLEPEER_H__

namespace VCF {


class Image;

/**
class GraphicsResourceBundlePeer documentation
*/
class GRAPHICSKIT_API GraphicsResourceBundlePeer {
public: 	
	virtual ~GraphicsResourceBundlePeer(){};

	virtual Image* getImage( const String& resourceName ) = 0;

};





};



#endif //_GRAPHICSRESOURCEBUNDLEPEER_H__



