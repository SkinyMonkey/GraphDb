#ifndef __IBATCHER__
#define __IBATCHER__

class AGraph;

class ABatcher
{
public:
	ABatcher()
	  {}
	virtual ~ABatcher() {}

	virtual void batch(AGraph const*, std::string const&,Protocol::error_code&) const = 0;

private:
	ABatcher(const ABatcher&);
	ABatcher& operator=(const ABatcher&);
};

#endif /* __IBATCHER__ */
