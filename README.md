GraphDb
=======

A graph database written in C++ with boost graphs and based on index free adjacency.
I'm currently studying a book about graph database to design the search engine.

If you interested about working on this project with me
(or simply interested about graph databases in general),
here is a free o'reilly book about it:
http://graphdatabases.com/

TODO:

- [ ] CRUD Core/Interface DB/DB:
  - [x]  Create a graph
  - [x]  Create a vertex
  - [x]  Create an edge

  - [x]  Retrieve a graph
  - [x]  Retrieve a vertex
  - [x]  Retrieve an edg

  - [ ]  Update a graph
  - [ ]  Update a vertex
  - [ ]  Update an edge
  
  - [x]  Delete a graph
  - [x]  Delete a vertex
  - [x]  Delete an edge
  
  - [ ]  Defined attributes in vertex

- [x] Network
  - [x] receive a message
  - [x] write a message back
  - [x] transfer to protocol

- [ ] CRUD Protocol
  - text protocol
    - [ ] command parsing
    - [ ] command check
    - [x] use interpretation
    - [x] add interpretation
    - [x] remove interprtation

- [ ] minimalistic client in python
    - [x] send a query
    - [ ] parse query
    - [ ] check query
    - [ ] interpret the answer

- [ ]  Query a graph
- [ ]  with a specified algorithm
