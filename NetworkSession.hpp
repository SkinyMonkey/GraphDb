#ifndef __NETWORKSESSION__
#define __NETWORKSESSION__

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
using namespace Protocol;

class NetworkSession
{
public:
    NetworkSession(boost::asio::io_service& io_service, AProtocol* p)
      : __socket(io_service), __protocol(p)
      {
      }

    ~NetworkSession()
      {
      }

    tcp::socket& socket()
      {
	return __socket;
      }

    void start()
      {
	std::cout << "Session starting" << std::endl;
	__socket.async_read_some(boost::asio::buffer(__data, MAX_LENGTH),
				 boost::bind(&NetworkSession::read,
			         this,
				 boost::asio::placeholders::error,
				 boost::asio::placeholders::bytes_transferred));
      }

    void read(const boost::system::error_code& error,
		     size_t bytes_transferred)
      {
	if (!error)
	  {
	    std::cout << this->__data << std::endl;
	    std::string result = this->__protocol->interpret(std::string(this->__data));
	    ::bzero(this->__data, MAX_LENGTH);
	    boost::asio::async_write(__socket,
				     boost::asio::buffer(result),
				     boost::bind(&NetworkSession::write,
                                     this,
				     boost::asio::placeholders::error));
	  }
	else
	  {
	    std::cout << "Error : " << error.message() << std::endl;
	    delete this;
	  }
      }

    void write(const boost::system::error_code& error)
      {
	if (!error)
	  {
	    __socket.async_read_some(boost::asio::buffer(__data, MAX_LENGTH),
				     boost::bind(&NetworkSession::read,
				     this,
				     boost::asio::placeholders::error,
				     boost::asio::placeholders::bytes_transferred));
	  }
	else
	  delete this;
      }

  private:
    NetworkSession(const NetworkSession&);
    NetworkSession& operator=(const NetworkSession&);

    AProtocol*		__protocol;
    tcp::socket 	__socket;
    enum 		{ MAX_LENGTH = 1024 };
    char 		__data[MAX_LENGTH];
};

#endif /* __NETWORKSESSION__ */
