#include <vector>
#include <algorithm>
#include <iostream>
#include <boost/compute.hpp>
#include <boost/program_options.hpp>

namespace compute = boost::compute;
namespace po = boost::program_options;

int prog_options(int ac, char* av[])
{
	int ret;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("length,l", po::value<int>(), "choose the length of the vector that will be sorted")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);

	po::notify(vm);


	if (vm.count("help")) {
		std::cout << desc << "\n";
	}

	if (vm.count("length")) {
		ret=vm["length"].as<int>();
	}

	return ret;
}


int main(int ac, char* av[])
{
    int VECTOR_SIZE = prog_options(ac, av);	//Maximum size (for now) : 16384

    //tests on VECTOR_SIZE to see it has a right value
    while (VECTOR_SIZE<0 || VECTOR_SIZE>16384)
    {
	std::cout << "Please enter a valid value (cannot be superior to 16384) : " << std::endl;
	std::cin >> VECTOR_SIZE;
    }

    if(VECTOR_SIZE==0)
	return 0;

    // get the default compute device
    compute::device gpu = compute::system::default_device();

    // create a compute context and command queue
    compute::context ctx(gpu);
    compute::command_queue queue(ctx, gpu);

    // generate random numbers on the host
    std::vector<float> host_vector(VECTOR_SIZE);
    std::generate(host_vector.begin(), host_vector.end(), rand);

    // create vector on the device
    compute::vector<float> device_vector(VECTOR_SIZE, ctx);

    // copy data to the device
    compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), queue
    );

    // sort data on the device
    compute::sort(
        device_vector.begin(), device_vector.end(), queue
    );

    // copy data back to the host
    compute::copy(
        device_vector.begin(), device_vector.end(), host_vector.begin(), queue
    );
    int err = 0;
    for(int i=0; i<host_vector.size()-1; ++i)
    {
	if(host_vector[i]>host_vector[i+1])
		++err;
    }
    std::cout << "Errors : " << err << std::endl;

    return 0;
}
