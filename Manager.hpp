#ifndef __MANAGER__
#define __MANAGER__

template<typename Managed>
class AManager
{
  public:
    virtual bool exists_or_error(std::string const& element_name,
                                         Protocol::error_code& error_code,
                                          std::string& error_string)
    {return false;}

    virtual bool exists(std::string const&) const {return false;}

    virtual void add(std::string const&, Managed const*)
    {}
    
    virtual Managed const*  get(std::string const& element_name){return NULL;}
};

template<typename Managed>
class Manager : public AManager<Managed>
{
  public:
    Manager(std::string const& element_type)
      : __element_type(element_type)
    {
    }

    ~Manager()
    {}

    bool  exists_or_error(std::string const& element_name,
                            Protocol::error_code& error_code,
                            std::string& error_string)
    {
      if (this->exists(element_name) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        error_string =\
          "This " + this->__element_type + " (" + element_name + ") could not be found";
        return false;
      }
      error_code = Protocol::OK;
      return true;
    }

    bool		exists(std::string const& element_name) const
    {
      return (this->__elements.find(element_name) != this->__elements.end());
    }

    void    add(std::string const& element_name, Managed const* element)
    {
      this->__elements[element_name] = element;
    }

    Managed const*get(std::string const& element_name)
    {
      return this->__elements[element_name];
    }

  protected:
    Manager(const Manager&);
    Manager& operator=(const Manager&);

    std::string                           __element_type;
    std::map<std::string, Managed const*>	__elements;
};

#endif /* __MANAGER__ */
