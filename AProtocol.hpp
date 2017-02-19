#ifndef __APROTOCOL__
#define __APROTOCOL__

class Core;
class ANetwork;

namespace		Protocol
{
  enum 			error_code
    {
      OK,
      ALREADY_EXIST,
      DOESNT_EXIST,
      NOT_IMPLEMENTED,
      CANT_ADD,
      NO_NAME,
      NO_FROM,
      NO_TO,
      NO_VALUE,
      NO_TYPE,
      NO_COMMAND,
      ERROR_CODE_SIZE,
      PERSISTENCE_ERROR,
    };

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
      ANetwork*			__network;

    private:
      AProtocol(const AProtocol&);
      AProtocol& operator=(const AProtocol&);
    };
}

#endif /* __APROTOCOL__ */
