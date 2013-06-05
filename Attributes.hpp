#ifndef	__ATTRIBUTES__
#define __ATTRIBUTES__

class	Attributes
{
	public:
	void		add_attribute(const std::string& name
							 ,const std::string&  value)
	{
		this->__attributes[name][value].set(name, value);
	}

	Attribute*	get_attribute(const std::string& name
							 ,const std::string& value)
	{
		return &this->__attributes[name][value];
	}

	void		dump_attributes_edges(const std::string& name
							 		 ,const std::string& value)
	{
		int		i;

		std::cout << "----- dump -----" << std::endl;
		std::cout << name << "[" << value << "]" << std::endl;
		for (i = 0; i < this->__attributes[name][value].select().size(); ++i)
		std::cout << " -> "
				  << this->__attributes[name][value].select()[i]->id()
				  << std::endl;

	}
	private:
		std::map<std::string,
				 std::map<std::string, Attribute> > __attributes;
};

#endif /* __ATTRIBUTES__ */
