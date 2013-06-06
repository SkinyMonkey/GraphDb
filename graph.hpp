#ifndef __GRAPH__
#define __GRAPH__

class	Graph
{
public:
  // BFS
  // DFS

  Node*				add_node(Node* node)
    {
      this->__nodes.push_back(node);
      return node;
    }

  Node*				add_node(void)
    {
      this->__nodes.push_back(new Node());
      return *this->__nodes.end();
    }

  void				delete_node(Node* node)
    {
      remove_element<Node*>(this->__nodes, node);
    }

  void				delete_node(int index)
    {
      remove_element<Node*>(this->__nodes, this->__nodes[index]);
    }

  void				delete_node(Node::uid node_id)
    {
      remove_element<Node*>(this->__nodes, this->operator[](node_id));
    }

  void				clear(void)
    {
      this->__nodes.clear();
    }

  std::vector<Node*> const&	nodes(void)
    {
      return this->__nodes;
    }

  Node*		operator[](int index)
    {
      return this->__nodes[index];
    }

  Node*		operator[](Node::uid node_id)
    {
      int	i;
      
      for (i = 0; i < this->__nodes.size(); ++i)
	if (this->__nodes[i]->id() == node_id)
	  return this->__nodes[i];
      return NULL;
    }

  void		dump_edges()
    {
      int	i;
      
      for (i = 0; i < this->__nodes.size(); ++i)
	this->__nodes[i]->dump_edges();
    }

  void		to_json()
    {
      int	i;
 
      // FIMXE : cout { ?
      for (i = 0; i < this->__nodes.size(); ++i)
	this->__nodes[i]->to_json();
      // FIXME : cout }
    }

private:
  std::vector<Node*>		__nodes;
};

#endif /* __GRAPH__ */
