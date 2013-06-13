#ifndef __INETWORK__
#define __INETWORK__

using namespace Protocol;

class ANetwork
{
public:
  ANetwork(AProtocol* p)
    : __protocol(p)
    {}
  ~ANetwork()
    {}

protected:
  AProtocol*	__protocol;

private:
  ANetwork(const ANetwork&);
  ANetwork& operator=(const ANetwork&);

};

#endif /* __INETWORK__ */
