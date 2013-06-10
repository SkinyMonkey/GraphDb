#ifndef __APROTOCOL__
#define __APROTOCOL__

class Core;
class ANetwork;

class AProtocol
{
public:
  AProtocol(){}
  ~AProtocol(){}

  void	set_core(Core* c)
    {
      this->__core = c;
    }

  void	set_network(ANetwork* n)
    {
      this->__network = n;
    }
  
  virtual std::string	interpret(std::string const& command) = 0;

protected:
  Core*			__core;
  ANetwork*		__network;

private:
  AProtocol(const AProtocol&);
  AProtocol& operator=(const AProtocol&);
};

#endif /* __APROTOCOL__ */
