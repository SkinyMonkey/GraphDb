#ifndef __DUMPER__
#define __DUMPER__

#include <boost/graph/graphviz.hpp>

template<typename G>
class AttributesWriter
{
  public:
    AttributesWriter(G const* graph) : __graph(graph) {}

  protected:
    template<typename VertexOrEdge>
      void  __write_metadata(std::ostream& out, VertexOrEdge const& e) const
      {
        // FIXME : use edge_mapping to get the id in graph ...
//        out << "[id=" << (*this->__graph)[e].uid << "]";
//        out << "[name=" << (*this->__graph)[e].name << "]";
      }

    G const*    __graph;
};

template<typename G>
class TestAttributesWriter : public AttributesWriter<G>
{
  public:
    TestAttributesWriter(G const* graph) : AttributesWriter<G>(graph) {}

    template <typename VertexOrEdge>
    void operator()(std::ostream& out, VertexOrEdge const& v) const
    {
      this->__write_metadata(out, v);
      // FIXME : here does nos compile because of some type bullshit
      std::cout << typeid(v).name() << std::endl;
      std::cout << v.m_source << std::endl;
      std::cout << v.target << std::endl;
//      for (auto attributes : this->__graph->edge_attributes[v])
//        out << "[" << attributes.first << "=" << attributes.second << "]";
    }
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
          TestAttributesWriter<G>(graph_ptr),
          TestAttributesWriter<G>(graph_ptr));
      return (out.str());
    }

  private:
    GraphvizDumper(const GraphvizDumper&);
    GraphvizDumper& operator=(const GraphvizDumper&);

};

#endif /* __DUMPER__ */
