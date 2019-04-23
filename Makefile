OS := $(shell uname)
OPTIONS:= 
 
ifeq ($(OS),Darwin)
	OPTIONS += -framework OpenCL
else
	OPTIONS += -lMali -L/usr/lib/aarch64-linux-gnu/
endif

all:
	g++ -Wall -g testOpenCL.cpp -o main $(OPTIONS)
	g++ -Wall -g clinfo.cpp -o clinfo $(OPTIONS)

main: testOpenCL.cpp
	g++ -Wall -g testOpenCL.cpp -o main $(OPTIONS)

clean:
	rm -rf main clinfo

clinfo:
	g++ -Wall -g clinfo.cpp -o clinfo $(OPTIONS)
