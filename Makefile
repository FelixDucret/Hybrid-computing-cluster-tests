all:
	g++ ~/Boost_UDP/asio/example/cpp03/multicast/receiver.cpp -o UDP -std=c++03 -I /usr/include/boost/ -lboost_system -pthread
