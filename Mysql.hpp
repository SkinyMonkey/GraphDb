#ifndef __MYSQL_PERSISTENCE__
#define __MYSQL_PERSISTENCE__

class MysqlPersistence : public IPersistence
{
  public:
    MysqlPersistence(std::string const& database_name)
      : __database_name(database_name)
    {
      this->init_db(database_name);
    }

    void  init_db(std::string const& database_name)
    {
      std::cout << "CREATE DATABASE IF NOT EXISTS " + database_name << std::endl;

      // FIXME : add id/name, attributes
      std::cout << "CREATE TABLE vertices IF NOT EXISTS IN " + database_name << std::endl;
      std::cout << "CREATE TABLE edges if NOT EXISTS IN " + database_name << std::endl;
    }

    void  use(std::string const& database_name, Protocol::error_code& code)
    {
      this->__database_name = database_name;
    }
    
    void  add(std::string const& database_name, Protocol::error_code& code)
    {
      this->init_db(database_name);
    }

    void  add(Vertex::id const&,
              std::string const&,
              std::map<std::string, std::string> const&)
    {
      std::cout << "INSERT INTO vertices VALUES ()" << std::endl;
    }

    void  add(Edge::id const&,
              std::string const&,
              Protocol::error_code&)
    {
      std::cout << "INSERT INTO edges VALUES ()" << std::endl;
    }

    void  remove(std::string const& graph_name, Protocol::error_code& code)
    {
      std::cout << "DROP DATABASE " << graph_name << std::endl;
    }
    
    void  remove(Vertex::id const&,
                 Protocol::error_code&)
    {
      std::cout << "REMOVE FROM vertices VALUES ()" << std::endl;
    }

    void  remove(Edge::id const&,
                         Protocol::error_code&)
    {
      std::cout << "REMOVE FROM edges VALUES ()" << std::endl;
    }

    void  get(Vertex::id const&)
    {
      std::cout << "SELECT * FROM vertex JOIN vertex_attributes ON vertex.id/vertex_attributes.id" << std::endl;
    }
    
    void  get(Edge::id const&)
    {
      std::cout << "SELECT * FROM edge JOIN edge_attributes ON edge.id/edge_attributes.id" << std::endl;
    }

  private:
    std::string               __database_name;
//    AManager<AConnexion>*   __connexions; // TODO
};

#endif /* __MYSQL_PERSISTENCE__ */
