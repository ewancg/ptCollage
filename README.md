A fork of [pxtone Collage](https://pxtone.org).

## Changes made
The code has been adapted to build with CMake to enable building with MinGW on Windows, and to ease future porting efforts.
It is not currently in a usable state because the XAudio2 client implementation is not compatible with the port.

Please see the [roadmap](ROADMAP.md).

## Dependencies
- zlib (provided)
- libpng (provided)
- libvorbis / OGG (provided)
- DirectX 9.0 (not supported in this fork, but awaiting an alternative)

All external dependencies were also provided with known working versions.

## Building
The CMakeLists.txt is fairly well documented and each option has a description. Use `cmake -LAH` to see all supported options.

It should support Visual Studio if opened in a version supporting CMake. If you want to use MSYS2 (which is recommended),
this command can be used to build all tools, assuming you have the accompanying packages installed:

`cmake -B build -S . -DBUNDLE_BUILD_DIR=release -DCMAKE_BUILD_TYPE=Release && cmake --build build --parallel`

```
mingw-w64-ucrt-x86_64-libogg
mingw-w64-ucrt-x86_64-libvorbis
mingw-w64-ucrt-x86_64-libpng
```

---

These are the respective versions for each pxtone project at the time of handoff (e.g., the version this is based off of).

|Program	|Version No.|
|--|--|
|ptCollage|0.9.3.2		|
|ptVoice	|0.9.4.1		|
|ptNoise	|0.9.3.1		|
|ptPlayer	|0.9.3.1		|

This is not pxtone engine -- the unmodified version of that can be found at [pxtone.org/developer](https://pxtone.org/developer), and the version used in this repository [here](https://github.com/ewancg/pxtone).
The original version of the code provided can be found at [here](https://www.cavestory.org/downloads/pxtoneProjectT-220401b-open230815c.zip). The source was provided by the original author of this software ([Studio Pixel](https://studiopixel.jp)) around January 5 2021 and explicit permission to release under the [zlib license](LICENSE) was given on July 21 2025.
