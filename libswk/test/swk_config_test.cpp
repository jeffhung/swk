#include <swk/config.hpp>
#include <iostream>

using namespace std;

int main()
{
	const swk_info_t& si = swk_info();
	cout << "SWK " << si.version_major << "." << si.version_minor << endl;
	return 0;
}

