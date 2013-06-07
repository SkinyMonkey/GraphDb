#ifndef __CONFIGURATION__
#define __CONFIGURATION__

class Configuration
{
public:
	Configuration(std::string const&)
	  {
	    //FIXME : read the configuration
	  }
	~Configuration()
	  {}

private:
	Configuration(const Configuration&);
	Configuration& operator=(const Configuration&);
};


#endif /* __CONFIGURATION__ */
