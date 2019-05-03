OS := $(shell uname)
OPTIONS:= 
 
ifeq ($(OS),Darwin)
        OPTIONS += -framework OpenCL
else
        OPTIONS += -lMali -L/usr/lib/aarch64-linux-gnu/
endif

all: compute globald

globald: testGlobal.cpp
	g++ -g testGlobal.cpp -o testG.X $(OPTIONS) -DBOOST_COMPUTE_MAX_CL_VERSION=102 -lboost_program_options -Wall -I/home/rock64/testGlobal/CImg/ -W -lm -ansi -pedantic -O3 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_use_xshm -Dcimg_use_xrandr -lpthread -lX11 -lXext -lXrandr #-Dwindows/
	./testG.X -l 1000

globaln: testGlobal.cpp
	g++ -g testGlobal.cpp -o testG $(OPTIONS) -DBOOST_COMPUTE_MAX_CL_VERSION=102 -lboost_program_options -Wall -I/home/rock64/testGlobal/CImg/ -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -lpthread -Dcimg_display=0
	./testG -l 1000

compute: testBoostCompute.cpp
	g++ -Wall -g testBoostCompute.cpp -o test $(OPTIONS) -DBOOST_COMPUTE_MAX_CL_VERSION=102 -lboost_program_options
	./test -l 10

cleanc:
	rm -rf test

cleang:
	rm -rf testG

