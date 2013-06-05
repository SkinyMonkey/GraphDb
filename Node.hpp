#ifndef	__NODE__
#define __NODE__

#include <vector>
#include <map>
#include <string>
#include "utils.hpp"
#include "Attribute.hpp"

class	Node
{
	static long id_count;

	public:
		Node()
			: __id(Node::id_count)
		{
			Node::id_count += 1;
		}

		long			id() const
		{
			return this->__id;
		}

		void			add_connexion(Node* node)
		{
			this->__connexions.push_back(node);
			node->add_reference(this);
		}

		void			add_attribute(const std::string& name, Attribute* value)
		{
			this->__attributes[name] = value;
			value->add_connexion(this);
		}

		void			remove_connexion(Node* node)
		{
			remove_element<Node*>(this->__connexions, node);
			node->remove_reference(this);
		}

		std::string		operator[](const std::string& name)
		{
			return this->__attributes[name]->value();
		}

		void			dump_edges(void)
		{
			int			i;

			std::cout << "----- dump -----" << std::endl;
			for (i = 0; i < this->__connexions.size(); ++i)
				std::cout << this->__id
						  << " -> "
						  << this->__connexions[i]->id() << std::endl;

			for (i = 0; i < this->__references.size(); ++i)
				std::cout << this->__id
						  << " <- "
						  << this->__references[i]->id() << std::endl;
		}

	private:
		void			add_reference(Node* node)
		{
			this->__references.push_back(node);
		}

		void			remove_reference(Node* node)
		{
			remove_element<Node*>(this->__references, node);
		}

		long						__id;
		std::vector<Node*>			__connexions;
		std::vector<Node*>			__references;
		// FIXME : std::string -> Data
		std::map<std::string, Attribute*>	__attributes;
};

long Node::id_count = 0;


#endif	/* __NODE__ */
