#ifndef _DEPENDENCYNODES_H__
#define _DEPENDENCYNODES_H__


#include <algorithm>



namespace xmake {

class DependencyNode {
public:	
	typedef std::vector<DependencyNode*> Vector;
	typedef Vector::iterator Iterator;
	typedef Vector::const_iterator ConstIterator;
	
	DependencyNode() : score_(0) {
		
	}
	
	DependencyNode( const std::string& aName ) : score_(0), name_(aName) {
		
	}
	
	
	void dependsOn( DependencyNode* node ) {
		childNodes_.push_back( node );
	}
	
	Vector& childNodes() {
		return childNodes_;
	}
	
	const Vector& childNodes() const{
		return childNodes_;
	}
	
	int score() {
		return score_;
	}
	
	void score( int val ) {
		score_ = val;
	}
	
	std::string name() const{
		return name_;	
	}
	
	
	void name( const std::string& val ) {
		name_ = val;
	}
	
protected:
	Vector childNodes_;	
	int score_;
	std::string name_;
private:
	
};






class DependsPred : public std::less<DependencyNode*>{
public:
	bool operator () ( DependencyNode* x, DependencyNode* y ) const {
		return x->score() < y->score();
	}
};

class CircularDependencyException : public RuntimeException {
public:
	CircularDependencyException() : RuntimeException("Circular dependency found"){}
};



class DependencyGraph {
public:	
	DependencyNode::Vector& nodes() {
		return nodes_;
	}
	
	const DependencyNode::Vector& nodes() const{
		return nodes_;
	}
	
	int travel( DependencyNode* node, DependencyNode* startingNode ) {
		int result = 0;
		DependencyNode::Iterator childIt = node->childNodes().begin();
		while ( childIt != node->childNodes().end() ) {
			
			if ( (*childIt != startingNode) ) {
				result++;
				result += travel( *childIt, startingNode );
			}			
			else if ( *childIt == startingNode ) {
				throw CircularDependencyException();
			}
			childIt ++;
		}
		return result;
	}
	
	void createDependencyList( DependencyNode::Vector& nodes ) {
		DependencyNode::Iterator it = nodes_.begin();
		
		nodes = nodes_;
		
		try {
			while ( it != nodes_.end() ) {
				DependencyNode* node = *it;
				
				node->score( travel( node, node ) );
				it ++;
			}
		}
		catch ( CircularDependencyException& e ) {
			printf( "Exception thrown: %s\n", e.err_.c_str() );
			//do not sort the nodes list!
			return;
		}		
		
		std::sort( nodes.begin(), nodes.end(), DependsPred() );
	}
protected:
	DependencyNode::Vector nodes_;
};


};

#endif //_DEPENDENCYNODES_H__


