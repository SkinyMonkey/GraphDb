#ifndef __PROTOCOL__
#define __PROTOCOL__

#include "AProtocol.hpp"

class Protocol : public AProtocol
{
public:
	Protocol(INetwork const* n)
	  : AProtocol(n)
	{}
	~Protocol(){}

private:
	Protocol(const Protocol&);
	Protocol& operator=(const Protocol&);
};


#endif /* __PROTOCOL__ */
