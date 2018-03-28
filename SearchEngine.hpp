#ifndef __SEARCHENGINE__
#define __SEARCHENGINE__

enum Operation {
  EQUAL,
  GT,
  LT,
  GTE,
  LTE
};

// name = "ok"
// a > 1
// a < 1
template <class G>
class QueryElement {
  Query(const Graph& G
       ,const Operation operation
       ,const std::string& field
       ,const std::string& value)
  : __graph(G),
  , __operation(operation)
  , __field(field)
  , __value(value) {
    // TODO : get the hash from graph here?
  }

  void operator()(Vertex& vertex) {
    // vertexFieldValue = ;
    // checkedValue = this->__value;
    // return this->__operations[this->__operation](vertexFieldValue, checkedValue);
  }
  
  void operator()(Edge& edge) {
    // edgeFieldValue = ;
    // checkedValue = this->__value;
    // return this->__operations[this->__operation](edgeFieldValue, checkedValue);
  }

protected:
  Graph     __graph;
  Operation __operation;
  String    __field;
  String    __value;
}

// OR : queryelement returning a or of two subqueryelements
// AND: queryelement returning an and of two subqueryelements
// VertexQueryElement : public QueryElement
// EdgeQueryElement : public QueryElement // FIXME gets a second value as constructor, a different operator()()

class SearchEngine : public ISearchEngine
{
public:
	SearchEngine(){}
	~SearchEngine(){}

private:
	SearchEngine(const SearchEngine&);
	SearchEngine& operator=(const SearchEngine&);

//	std::list<Vertex*> ;
};


#endif /* __SEARCHENGINE__ */
