all:
	g++ ~/Boost_UDP/UDP_server.cpp -o UDPserv -std=c++03 -I /usr/include/boost/ -lboost_system -lboost_thread
