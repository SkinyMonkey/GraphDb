# send info on server via socket
import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "Launching client on port %s" % 5005
s.connect((TCP_IP, TCP_PORT))
while True:
  command = raw_input("Network test $> ");
  if command:
    s.send(command)
    data = s.recv(BUFFER_SIZE)
    print data
s.close()
