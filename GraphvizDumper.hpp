#ifndef __DUMPER__
#define __DUMPER__

#include <boost/graph/graphviz.hpp>

void __write_attributes(std::ostream& out, std::map<std::string, std::string> const& attributes) // const
{
  for (auto attribute : attributes)
    out << "[" << attribute.first << "=" << attribute.second << "]";
}

template<typename G>
class TestEdgeAttributesWriter
{
  public:
    TestEdgeAttributesWriter(G const* graph) : __graph(graph) {}

    void  __write_metadata(std::ostream& out, unsigned long const& e) const
    {
      // FIXME : use edge_mapping to get the id in graph ...
      out << "[name=" << (*this->__graph)[e].name << "]";
    }

    void operator()(std::ostream& out, unsigned long const& e) const
    {
      this->__write_metadata(out, e);
      __write_attributes(out, (*this->__graph)[e].attributes);
      // this->__write_attributes(out, this->__graph->edge_attributes[e]);
      // FIXME : here does nos compile because of some type bullshit
      // std::cout << typeid(v).name() << std::endl;
//      std::cout << typeid(v).m_source << std::endl;
//      std::cout << v.target << std::endl;

    }
    
    G const*    __graph;
};

template<typename G>
class TestVertexAttributesWriter
{
  public:
    TestVertexAttributesWriter(G const* graph) : __graph(graph) {}

    void  __write_metadata(std::ostream& out, boost::detail::edge_desc_impl<boost::undirected_tag, unsigned long> const& v) const
    {
      // FIXME : use edge_mapping to get the id in graph ...
      //        out << "[id=" << (*this->__graph)[e].uid << "]";
//      out << "[name=" << (*this->__graph)[v].name << "]";
    }

    // FIXME : Edge
    void operator()(std::ostream& out, boost::detail::edge_desc_impl<boost::undirected_tag, unsigned long> const& v) const
    {
      this->__write_metadata(out, v);
      __write_attributes(out, (*this->__graph)[v].attributes);
//      this->__write_attributes(out, this->__graph->vertex_attributes[v]);
    }
    
    G const*    __graph;
};


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
          TestEdgeAttributesWriter<G>(graph_ptr),
          TestVertexAttributesWriter<G>(graph_ptr));
      return (out.str());
    }

  private:
    GraphvizDumper(const GraphvizDumper&);
    GraphvizDumper& operator=(const GraphvizDumper&);

};

#endif /* __DUMPER__ */
