all:
	g++ ~/Boost_UDP/UDP_client.cpp -o UDPclient -std=c++03 -I /usr/include/boost/ -lboost_system -pthread
