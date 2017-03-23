Temporary Directory (C++)
=========================

A stupidly simple way of creating temporary directories.

Example
-------

```c++
// example.cpp

#include <temporary-directory.hpp>
#include <iostream>

using namespace std;

int
main(int argc, char **argv)
{
  TemporaryDirectory tmpdir;

  string pathname = tmpdir("example.txt");
  cout << pathname << endl;

  return 0;
}
```

```sh
$ c++ -o example -I${prefix}/include -L${prefix}/lib -ltemporary-directory example.cpp
$ ./example
/var/folders/w6/rfd8_5t959nbyn_vzcfcy1p9hv1sn1/T//h8QvsRBN/example.txt
$ ls /var/folders/w6/rfd8_5t959nbyn_vzcfcy1p9hv1sn1/T//h8QvsRBN/
ls: /var/folders/w6/rfd8_5t959nbyn_vzcfcy1p9hv1sn1/T//h8QvsRBN/: No such file or directory
```

Installation
------------
Temporary Directory requires the following components:
1. [CMake >= 3.4.2](https://cmake.org)
2. C++11 Compiler
3. [Catch CMake](https://github.com/markcox80/catch-cmake)

The software can be built and installed using the following commands.

    $ mkdir /tmp/build
    $ cd /tmp/build
    $ cmake -DCMAKE_INSTALL_PREFIX=/tmp/install \
            -DCMAKE_PREFIX_PATH=/tmp/dependencies \
            -DCMAKE_BUILD_TYPE=Release \
            ${SOURCE_DIR}
    $ make
    $ make tests
    $ sudo make install

The Temporary directory library can be used in your CMake managed
project using the following commands.

   find_package(temporary-directory REQUIRED)

   add_library(are-you-talking-to-me are-you-talking-to-me.cpp)
   target_link_libraries(are-you-talking-to-me temporary-directory)