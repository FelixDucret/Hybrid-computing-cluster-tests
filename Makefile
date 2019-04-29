OS := $(shell uname)
OPTIONS:= 
 
ifeq ($(OS),Darwin)
	OPTIONS += -framework OpenCL
else
	OPTIONS += -lMali -L/usr/lib/aarch64-linux-gnu/
endif

all:	main clinfo sum

main: testOpenCL.cpp
	g++ -Wall -g testOpenCL.cpp -o main $(OPTIONS)

clean:
	rm -rf main clinfo test

clinfo:
	g++ -Wall -g clinfo.cpp -o clinfo $(OPTIONS)

sum:
	g++ -Wall -g test_vec_sum.cpp -o test $(OPTIONS)
