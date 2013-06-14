#ifndef __IDUMPER__
#define __IDUMPER__

class ADumper
{
public:
	ADumper()
	  {}
	virtual ~ADumper() {}

	virtual std::string	operator()(Graph const*, Protocol::error_code*) const = 0;

private:
	ADumper(const ADumper&);
	ADumper& operator=(const ADumper&);
};

#endif /* __IDUMPER__ */
