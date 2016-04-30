import socket

s = socket.socket()
s.connect((raw_input("input ip :"),80))
while 1:
    s.send(raw_input("input:    "))
s.close()
