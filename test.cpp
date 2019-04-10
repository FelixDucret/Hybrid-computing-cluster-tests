#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>

struct ret{
	bool e;	//Error bool
	int l;	//Used to return the length in the main function
};

ret prog_options(int ac, char* av[])
{
	namespace po = boost::program_options;
	
	ret result;
	//Error bool
	result.e = 0;
	result.l=0;

	// Declare the supported options.

	po::options_description desc("Allowed options");
	desc.add_options()
    		("help", "produce help message")
    		("length", po::value<int>(), "choose the length of vectors you want to sum")
	;
//	po::positional_options_description p;

//	p.add("length", -l);

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
		 // options(desc).positional(p).run()


	po::notify(vm);    

	if (vm.count("help")) {
    		std::cout << desc << "\n";
    		result.e = 1;
	}

	else if (vm.count("length")) {
    		std::cout << "You chose to sum the " 
 		<< vm["length"].as<int>() << " first terms of the vectors.\n";
		result.l=vm["length"].as<int>();

	} else {
    		std::cout << "You chose to sum all the terms of the vectors.\n";
	}
	
	
	return result;
}

int main(int ac, char* av[])
{
	ret s=prog_options(ac, av);
	
	

	return s.e;

}//main
