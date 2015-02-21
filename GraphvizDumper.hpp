#ifndef __DUMPER__
#define __DUMPER__

#include <boost/graph/graphviz.hpp>

template<typename G>
class GraphvizDumper : public ADumper
{
public:
  GraphvizDumper()
    {}
  ~GraphvizDumper() {}

  std::string	dump(AGraph const* graph, Protocol::error_code& error_code) const
    {
      std::ostringstream out;
      G const*                 graph_ptr = static_cast<G const*>(graph);

      boost::write_graphviz(out, *graph_ptr,
	      boost::make_label_writer(
          boost::get(&Vertex::Vertex::name, *graph_ptr)));
      return (out.str());
    }

private:
  GraphvizDumper(const GraphvizDumper&);
  GraphvizDumper& operator=(const GraphvizDumper&);

  // FIXME : define a prop_writer that dump the attributes of the node
};

#endif /* __DUMPER__ */
