import socket
from os import system
from time import time

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024
FILE_NAME = "test.png"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "Launching client on port %s" % 5005
s.connect((TCP_IP, TCP_PORT))

for command in ["add vertex",
		"add vertex souss gentil=true",
		"add vertex tanon",
		"add vertex thomas",
		"add edge 0 1",
		"add edge 1 2",
		"add edge 2 3",
		"add edge 3 1",
		"add edge 3 2",
		"add edge 3 0",
		"dump graphviz"]:
#begin = time()
#i = 0
#while i < 1000000:
#  s.send("add vertex")

  s.send(command)
  data = s.recv(BUFFER_SIZE)
  data_split = data.split(" ")
  if data_split[0] == "DUMP":
    print data
    print "Data dumped into : %s" % FILE_NAME
    system("echo '%s' | dot -T png -o %s" % (data[5:], FILE_NAME));

#  print data
#  i = i + 1
#print "Elapsed time : %s" %  (time() - begin)

s.close()
