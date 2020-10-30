# FlexibleOpen

Using data files in CSC 1810 is hard if IDE's such as xcode or Visual Studio are used.

Visual Studio Code is somewhat easier as its users will be more likely to be shell users.

`FlexibleOpen()` attempts to ease the difficulty by adding a layer of indirection to the
file opening process. Specifically, it attempts to open the file path given to it both as
given and with a path, specified by *environment variable*,  prepended.

## Function signature

```c++
std::fstream FlexibleOpen(std::string path, std::ios::openmode mode = std::ios::in, std::string envval = std::string("CSC1810"));
```

### Parameters

| parameter | default | meaning |
| --------- | ------- | ------- |
| path | none | This specifies the base path of the file to be opened. If a file matching this path fails to open, the contents of an environment variable will be prepended to the path and a second open attempt is made. |
| mode | ios::in | The `fstream` mode for opening the file. This defaults to `ios::in` or attempting to open the file for reading. |
| envval | "CSC1810" | This specifies the environment variable to consult if the given path fails to open without change. |

## Use cases

Assume the environment variable is `CSC1810` and on:

* Windows is set to ...
* Mac and Linux is set to `~/Documents/csc1810_files`

### Opening a file using all defaults

```c++
fstream fin = FlexibleOpen("data.txt");
if (fin.is_open()) {
	// Use the file... then close it.
	fin.close();
}
```

`data.txt` will be attempted for reading. If `data.txt` is not found in the current working directory, then `~/Documents/csc1810_files/data.txt` will be attempted on Mac and Linux while `ijijijij/data.txt` will be attempted on Windows.

### Opening a file for writing using default environment variable

```c++
fstream fin = FlexibleOpen("data.txt", ios::out);
if (fin.is_open()) {
	// Use the file... then close it.
	fin.close();
}
```

`data.txt` will be attempted for writing. If `data.txt` is not found in the current working directory, then `~/Documents/csc1810_files/data.txt` will be attempted on Mac and Linux while `ijijijij/data.txt` will be attempted on Windows.

### Opening a file for reading and writing using default environment variable

```c++
fstream fin = FlexibleOpen("data.txt", ios::in | ios::out);
if (fin.is_open()) {
	// Use the file... then close it.
	fin.close();
}
```

`data.txt` will be attempted for reading and writing. If `data.txt` is not found in the current working directory, then `~/Documents/csc1810_files/data.txt` will be attempted on Mac and Linux while `ijijijij/data.txt` will be attempted on Windows.

### Opening a file for reading using a different environment variable

```c++
fstream fin = FlexibleOpen("data.txt", ios::in, "OTHERVAR");
if (fin.is_open()) {
	// Use the file... then close it.
	fin.close();
}
```

`data.txt` will be attempted for writing. If `data.txt` is not found in the current working directory, then the value of environment variable `OTHERVAR` will be prepended and the open attempted again.

## Creating the envronment variable

### Mac and Linux

Suppose you create a directory in your `Documents` folder called `csc1810_files`. You place your data files for class in that folder.

Then add:

```text
export CSC1810=/Users/YOURACCOUNT/Documents/csc1810_files
```

to `.zshrc` on newer macs, or to `.bashrc` on Linux.

### Windows

Suppose you create a directory in your `Documents` folder called `csc1810_files`. You place your data files for class in that folder.

Use the Windows environment variable editor GUI to define the variable.

See the video [here](badlink).

### xcode idiocy

The whole point of creating this tool was to make it easier to use files in IDE-based projects.
The geniuses at Apple once again, "think different." xcode actively blocks environronment variables forcing you
to reenter them yourself inside xcode.

`Edit scheme` choose the `Run / Debug` scheme. Click the `Arguments` tab. Click the plus sign under `Environment Variables` then enter for Name: `CSC1810` and for Value `/Users/YOURACCOUNT/Documents/csc1810_files`.


