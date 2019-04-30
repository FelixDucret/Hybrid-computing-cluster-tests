OS := $(shell uname)
OPTIONS:= 
 
ifeq ($(OS),Darwin)
        OPTIONS += -framework OpenCL
else
        OPTIONS += -lMali -L/usr/lib/aarch64-linux-gnu/
endif

all: testBoostCompute.cpp
	g++ -Wall -g testBoostCompute.cpp -o test $(OPTIONS) -DBOOST_COMPUTE_MAX_CL_VERSION=102 -lboost_program_options
	./test -l 10

clean:
	rm -rf test
