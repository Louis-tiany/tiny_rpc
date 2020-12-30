server : Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc TcpServer.cc test.cc Acceptor.cc 
	g++ Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc TcpServer.cc test.cc Acceptor.cc -o a -g -ldl


client : Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc Acceptor.cc ./client.cc ./Connector.cc ./TcpClient.cc
	g++ Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc Acceptor.cc ./client.cc ./Connector.cc ./TcpClient.cc -o cli  
