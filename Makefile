all: display nodisplay

display:
	g++ -o test.X test.cpp -Wall -W -lm -ansi -pedantic -O3 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_use_xshm -Dcimg_use_xrandr -lpthread -lX11 -lXext -lXrandr -Dwindows -I/home/rock64/testGlobal/CImg
	./test.X

nodisplay:
	g++ test.cpp -o test -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -lpthread -Dcimg_display=0 -I/home/rock64/testGlobal/CImg
	./test
