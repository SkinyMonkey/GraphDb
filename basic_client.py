import socket
from os import system

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "Launching client on port %s" % 5005
s.connect((TCP_IP, TCP_PORT))

for command in ["add vertex",
		"add vertex",
		"add vertex",
		"add vertex",
		"add edge 1 2",
		"add edge 2 3",
		"add edge 3 4",
		"add edge 4 1",
		"add edge 4 2",
		"add edge 4 3",
		"dump"]:
  s.send(command)
  data = s.recv(BUFFER_SIZE)
  if data.split(" ")[0] == "DUMP":
    print data
    system("echo '%s' | dot -T png -o test.png" % data[5:]);

exit(0)

while True:
  command = raw_input("Network test $> ");
  if command:
    s.send(command)
    data = s.recv(BUFFER_SIZE)
    print data
s.close()
