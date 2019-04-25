all:
	g++ -o test test.cpp -I/usr/include/CImg -Wall -W -lm -ansi -pedantic -O1 -fno-tree-pre -Dcimg_use_vt100 -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr
nodisplay:
	g++ test.cpp -o test -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -lpthread -Dcimg_display=0
