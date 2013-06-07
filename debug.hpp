#ifndef __DEBUG__
#define __DEBUG__

#include <exception>

namespace	DEBUG
{
  class not_implemented : public std::exception
  {
  public:
    not_implemented(std::string const& name)
    {
      this->__buffer = new char[4096]();

      ::bzero(this->__buffer, 4096);
      ::strcpy(this->__buffer, "Not implemented :");
      ::strcat(this->__buffer, name.c_str());
    }

    virtual ~not_implemented() throw()
    {
    }

    virtual const char * what() const throw()
      {
	return this->__buffer;
      }

  private:
    char*	__buffer;
  };
}

#endif /* __DEBUG__ */
