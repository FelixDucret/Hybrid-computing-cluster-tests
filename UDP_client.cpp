#include <boost/asio>
#include <iostream>

using boost::asio::ip::udp;
namespace udp = boost::asio::ip::udp;

int main()
{
	try
	{
		boost::asio::io_context my_io_context;
		
ip::udp::resolver resolver(my_io_context);
ip::udp::resolver::query query("localhost", "daytime");
ip::udp::resolver::iterator iter = resolver.resolve(query);
