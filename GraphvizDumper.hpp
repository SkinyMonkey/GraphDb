#ifndef __DUMPER__
#define __DUMPER__

#include <boost/graph/graphviz.hpp>

class GraphvizDumper : public ADumper
{
public:
  GraphvizDumper()
    {}
  ~GraphvizDumper() {}

  std::string	operator()(AGraph const* graph, Protocol::error_code& error_code) const
    {
      std::ostringstream out;

      // FIXME
      CAST_CALL(graph)

      boost::write_graphviz(out, real_typed_graph,
	    boost::make_label_writer(
           boost::get(&Vertex::Vertex::name, real_typed_graph)));
      return (out.str());
    }

private:
  GraphvizDumper(const GraphvizDumper&);
  GraphvizDumper& operator=(const GraphvizDumper&);

  // FIXME : define a prop_writer that dump the attributes of the node
};

#endif /* __DUMPER__ */
