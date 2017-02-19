#ifndef __MYSQL_PERSISTENCE__
#define __MYSQL_PERSISTENCE__

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class MysqlPersistence : public IPersistence
{
  public:
    MysqlPersistence(std::string const& database_name, IGraphDB* graphdb)
      : __graphdb(graphdb)
    {
      sql::Driver *driver;

      std::cout << "MYSQL PERSISTENCE "<< std::endl;

      try {
        driver = get_driver_instance();

        Protocol::error_code code = Protocol::OK;

        // TODO : from config
        this->__connexion = driver->connect("tcp://127.0.0.1:3306", "root", "root");
        this->init_db(database_name);
        this->load(code);

        std::cout << "Connexion to database OK"<< std::endl;
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
      }
    }

    ~MysqlPersistence() {
      delete this->__connexion;
    }

    void  init_db(std::string const& database_name)
    {
      const std::string name("name char(64) NOT NULL");

      // FIXME : add cascade on delete

      try {
        sql::Statement* stmt = this->__connexion->createStatement();

        std::string create_database = std::string("CREATE DATABASE IF NOT EXISTS " + database_name);
        stmt->execute(create_database);
        
        this->__connexion->setSchema(database_name);

        std::string vertices_values = "uid int(64) NOT NULL," + name;
        stmt->execute(this->__create_table_if_not_exists(database_name, "vertices", vertices_values));

        std::string edges_values = "uid_from int(64) NOT NULL, uid_to int(64) NOT NULL," + name;
        stmt->execute(this->__create_table_if_not_exists(database_name, "edges", edges_values));

        std::string vertices_attributes_values = "vertex_uid int(64) NOT NULL, name char(64) NOT NULL, value char(64) NOT NULL";
        stmt->execute(this->__create_table_if_not_exists(database_name, "vertices_attributes", vertices_attributes_values));

        std::string edges_attributes_values = "vertex_uid_from int(64) NOT NULL, vertex_uid_to int(64) NOT NULL, name char(64) NOT NULL, value char(64) NOT NULL";
        stmt->execute(this->__create_table_if_not_exists(database_name, "edges_attributes", edges_attributes_values));
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        exit(-1);
      }
    }

    void  use(std::string const& database_name, Protocol::error_code& code)
    {
      this->__database_name = database_name;

      try {
        this->__connexion->setSchema(database_name);
        this->load(code);
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        code = Protocol::PERSISTENCE_ERROR;
      }
    }
    
    void  add(std::string const& database_name, Protocol::error_code& code)
    {
      this->init_db(database_name);
    }

    void  add(Vertex::id const& uid,
              std::string const& name,
              std::map<std::string, std::string> const& attributes,
              Protocol::error_code& error_code)
    {
      const std::string insert_vertice =
        "INSERT INTO vertices (uid, name) VALUES (" +
        boost::lexical_cast<std::string>(uid) + ",'" +
        name + "');";

      try {
        sql::Statement* stmt = this->__connexion->createStatement();

        stmt->execute(insert_vertice);

        for (auto& key_value : attributes) {
          const std::string insert_vertice_attribute =
            "INSERT INTO vertices_attributes (vertex_uid, name, value) VALUES (" +
            boost::lexical_cast<std::string>(uid) + ",'" +
            key_value.first + "','" +
            key_value.second + "')";
      
          stmt->execute(insert_vertice_attribute);
        }
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        error_code = Protocol::PERSISTENCE_ERROR;
      }
    }

    void  add(Edge::id const& uid,
              std::string const& name,
              Protocol::error_code& error_code)
              // std::map<std::string, std::string> const& attributes)
    {
      Vertex::id from = uid.get<0>();
      Vertex::id to = uid.get<1>();

      const std::string insert_edge =
        "INSERT INTO edges (uid_from, uid_to, name) VALUES (" +
        boost::lexical_cast<std::string>(from) + ", " +
        boost::lexical_cast<std::string>(to) + ", '" +
        name + "')";

      try {
        sql::Statement* stmt = this->__connexion->createStatement();

        stmt->execute(insert_edge);
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        error_code = Protocol::PERSISTENCE_ERROR;
      }

      /*
      for (auto& key_value : attributes) {
        std::cout << "INSERT INTO edges_attributes (uid_from, uid_to, key, value) VALUES (" << from << "," << to << "," << key_value.first << "," << key_value.second << ")" << std::endl;
      }
      */
    }

    void  remove(std::string const& graph_name, Protocol::error_code& error_code)
    {
      const std::string drop_database = std::string("DROP DATABASE ") + graph_name;

      try {
        sql::Statement* stmt = this->__connexion->createStatement();

        stmt->execute(drop_database);
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        error_code = Protocol::PERSISTENCE_ERROR;
      }
    }
    
    void  remove(Vertex::id const&,
                 Protocol::error_code& error_code)
    {
      const std::string remove_vertex = "REMOVE FROM vertices VALUES ()";

      try {
        sql::Statement* stmt = this->__connexion->createStatement();

        stmt->execute(remove_vertex);
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        error_code = Protocol::PERSISTENCE_ERROR;
      }
    }

    void  remove(Edge::id const&,
                         Protocol::error_code& error_code)
    {
      const std::string remove_edge = "REMOVE FROM edges VALUES ()";

      try {
        sql::Statement* stmt = this->__connexion->createStatement();

        stmt->execute(remove_edge);
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        error_code = Protocol::PERSISTENCE_ERROR;
      }
    }

    void  get(Vertex::id const& uid)
    {
      std::cout << "SELECT * FROM vertex JOIN vertex_attributes ON vertex.uid=vertex_attributes.uid WHERE vertex.uid=" << uid << "" << std::endl;
    }

    void  get(Edge::id const& uid)
    {
      Vertex::id from = uid.get<0>();
      Vertex::id to = uid.get<1>();

      std::cout << "SELECT * FROM edge WHERE edge.uid_from=" << from << ",edge.uid_to=" << to << std::endl;
      std::cout << "SELECT * FROM edge JOIN edge_attributes ON WHERE edge.from=" << from << ",to=" << to << std::endl;

//      return ;
    }

    /*
      update a vertex
      update an edge
    */

    void  load(Protocol::error_code& error_code) {
      const std::string get_vertices = std::string("SELECT * FROM vertices;");
      const std::string get_vertices_attributes = std::string("SELECT * FROM vertices_attributes ORDER BY vertex_uid;");

      const std::string get_edges = std::string("SELECT * FROM edges;");
//      const std::string get_edges_attributes = std::string("SELECT * FROM edges_attributes ORDER BY from;");

      try {
        sql::Statement* stmt = this->__connexion->createStatement();

        sql::ResultSet* get_vertices_result = stmt->executeQuery(get_vertices);
        sql::ResultSet* get_edges_result = stmt->executeQuery(get_edges);

        sql::ResultSet* get_vertices_attributes_result = stmt->executeQuery(get_vertices_attributes);

        this->__add_vertices(get_vertices_result, get_vertices_attributes_result);

        std::cout << "EDGE NUMBER " << get_edges_result->rowsCount() << std::endl;
        this->__add_edges(get_edges_result);
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        error_code = Protocol::PERSISTENCE_ERROR;
      }
    }

  private:
    void                          __fill_edge_attributes(sql::ResultSet* results,
                                                         std::map<std::string, std::string>& attributes,
                                                         std::string const& current_edge_from,
                                                         std::string const& currrent_edge_to) {
      try {
        bool next = true;

        /*
        while (next && results->getString("vertex_uid") == current_vertex) {
          const std::string name = results->getString("attribute_name");

          attributes[name] = results->getString("value");

          next = results->next();
        }
        */
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
      }
    }

    bool                          __fill_vertex_attributes(sql::ResultSet* results, std::map<std::string, std::string>& attributes, std::string const& current_vertex) {
      bool attributes_found = false;

      try {
        bool next = true;

        while (next && results->getString("vertex_uid") == current_vertex) {
          attributes_found = true;

          const std::string name = results->getString("name");

          attributes[name] = results->getString("value");

          next = results->next();
        }
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
      }

      return attributes_found;
    }

    void                          __add_vertices(sql::ResultSet* results, sql::ResultSet* attributes_results) {
      try {
        bool attribute_end = false;

        attributes_results->next();

        while (results->next()) {
          const std::string name = results->getString("name");
          const std::string uid = results->getString("uid");
          std::map<std::string, std::string> attributes;

          if (!attribute_end || attributes_results->next()) {
            attribute_end = this->__fill_vertex_attributes(attributes_results, attributes, uid);
          }
          this->__graphdb->add(name, attributes);
        }
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
      }
    }

    void                          __add_edges(sql::ResultSet* results) {
      Protocol::error_code error_code = Protocol::OK;

      try {
        while (results->next()) {
          unsigned long from;
          unsigned long to;
          const std::string name = results->getString("name");

          std::stringstream(results->getString("uid_from")) >> from;
          std::stringstream(results->getString("uid_to")) >> to;
          // this->__fill_attributes(results)

          this->__graphdb->add(from, to, name, error_code);
        }
      }
      catch (sql::SQLException& e) {
        this->__print_exception(e, __LINE__);
        error_code = Protocol::PERSISTENCE_ERROR;
      }
    }

    std::string const             __create_table_if_not_exists(std::string const& database_name, std::string const& table_name, std::string const& values) {
      return "CREATE TABLE IF NOT EXISTS " + table_name + " (" +  values + ");";
    }

    void  __print_exception(sql::SQLException& e, int line) {
        std::cerr << "# ERR: SQLException in " << __FILE__;
        std::cerr << "(" << __FUNCTION__ << ") on line " << line << std::endl;
        std::cerr << "# ERR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    std::string               __database_name;
    sql::Connection*          __connexion;

    IGraphDB*                 __graphdb;

//    AManager<AConnexion>*   __connexions; // TODO
};

#endif /* __MYSQL_PERSISTENCE__ */
