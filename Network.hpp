#ifndef __NETWORK__
#define __NETWORK__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Network : public ANetwork
{
public:
  ~Network(){}

  Network(boost::asio::io_service& io_service, short port, AProtocol* protocol)
    : ANetwork(protocol),
    __io_service(io_service),
    __acceptor(io_service, tcp::endpoint(tcp::v4(), port))
  {
    NetworkSession* new_session = new NetworkSession(__io_service, this->__protocol);
    __acceptor.async_accept(new_session->socket(),
        boost::bind(&Network::accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void accept(NetworkSession* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      std::cout << "Accept" << std::endl;
      new_session->start();
      new_session = new NetworkSession(__io_service, this->__protocol);
      __acceptor.async_accept(new_session->socket()
          ,boost::bind(&Network::accept
            ,this
            ,new_session
            ,boost::asio::placeholders::error));
    }
    else
      delete new_session;
  }

private:
  Network(const Network&);
  Network& operator=(const Network&);

  boost::asio::io_service& __io_service;
  tcp::acceptor 	   __acceptor;
};


#endif /* __NETWORK__ */
