#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include <CL/cl.hpp>


#define MAX_SOURCE_SIZE (0x100000)

using namespace std;


inline void
checkErr(cl_int err, const char * name)
{
    if (err != CL_SUCCESS) {
        cerr << "ERROR: " << name
                 << " (" << err << ")" << endl;
//            eILURE);
    }
}

int main(void) {
    // Create the two input vectors
    const int LIST_SIZE = 512; //65536;
    vector<int> A;
    A.reserve(LIST_SIZE);
    vector<int> B;
    B.reserve(LIST_SIZE);
    vector<int> C;
    C.reserve(LIST_SIZE);

    for(int i = 0; i < LIST_SIZE; i++) {
        A.push_back(i);
        B.push_back(LIST_SIZE - i);
        C.push_back(-99);
    }
    cout<<"vector size="<<A.size()<<endl;

    // Load the kernel source code into the array source_str

    ifstream kernel_file("vector_add_kernel.cl");
    checkErr(kernel_file.is_open() ? CL_SUCCESS:-1, "vector_add_kernel.cl"); 

    string prog(istreambuf_iterator<char>(kernel_file), (istreambuf_iterator<char>()));
    cl::Program::Sources source(1, make_pair(prog.c_str(), prog.length()+1));

    // Get platform and device information

    cl_int err;
    vector< cl::Platform > platformList;
    cl::Platform::get(&platformList);
    checkErr(platformList.size()!=0 ? CL_SUCCESS : -1, "cl::Platform::get");
    cerr << "Platform number is: " << platformList.size() << endl;

    string platformVendor;
    platformList[0].getInfo((cl_platform_info)CL_PLATFORM_VENDOR, &platformVendor);
    cerr << "Platform is by: " << platformVendor << "\n";
    cl_context_properties cprops[3] = 
        {CL_CONTEXT_PLATFORM, (cl_context_properties)(platformList[0])(), 0};

    // Create an OpenCL context

    cl::Context context(
       CL_DEVICE_TYPE_GPU,
       cprops,
       NULL,
       NULL,
       &err);
    checkErr(err, "Context::Context()");

    vector<cl::Device> devices;
    devices = context.getInfo<CL_CONTEXT_DEVICES>();
    checkErr(devices.size() > 0 ? CL_SUCCESS : -1, "devices.size() > 0");

    // Create a command queue

    cl::CommandQueue queue(context, devices[0], 0, &err);
    checkErr(err, "CommandQueue::CommandQueue()");


    // Create memory buffers on the device for each vector 
    int* outA = &(A[0]);
    cl::Buffer outCLA(context, (cl_mem_flags)(CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR),  LIST_SIZE*sizeof(int), (void*)outA, &err);
    checkErr(err, "Buffer::BufferA()");
    int* outB = &(B[0]);
    cl::Buffer outCLB(context, (cl_mem_flags)(CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR),  LIST_SIZE*sizeof(int), (void*)outB, &err);
    checkErr(err, "Buffer::BufferB()");
    int* outC = &(C[0]);
    cl::Buffer outCLC(context, (cl_mem_flags)(CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR), LIST_SIZE*sizeof(int), (void*)outC, &err);
    checkErr(err, "Buffer::BufferC()");

    // Copy the lists A and B to their respective memory buffers

    cl::Event event;
    vector<cl::Event> events;

    cl_int state;
    event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS, &state);
    cout << state << endl;

    err = queue.enqueueWriteBuffer(outCLA, CL_TRUE, 0, LIST_SIZE*sizeof(int), outA, NULL, NULL);
//    err = queue.enqueueWriteBuffer(outCLA, CL_TRUE, 0, LIST_SIZE, outA, &events, &event);
    checkErr(err, "CommandQueue::enqueueWriteBufferA()");
//    event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS, &state);
//    cout << state << endl;

//    event.wait();

    err = queue.enqueueWriteBuffer(outCLB, CL_TRUE, 0, LIST_SIZE*sizeof(int), outB, NULL,NULL);
//    err = queue.enqueueWriteBuffer(outCLB, CL_TRUE, 0, LIST_SIZE, outB, &events, &event);
    checkErr(err, "CommandQueue::enqueueWriteBufferB()");
//    event.wait();
//    event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS, &state);
//    cout << state << endl;


    // Create a program from the kernel source

    cl::Program program(context, source);


    // Build the program

    err = program.build(devices,"");
    checkErr(kernel_file.is_open() ? CL_SUCCESS : -1, "Program::build()");

   // Create the OpenCL kernel
    cl::Kernel kernel(program, "vector_add", &err);
    checkErr(err, "Kernel::Kernel()");

    // Set the arguments of the kernel

    err = kernel.setArg(0, outCLA);
    checkErr(err, "Kernel::setArgA()");
    err = kernel.setArg(1, outCLB);
    checkErr(err, "Kernel::setArgB()");
    err = kernel.setArg(2, outCLC);
    checkErr(err, "Kernel::setArgC()");

    // Execute the OpenCL kernel on the list


    err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(LIST_SIZE), cl::NDRange(4), NULL,NULL);
//    err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(LIST_SIZE), cl::NDRange(64), &events, &event);
    checkErr(err, "CommandQueue::enqueueNDRangeKernel()");
//    event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS, &state);
//    cout << state << endl;
//    event.wait();

    // Read the memory buffer C on the device to the local variable C

    err = queue.enqueueReadBuffer(outCLC, CL_TRUE, 0, LIST_SIZE*sizeof(int), outC, NULL,NULL);
//    err = queue.enqueueReadBuffer(outCLC, CL_TRUE, 0, LIST_SIZE, outC, &events, &event);
    checkErr(err, "CommandQueue::enqueueReadBufferC()");
//    event.wait();
/*
        for(int i=0; i<LIST_SIZE; ++i)
    {
        cout << A[i] <<"+"<<B[i]<<"="<<C[i]<<", "<<flush;
   }
*/
    // Display the result to the screen
    int test=0;
    for(int i=0; i<LIST_SIZE; ++i)
    {
//	cout << C[i] <<",";
        if(A[i]+B[i]!=C[i]) ++test;
    }cout<<endl;

    cout<<"test ";
    if(test==0)
      cout<<"pass"<<endl;
    else
      cout<<"fail (count="<<test<<"/"<<C.size()<<")"<<endl;

    return EXIT_SUCCESS;

}//main

