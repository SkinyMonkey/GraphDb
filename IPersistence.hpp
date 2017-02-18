#ifndef __IPERSISTENCE__
#define __IPERSISTENCE__

class IPersistence
{
  public:
  virtual void  use(std::string const&, Protocol::error_code&) = 0;

  virtual void  add(std::string const&, Protocol::error_code&) = 0;

  virtual void  add(Vertex::id const&,
                    std::string const&,
                    std::map<std::string, std::string> const&,
                    Protocol::error_code&) = 0;

  virtual void  add(Edge::id const&,
                    std::string const&,
                    Protocol::error_code&) = 0;
  
  virtual void  remove(std::string const&,
                       Protocol::error_code&) = 0;

  virtual void  remove(Vertex::id const&,
                       Protocol::error_code&) = 0;

  virtual void  remove(Edge::id const&,
                       Protocol::error_code&) = 0;

  // FIXME : update?
};

/*
class IConnexion
{
  public:
}
*/

#endif  /* __IPERSISTENCE__ */
