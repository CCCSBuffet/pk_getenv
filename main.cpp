#include <iostream>
#include <fstream>
#include <cstdlib>
#include "fo.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc > 1) {
		fstream f = FlexibleOpen(string(argv[1]));
		if (f.is_open()) {
			cout << "File opened\n";
			f.close();
		}
		else {
			cout << "File failed to open\n";
		}
	}
	else {
		cout << "No argument given.\n";
	}
	return 0;
}
