//#include <boost/lambda/lambda.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
//#include <algorithm>

int main(int ac, char* av[])
{
	//using namespace boost::lambda;
	//typedef std::istream_iterator<int> in;
	namespace po = boost::program_options;

	//std::for_each(
	//	in(std::cin), in(), std::cout << (_1 * 3) << " " );


	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
    		("help", "produce help message")
    		("compression", po::value<int>(), "set compression level")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
    		std::cout << desc << "\n";
    		return 1;
	}

	if (vm.count("compression")) {
    		std::cout << "Compression level was set to " 
 		<< vm["compression"].as<int>() << ".\n";
	} else {
    		std::cout << "Compression level was not set.\n";
	}

	return 0;


}//main
