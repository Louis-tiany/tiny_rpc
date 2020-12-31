server : Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc TcpServer.cc test.cc Acceptor.cc 
	g++ Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc TcpServer.cc test.cc Acceptor.cc -o a -g


client : Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc Acceptor.cc ./client.cc ./Connector.cc ./TcpClient.cc
	g++ Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc Acceptor.cc ./client.cc ./Connector.cc ./TcpClient.cc -o cli  
http : Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc TcpServer.cc Acceptor.cc ./httpserver_test.cc ./HttpServer.cc ./HttpContext.cc ./HttpResponse.cc 
	g++ Socket.h EventLoop.cc Channel.cc TcpConnection.cc Poller.cc TcpServer.cc Acceptor.cc ./httpserver_test.cc ./HttpServer.cc ./HttpContext.cc ./HttpResponse.cc -o http
