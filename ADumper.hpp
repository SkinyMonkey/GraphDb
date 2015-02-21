#ifndef __IDUMPER__
#define __IDUMPER__

class AGraph;

class ADumper
{
public:
	ADumper()
	  {}
	virtual ~ADumper() {}

	virtual std::string	dump(AGraph const*, Protocol::error_code&) const = 0;

private:
	ADumper(const ADumper&);
	ADumper& operator=(const ADumper&);
};

#endif /* __IDUMPER__ */
