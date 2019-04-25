all:
	g++ -o test test.cpp -Wall -W -lm -ansi -pedantic -O1 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_use_xshm -Dcimg_use_xrandr -lpthread -lX11 -lXext -lXrandr
nodisplay:
	g++ test.cpp -o test -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -lpthread -Dcimg_display=0
