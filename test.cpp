#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>

int prog_options(int ac, char* av[])
{
	namespace po = boost::program_options;

	// Declare the supported options.

	po::options_description desc("Allowed options");
	desc.add_options()
    		("help", "produce help message")
//    		("length,l", po::value<int>(), "choose the length of vectors you want to sum")
	;
//	po::positional_options_description p;

//	p.add("length", -l);

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
		 // options(desc).positional(p).run()


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
}

int main(int ac, char* av[])
{
	int r=prog_options(ac, av);
	

	return r;

}//main
