#include <CL/cl.hpp>
#include <iostream>

#include <string>
#include <vector>

using namespace std;


int main(void)
{
	//Platforms
	std::vector< cl::Platform > platformList;
	cl::Platform::get(&platformList);
	if(platformList.size()<=0)
	{
		cout << "Error: no platform" << endl;
		return -1;
	}
	cout << "Number of platforms: " << platformList.size() << endl;
	for(int i=0;i<platformList.size(); i++)
	{
		cout << "Platform " << i+1 << ":" << endl;
		string platformVendor;
		platformList[i].getInfo((cl_platform_info)CL_PLATFORM_VENDOR, &platformVendor);
		cout << "Platform vendor : " << platformVendor << endl;


		//Devices
		vector< cl::Device > devices;
		platformList[i].getDevices(CL_DEVICE_TYPE_ALL, &devices);

		if(devices.size() <= 0)
		{
			cerr << "No device for this platform" << endl;
		}
		cout << "Number of devices for this platform : " << devices.size() << endl;
		for(int j=0;j<devices.size();j++)
		{
			string name;
			string vendor;
			string version;
			string oclversion;
			devices[j].getInfo(CL_DEVICE_NAME, &name);
			devices[j].getInfo(CL_DEVICE_VENDOR, &vendor);
			devices[j].getInfo(CL_DEVICE_VERSION, &version);
			devices[j].getInfo(CL_DEVICE_OPENCL_C_VERSION, &oclversion);
			cout << "Device " << j+1 << endl << "Name : " << name << endl << "Vendor : " << vendor << endl << "Version : " << version << endl << "OpenCL Version : " << oclversion << endl << endl << endl;
		}

	}

	return 0;
}
