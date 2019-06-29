# N Body Simulation
An N-body simulation approximates the motion of particles, often specifically particles that interact with one
another through some type of physical forces.

## Development
Project uses C++17 along with Qt5 and OpenGL 4.1. Read about following:
* [Qt5 Installation](https://www.qt.io/download)
* [OpenGL 4.1](https://www.khronos.org/opengl/wiki/Getting_Started)

### Compile and Build

```bash
mkdir bin
cd bin
cmake ../
make
```

### Coding Style
The project using LLVM coding style and `clang-format` is used to format the project. In order to format the whole
project, do the following:

```bash
clang-format -i **/*.cpp **/*.h
```
