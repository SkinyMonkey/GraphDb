#ifndef	__ATTRIBUTE__
#define __ATTRIBUTE__

class	Node;

class	Attribute
{
	public:
	void				set(const std::string& name
						   ,const std::string& value)
	{
		this->__name = name;
		this->__value = value;
	}

	void				add_connexion(Node* node)
	{
		this->__connexions.push_back(node);
	}

	std::string		value() const
	{
		return this->__value;
	}

	const std::vector<Node*>&	select(void) const
	{
		return this->__connexions;
	}

	private:
	// std::String -> generic Data
	std::string					__name;
	std::string					__value;
	std::vector<Node*>			__connexions;
};

#endif /* __ATTRIBUTE__ */
