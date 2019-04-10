all :
	c++ -I ~/ test.cpp -o test \
	-L/usr/lib64 -lboost_program_options-mt
