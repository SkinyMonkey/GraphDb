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

  virtual void		use(std::string const&, Protocol::error_code*) = 0;

  virtual void		add(std::string const&, Protocol::error_code*) = 0;
  virtual Edge::id	add(Vertex::id, Vertex::id, Protocol::error_code*) = 0;
  // FIXME : alloc exception -> error_code?
  virtual Vertex::id	add(void) = 0;

  virtual void		remove(std::string const&, Protocol::error_code*) = 0;
  virtual void		remove(Edge::id, Protocol::error_code*) = 0;
  virtual void		remove(Vertex::id, Protocol::error_code*) = 0;

  // FIXME : how to add const to this get on graph?
  virtual Graph*		get(std::string const&, Protocol::error_code*) = 0;
  virtual Vertex::Vertex*	get(Vertex::id, Protocol::error_code*) const = 0;
  virtual Edge::Edge*		get(Edge::id, Protocol::error_code*) const = 0;

protected:
  IGraphDB(const IGraphDB&);
  IGraphDB& operator=(const IGraphDB&);
};

#endif /* __IGRAPHDB__ */
