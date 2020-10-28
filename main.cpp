#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

fstream FlexibleOpen(string path, ios::openmode mode = ios::in, string envval = string("CSC1810"));

/*	FlexibleOpen() will attempt to open the file given in `path` for reading (or
	writing depending on `mode`). The file will be attempted locally first - that
	is, as given in `path`. If this fails, the environment variable `envval` will
	be prepended to `path` and the open is attempted again.

	In zsh and bash, define the environment variable by:
	$ export VARNAME=path

	Put this in an rc file to make sticky. Real example:
	$ export CSC1810=~/Documents/csc1810_files

	In Windows, edit the environment variables directly using the UI. Note that
	Visual Studio must be restarted for it to pick up the newest values.
*/

fstream FlexibleOpen(string path, ios::openmode mode, string envval) {
	fstream file;
	// Check for local open.
	file.open(path, mode);
	if (!file.is_open()) {
		/*	Check environment variable. Unfortunately, this is done with platform
			specific code. On Mac, this can  be done using the oldest form of getenv.
			On Windows, getenv is deprecated.
		*/
		const char* envvar = nullptr;
		string s;
#if defined(_WIN64) || defined(WIN32)
		/*	On Windows, the safer getenv_s is used. It follows the "call me twice"
			pattern. The first time, call with a null destination buffer and only
			the space needed will be filled in. Then call a second time to actually
			get the value.
		*/
		size_t space_needed;
		getenv_s(&space_needed, nullptr, 0, envval.c_str());
		if (space_needed > 0) {
			s.resize(space_needed);
			getenv_s(&space_needed, (char*)s.c_str(), space_needed, envval.c_str());
			envvar = s.c_str();
		}
#else
		envvar = getenv(envval.c_str());
#endif
		if (strlen(envvar) > 0) {
			string p = string(envvar);
			if (p.at(p.size() - 1) != '/') {
				p = p + "/";
			}
			p = p + path;
			file.open(p, mode);
		}
	}
	return file;
}


int main(int argc, char* argv[]) {
	if (argc > 1) {
		fstream f = FlexibleOpen(string(argv[1]), ios::in);
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
