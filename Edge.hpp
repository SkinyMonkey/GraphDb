#ifndef __EDGE__
#define __EDGE__

namespace					Edge
{
  typedef std::pair<Vertex::id, Vertex::id>	id;
  typedef struct 				edge
    {
      id					uid;
    }						Edge;
}

#endif /* __EDGE__ */
