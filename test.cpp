#include <CImg.h>
using namespace cimg_library;

int main() {
  CImg<unsigned char> image("Image_test.png"), visu(500,400,1,1,0),image2("Image_test-2.png");
  const unsigned char white[] = { 255,255,255 };
  CImg<unsigned char> image3(640,400,1,1,0);
  image3 = image+image2;
  CImgDisplay main_disp(image3,"Click a point"), draw_disp(visu,"Grayscale level");
  while (!main_disp.is_closed() && !draw_disp.is_closed()) {
    main_disp.wait();
    if (main_disp.button() && main_disp.mouse_y()>=0) {
      const int y = main_disp.mouse_y();
      visu.fill(0).draw_graph(image3.get_crop(0,y,0,0,image3.width()-1,y,0,0),white,1,1,0,255,0).display(draw_disp);
      }
    }
  return 0;
}
