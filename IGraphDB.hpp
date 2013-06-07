#ifndef __IGRAPHDB__
#define __IGRAPHDB__

#include "Edge.hpp"
#include "Vertex.hpp"
#include "Graph.hpp"

class IGraphDB
{
public:
	IGraphDB() {}
	virtual ~IGraphDB() {};

	virtual bool		create(std::string const&) = 0;

	virtual bool		use(std::string const&) = 0;

	virtual Edge::id	add(Vertex::id, Vertex::id) = 0;
	virtual Vertex::id	add(void) = 0;

	virtual bool		remove(Edge::id) = 0;
	virtual bool		remove(Vertex::id) = 0;

	virtual Vertex::Vertex*	get(Vertex::id) const = 0;
	virtual Edge::Edge*	get(Edge::id) const = 0;

protected:
	IGraphDB(const IGraphDB&);
	IGraphDB& operator=(const IGraphDB&);
};


#endif /* __IGRAPHDB__ */
