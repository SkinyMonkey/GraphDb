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

      const strd::string name = "'name' char(64) NOT NULL"

      // FIXME : add cascade on delete

      const std::string vertices_values = "'uid' int(32) NOT NULL," << name
      this->__create_table_if_not_exists(database_name, "vertices", vertices_values)

      const std::string edges_values = "'uid_from' int(32) NOT NULL, 'uid_to' int(32) NOT NULL," << name
      this->__create_table_if_not_exists(database_name, "edges", edges_values)

      const std::string vertices_attributes_values = "'vertex_uid' int(32) NOT NULL, 'key' char(64) NOT NULL, 'value' char(64) NOT NULL"
      this->__create_table_if_not_exists(database_name, "vertices_attributes", vertices_attributes_values)
      
      const std::string edges_attributes_values = "'edge_uid_from' int(32) NOT NULL, 'edge_uid_to' int(32) NOT NULL, 'key' char(64) NOT NULL, 'value' char(64) NOT NULL"
      this->__create_table_if_not_exists(database_name, "edges_attributes", edges_attributes_values)
    }

    void  use(std::string const& database_name, Protocol::error_code& code)
    {
      this->__database_name = database_name;
    }
    
    void  add(std::string const& database_name, Protocol::error_code& code)
    {
      this->init_db(database_name);
    }

    void  add(Vertex::id const& uid,
              std::string const& name,
              std::map<std::string, std::string> const& attributes)
    {
      std::cout << "INSERT INTO vertices ('uid', 'name') VALUES ('" << uid << "','" << name <<"')" << std::endl;

      for (auto& key_value : attributes)
        std::cout << "INSERT INTO vertices_attributes ('uid', 'key', 'value') VALUES ('" << uid << "','" << key_value.first << "','" << key_value.second << "')" << std::endl;
      }
    }

    void  add(Edge::id const& uid,
              std::string const& name,
              // Protocol::error_code&)
              // std::map<std::string, std::string> const& attributes)
    {
      std::cout << "INSERT INTO edges ('uid_from', 'uid_to', 'name') VALUES ('" << uid.first << "', '" << uid.second << "', '" << name << "')" << std::endl;

      /*
      for (auto& key_value : attributes)
        std::cout << "INSERT INTO edges_attributes ('uid_from', 'uid_to', 'key', 'value') VALUES ('" << uid.first << "','" << uid.second << "','" << key_value.first << "','" << key_value.second << "')" << std::endl;
      }
      */
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

    void  get(Vertex::id const& uid)
    {
      std::cout << "SELECT * FROM vertex JOIN vertex_attributes ON vertex.uid=vertex_attributes.uid WHERE vertex.uid='" << uid << "'" << std::endl;
    }

    void  get(Edge::id const& uid)
    {
      std::cout << "SELECT * FROM edge WHERE edge.uid_from=" << uid.first << ",edge.uid_to=" << uid.second << std::endl;
//      std::cout << "SELECT * FROM edge JOIN edge_attributes ON edge.id/edge_attributes.id" << std::endl;
    }

    /*
      update a vertex
      update an edge
    */

  private:
    const string&             __create_table_if_not_exists(database_name, table_name, values) {
      std::stream             s;

      // FIXME : stream
      return "CREATE TABLE " << table_name << " IF NOT EXISTS IN " + database_name << "(" << values << ")";
    }

    std:string               __database_name;
//    AManager<AConnexion>*   __connexions; // TODO
};

#endif /* __MYSQL_PERSISTENCE__ */
