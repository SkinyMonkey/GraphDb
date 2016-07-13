#ifndef __VERTEX__
#define __VERTEX__

namespace			                            Vertex
{
  typedef unsigned long		                id;
  typedef struct		                      vertex
    {
      id			                            uid;
      std::string		                      name;
      std::map<std::string, std::string>  attributes;
    }				                              Vertex;
}

#endif /* __VERTEX__ */
