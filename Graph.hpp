#ifndef __GRAPH__
#define __GRAPH__

#include "__Graph.hpp"

// FIXME : cog to generate different types
//         mother class to contain in hash table an instance of each?

typedef __Graph<boost::adjacency_list<boost::vecS
	       ,boost::vecS
	       ,boost::undirectedS
	       ,Vertex::Vertex
	      ,Edge::Edge> > Graph;


std::map<std::string, AGraph*>  graph_types;

// FIXME : one map for typeindex : instance
//       : one map for name : instance
//       we want to determine cast from instance -> typeindex
//
//       generate/template functions to return type from type_name/hash(type_name)
//       switch name/cast ...
//

// FIXME : boost::no_property, boost::listS

void  init_graph_types(void)
{
// The following python code generates each specialisation possibility

/* [[[cog
import cog
  
#   launch a.out in debug mode with option, get mangling names and split into array
#   use index to generate mangling to type function

# FIXME : see above

mangled_names = [
"N5boost14adjacency_listINS_4vecSES1_NS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyENS_5listSEEE",
"N5boost14adjacency_listINS_4vecSENS_5listSENS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES2_EE",
"N5boost14adjacency_listINS_5listSENS_4vecSENS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_5listSES1_NS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_4vecSES1_NS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyENS_5listSEEE",
"N5boost14adjacency_listINS_4vecSENS_5listSENS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES2_EE",
"N5boost14adjacency_listINS_5listSENS_4vecSENS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_5listSES1_NS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_4vecSES1_NS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyENS_5listSEEE",
"N5boost14adjacency_listINS_4vecSENS_5listSENS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES2_EE",
"N5boost14adjacency_listINS_5listSENS_4vecSENS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_5listSES1_NS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE"
]

combinations = []
for graph_type in ("adjacency_list",):
   for direction in ("undirectedS", "directedS", "bidirectionalS"):
       for out_edge_list in ("vecS", "listS"):
           for vertex_list in ("vecS", "listS"):
            combinations.append((graph_type, out_edge_list, vertex_list, direction))
            
index = 0
for combination in combinations:
  cog.outl("""
    graph_types["{}_{}_{}_{}"] = new __Graph<boost::{}<boost::{}
	                                          ,boost::{}
	                                          ,boost::{}
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();
""".format(combination[0], combination[1], combination[2], combination[3],
           combination[0], combination[1], combination[2], combination[3]))
  index += 1

cog.outl("""std::vector<std::string> graph_types = {""")

for mangled_name in mangled_names:
    cog.outl('"{}",'.format(mangled_name))

cog.outl("""};""")

cog.outl("""
#define CAST_CALL(graph)\\
  auto index_it = std::find(graph_types.begin(), graph_types.end(), graph->type_name());\\
  int index = index_it - graph_types.begin();\\
  switch (index)\\
  {\\""")

index = 0
for combination in combinations:
  cog.outl("""          case {}: \\
          {{\\
            auto real_typed_graph = *static_cast<__Graph<boost::{}<boost::{}\\
                                   ,boost::{}\\
                                   ,boost::{}\\
                                   ,Vertex::Vertex\\
                                   ,Edge::Edge> > const* >(graph);\\
            break;\\
      }}\\""".format(index, combination[0], combination[1], combination[2], combination[3]))
  index += 1

cog.outl("""        default:\\
      ;\\
  }""")

]]]*/

    graph_types["adjacency_list_vecS_vecS_undirectedS"] = new __Graph<boost::adjacency_list<boost::vecS
	                                          ,boost::vecS
	                                          ,boost::undirectedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_vecS_listS_undirectedS"] = new __Graph<boost::adjacency_list<boost::vecS
	                                          ,boost::listS
	                                          ,boost::undirectedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_listS_vecS_undirectedS"] = new __Graph<boost::adjacency_list<boost::listS
	                                          ,boost::vecS
	                                          ,boost::undirectedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_listS_listS_undirectedS"] = new __Graph<boost::adjacency_list<boost::listS
	                                          ,boost::listS
	                                          ,boost::undirectedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_vecS_vecS_directedS"] = new __Graph<boost::adjacency_list<boost::vecS
	                                          ,boost::vecS
	                                          ,boost::directedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_vecS_listS_directedS"] = new __Graph<boost::adjacency_list<boost::vecS
	                                          ,boost::listS
	                                          ,boost::directedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_listS_vecS_directedS"] = new __Graph<boost::adjacency_list<boost::listS
	                                          ,boost::vecS
	                                          ,boost::directedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_listS_listS_directedS"] = new __Graph<boost::adjacency_list<boost::listS
	                                          ,boost::listS
	                                          ,boost::directedS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_vecS_vecS_bidirectionalS"] = new __Graph<boost::adjacency_list<boost::vecS
	                                          ,boost::vecS
	                                          ,boost::bidirectionalS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_vecS_listS_bidirectionalS"] = new __Graph<boost::adjacency_list<boost::vecS
	                                          ,boost::listS
	                                          ,boost::bidirectionalS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_listS_vecS_bidirectionalS"] = new __Graph<boost::adjacency_list<boost::listS
	                                          ,boost::vecS
	                                          ,boost::bidirectionalS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();


    graph_types["adjacency_list_listS_listS_bidirectionalS"] = new __Graph<boost::adjacency_list<boost::listS
	                                          ,boost::listS
	                                          ,boost::bidirectionalS
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();

std::vector<std::string> graph_types = {
"N5boost14adjacency_listINS_4vecSES1_NS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyENS_5listSEEE",
"N5boost14adjacency_listINS_4vecSENS_5listSENS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES2_EE",
"N5boost14adjacency_listINS_5listSENS_4vecSENS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_5listSES1_NS_11undirectedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_4vecSES1_NS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyENS_5listSEEE",
"N5boost14adjacency_listINS_4vecSENS_5listSENS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES2_EE",
"N5boost14adjacency_listINS_5listSENS_4vecSENS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_5listSES1_NS_9directedSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_4vecSES1_NS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyENS_5listSEEE",
"N5boost14adjacency_listINS_4vecSENS_5listSENS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES2_EE",
"N5boost14adjacency_listINS_5listSENS_4vecSENS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
"N5boost14adjacency_listINS_5listSES1_NS_14bidirectionalSEN6Vertex6vertexEN4Edge4edgeENS_11no_propertyES1_EE",
};

#define CAST_CALL(graph)\
  auto index_it = std::find(graph_types.begin(), graph_types.end(), graph->type_name());\
  int index = index_it - graph_types.begin();\
  switch (index)\
  {\
          case 0: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::vecS\
                                   ,boost::vecS\
                                   ,boost::undirectedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 1: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::vecS\
                                   ,boost::listS\
                                   ,boost::undirectedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 2: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::listS\
                                   ,boost::vecS\
                                   ,boost::undirectedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 3: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::listS\
                                   ,boost::listS\
                                   ,boost::undirectedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 4: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::vecS\
                                   ,boost::vecS\
                                   ,boost::directedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 5: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::vecS\
                                   ,boost::listS\
                                   ,boost::directedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 6: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::listS\
                                   ,boost::vecS\
                                   ,boost::directedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 7: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::listS\
                                   ,boost::listS\
                                   ,boost::directedS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 8: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::vecS\
                                   ,boost::vecS\
                                   ,boost::bidirectionalS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 9: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::vecS\
                                   ,boost::listS\
                                   ,boost::bidirectionalS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 10: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::listS\
                                   ,boost::vecS\
                                   ,boost::bidirectionalS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
          case 11: \
          {\
            auto real_typed_graph = *static_cast<__Graph<boost::adjacency_list<boost::listS\
                                   ,boost::listS\
                                   ,boost::bidirectionalS\
                                   ,Vertex::Vertex\
                                   ,Edge::Edge> > const* >(graph);\
            break;\
      }\
        default:\
      ;\
  }
//[[[end]]]

}

#endif /* __GRAPH__ */
