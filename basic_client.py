import socket
from os import system

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024
FILE_NAME = "test.png"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "Launching client on port %s" % 5005
s.connect((TCP_IP, TCP_PORT))

for command in ["add vertex",
		"add vertex souss",
		"add vertex tanon",
		"add vertex thomas",
		"add edge 1 2",
		"add edge 2 3",
		"add edge 3 4",
		"add edge 4 1",
		"add edge 4 2",
		"add edge 4 3",
		"dump default graphviz"]:
  s.send(command)
  data = s.recv(BUFFER_SIZE)
  if data.split(" ")[0] == "DUMP":
    print data
    print "Data dumped into : %s" % FILE_NAME
    system("echo '%s' | dot -T png -o %s" % (data[5:], FILE_NAME));

exit(0)

while True:
  command = raw_input("Network test $> ");
  if command:
    s.send(command)
    data = s.recv(BUFFER_SIZE)
    print data
s.close()
