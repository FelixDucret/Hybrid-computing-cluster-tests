//Packages Boost
#include <vector>
#include <iostream>
#include <boost/compute.hpp>
#include <boost/program_options.hpp>

//Package CImg
#include <CImg.h>

namespace compute = boost::compute;
namespace po = boost::program_options;

using namespace cimg_library;



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
    CImg<unsigned char> image("Image_test.png"), visu(500,400,1,1,0),image2("Image_test-2.png");
    //CImg<unsigned char> image3 = image+image2;

    int N_LINES = prog_options(ac, av);     //Maximum size (image size) : 400*600=240000

    //Variable: nombre de lignes de l'image
    int h = image.height();

    //tests on VECTOR_SIZE to see it has a right value
    while (N_LINES<0 || N_LINES>h-1)
    {
        std::cout << "Please enter a valid value (cannot be superior to " << h-1 << ")" << std::endl;
        std::cin >> N_LINES;
    }

    if(N_LINES==0)
	return  0;

    //test to see if images have the same size and thus are comparable
    if(image2.height()!=h || image2.width()!=image.width())
    {
	std::cout << "The two images do not have the same size, they can't be summed" << std::endl;
	return -1;
    }

    /*

    // get the default compute device
    compute::device gpu = compute::system::default_device();

    // create a compute context and command queue
    compute::context ctx(gpu);
    compute::command_queue queue(ctx, gpu);

    // generate two int vectors
    //char* ptr_vector1(&image);
    //char* ptr_vector2(&image);
    std::vector<char> host_vector3(VECTOR_SIZE);


    // create vectors on the device
    compute::vector<char> device_vector1(VECTOR_SIZE, ctx);
    compute::vector<char> device_vector2(VECTOR_SIZE, ctx);
    compute::vector<char> device_vector3(VECTOR_SIZE, ctx);


    // copy data to the device
    compute::copy(
        image.begin(), image(VECTOR_SIZE), device_vector1.begin(), queue
    );
    compute::copy(
        image2.begin(), image2(VECTOR_SIZE), device_vector2.begin(), queue
    );

    //Add vectors

    //boost::compute::transform(device_vector1.begin(), device_vector1.end(), ddevice_vector2.begin(), device_vector3.begin(), compute::plus<int>(), queue);

    using compute::lambda::_1;
    using compute::lambda::_2;

    boost::compute::transform(device_vector1.begin(), device_vector1.end(), device_vector2.begin(), device_vector3.begin(),
       _1+_2 , queue);
    // c[id]=a[id]+b[id]; //kernel
    // return a+b //BOOST_COMPUTE_FUNCTION

    // copy data back to the host
    compute::copy(
        device_vector3.begin(), device_vector3.end(), host_vector3.begin(), queue
    );
    int err = 0;
    //std::cout << "Values : " << std::endl;
    for(unsigned int i=0; i<host_vector3.size(); ++i)
    {
        if(host_vector3[i]!=image[i]+image2[i])
        {
                ++err;
        }
        //std::cout << host_vector3[i] << std::endl;
    }
    std::cout << "Errors : " << err << "/" << host_vector3.size() << std::endl;

*/

#ifdef windows
  const unsigned char white[] = { 255,255,255 };
  CImg<unsigned char> image3(600, 400, 1, 1, 0);
  CImgDisplay main_disp(image3,"Click a point"), draw_disp(visu,"Grayscale level");
  while (!main_disp.is_closed() && !draw_disp.is_closed()) {
    main_disp.wait();
    if (main_disp.button() && main_disp.mouse_y()>=0) {
      const int y = main_disp.mouse_y();
      visu.fill(0).draw_graph(image3.get_crop(0,y,0,0,image3.width()-1,y,0,0),white,1,1,0,255,0).display(draw_disp);
      }
    }
#endif
  return 0;
}

