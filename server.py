import socket
import sys

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = "#your-ip"
port = #your port

serversocket.bind((host, port))
serversocket.listen(5)
print ('server started and listening on port '+str(port))

while 1:
    (clientsocket, address) = serversocket.accept()
    print ("new connection from : "+str(address))
    print("Send commands : ")
    while 1:
        r=str( sys.stdin.readline() )
        clientsocket.send(r.encode())
        r = clientsocket.recv(999)
        client_answer = str( r.decode("utf-8", errors="ignore"))
        print(str(client_answer)+"\n")
