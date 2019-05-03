#include <CImg.h>
#include <iostream>
using namespace cimg_library;


int main() {
  CImg<unsigned char> image("Image_test.png"), visu(500,400,1,1,0);//,image2("Image_test-2.png");
  //CImg<unsigned char> image3 = image+image2;

  unsigned char* pix=image.data();
  for(int i=0; i<1000; ++i)
	*(pix+i+15000)=255;
  //std::cout << "Image size : " << image.size() << std::endl;
  //std::cout << "Image width : " << image.width() << std::endl;
  //std::cout << "Image height : " << image.height() << std::endl;


#ifdef windows
  const unsigned char white[] = { 255,255,255 };
  CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Grayscale level");
  while (!main_disp.is_closed() && !draw_disp.is_closed()) {
    main_disp.wait();
    if (main_disp.button() && main_disp.mouse_y()>=0) {
      const int y = main_disp.mouse_y();
      visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),white,1,1,0,255,0).display(draw_disp);
      }
    }
#endif
  return 0;
}
