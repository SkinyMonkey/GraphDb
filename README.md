GraphDb
=======

A graph database written in C++ with boost graphs and based on index free adjacency.
I'm currently studying a book about graph database to design the search engine.

If you interested about working on this project with me
(or simply interested about graph databases in general),
here is a free o'reilly book about it:
http://graphdatabases.com/

Also, as i use the boost graph library, you might be interested about reading this book:
http://books.google.fr/books/about/Boost_Graph_Library.html?id=CPi7g1hjyIYC&redir_esc=y

Which, of what i've seen so far, seems more clear and accurate than the online documentation.

One of my main final goal is to offer a server that can work on different kind of graph,
depending on user's needs and a set of algorithm to apply on it.

TODO:

- [ ] CRUD Core/Interface DB/DB:
  - [x]  Create a graph
  - [x]  Create a vertex
  - [x]  Create an edge
  - [x]  Name a vertex
    -> dynamic attributes?
    -> one map per graph
    -> one associative_property_map per graph

  - [ ]  Name an edge
    -> one map per graph
    -> one associative_property_map per graph

  - [ ] Add qualifiers in args
    -> unique
    -> ...

  - [x]  Retrieve a graph
  - [x]  Retrieve a vertex
  - [x]  Retrieve an edge

  - [ ]  Update a graph
  - [ ]  Update a vertex
  - [ ]  Update an edge
  
  - [x]  Delete a graph
  - [x]  Delete a vertex
  - [x]  Delete an edge
  
  - [x]  Defined attributes in vertex

- [x] Network
  - [x] receive a message
  - [x] write a message back
  - [x] transfer to protocol

- [ ] CRUD Protocol
  - text protocol
    - [x] command parsing
    - [x] command check
    - [x] use interpretation
    - [x] add interpretation
    - [x] remove interpretation
    - [x] dump

- [ ] Batchers
  - [ ] manager
  - [ ] graphviz
  - [ ] graphml

- [ ] Dumpers
  - [x] manager
  - [x] graphviz
  - [ ] graphml ?
  - [ ] json
  - [ ] yaml

- [ ] minimalistic client in python
    - [x] send a query
    - [ ] parse query
    - [ ] check query
    - [ ] interpret the answer

- [ ]  Visit a graph with a specified algorithm
  - BFS -> Browser.hpp
  - DFS

- [ ]  Query a graph
  - build query
  - apply to visitor

- [ ]  Data index?
  
- [ ] Persistence layer
    - [x] abstract calls in Core
    - [ ] mysql implementation
      - [x] class
      - [x] table and database declaration
      - [x] sql queries with attributes
      - [ ] sql calls
    - bonus
      - [ ] postgresql implementation
      - [ ] mongodb implementation
      - [ ] redis implementation
