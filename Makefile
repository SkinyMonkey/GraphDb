CC    =    clang

INCLUDES = -I/usr/local/include

LIBS = -L/usr/local/lib -lboost_graph -lboost_system -lstdc++ -lmysqlclient -lmysqlcppconn-static

# -Wall -Wextra
CPPFLAGS    =    -g3 -std=c++11 $(INCLUDES)

SRCS    =    main.cpp

OBJS    =    $(SRCS:.cpp=.o)

all:    $(OBJS)
	$(CC) $(OBJS) $(CPPFLAGS) $(LIBS) 

clean:
	rm -rf $(OBJS)

fclean:    clean
	rm -rf ./a.out

re: fclean all
