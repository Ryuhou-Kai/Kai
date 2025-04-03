<p align="center">
 <a href="#"><img src="https://img.shields.io/badge/c++-%2300427e.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white"/></a>
 <a href="#"><img src="https://img.shields.io/badge/CMake-%23eb2633.svg?style=for-the-badge&logo=cmake&logoColor=white"/></a>
</p>

# Kai

A small but nice Discord bot, for our discord server, does mostly small work and personalized commands that the big bots don't support, and a bit of quality of life shit

## Features

- Answers with a cat picture upon "!cat" /ᐠ ˵> ⩊ <˵マ

# Build/Contributing

## Dependencies

- cmake >=3.3
- A modern c++ compiler (one that can handle c++ 22)
- Git

Open the root CMakeLists.txt in a coder editor/IDE that can:
    
 1. Handle cmake presets
 2. Supports clang-format 
   
For development, select the debug profile and start the cmake, followed by a build.

>[!WARNING]
>The build will most likely fail, due to two missing includes in the d++ lib
>There is a patch for this in the “patches” folder, just go to the build/_deps/dpp-src directory and `git apply patch <path/to/patch>`.


