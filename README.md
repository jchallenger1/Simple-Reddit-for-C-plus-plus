# Simple Reddit for C++
A simple api wrapper for listings, searching, and your profile <br />
This library uses Libcurl for networking, and Json for Modern C++ for parsing <br />
# Requirements
You must have curl installed in order to build Simple Reddit for C++. It can be download at <https://curl.haxx.se/download.html>, or if on linux using the command <br />
```
  sudo apt install curl
```
You must have CMake installed to create the static library. It can be downloaded at <https://cmake.org/download/>, or using the command under Debian
```
  sudo apt-get install cmake
```
# Quick Start
1.  Download all files
2.  Change directory to build
```
  cd build
```
3. Execute CMake
```
  cmake ..
```
4. Run the makefile
```
 make
```
This will create the static library called "libreddit.a".
To compile and run programs with the library run the command (if the file is main.cpp)
```
  g++ main.cpp -o test -L . -lreddit
```
