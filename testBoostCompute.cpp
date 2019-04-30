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

    // generate two int vectors
    std::vector<int> host_vector1(VECTOR_SIZE);
    std::vector<int> host_vector2(VECTOR_SIZE);
    for(unsigned int i=0; i<host_vector1.size(); ++i)
    {
	host_vector1[i]=i;
        //host_vector2[i]=VECTOR_SIZE-i;
    }

    // create vectors on the device
    compute::vector<int> device_vector1(VECTOR_SIZE, ctx);
    compute::vector<int> device_vector2(VECTOR_SIZE, ctx);

    // copy data to the device
    compute::copy(
        host_vector1.begin(), host_vector1.end(), device_vector1.begin(), queue
    );
   /* compute::copy(
        host_vector2.begin(), host_vector2.end(), device_vector2.begin(), queue
    );*/
    

    // Adds four to vector
    BOOST_COMPUTE_FUNCTION(int, add_four, (int x),
    {
	return x+4;
    });

    boost::compute::transform(device_vector1.begin(), device_vector1.end(), device_vector2.begin(), add_four, queue);

    // copy data back to the host
    compute::copy(
        device_vector2.begin(), device_vector2.end(), host_vector2.begin(), queue
    );
    int err = 0;
    //std::cout << "Values : " << std::endl;
    for(unsigned int i=0; i<host_vector2.size(); ++i)
    {
	if(host_vector2[i]!=host_vector1[i]+4)
	{
		++err;
	}
	//std::cout << host_vector2[i] << std::endl;
    }
    std::cout << "Errors : " << err << "/" << host_vector2.size() << std::endl;
    return 0;
}
