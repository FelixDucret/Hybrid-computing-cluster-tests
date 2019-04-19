OS := $(shell uname)
OPTIONS:= 
 
ifeq ($(OS),Darwin)
	OPTIONS += -framework OpenCL
else
	OPTIONS += -lMali -L/usr/lib/aarch64-linux-gnu/
endif

main: testOpenCL.cpp
	g++ -Wall -g testOpenCL.cpp -o main $(OPTIONS)

clean:
	rm -rf main
