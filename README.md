## Prerequisite
* conan
* cmake
* Visual Studio 2017(or later)

## Steps to compile

```bash
mkdir build
cd build
conan install .. -s build_type=Release
conan install .. -s build_type=Debug
cmake .. -G "Visual Studio 15 2017 Win64"
cmake --build . --config Release
cd src/Release
start qt-sdl-box2d.exe
```

