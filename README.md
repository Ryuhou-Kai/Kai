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
    
 - Handle cmake presets
 - Supports clang-format 

## Development

### Debug/Testing

1. Create a private discord bot on the discord developer portal
2. Invite the bot to your private test server

For development, select one of the debug profiles and start the cmake, followed by a build.

### Release

- The Bot Token for the main server will be set active in a release cmake preset
- Rest is the same as in Debug
- Dont't use this for feature testing

>Tested with clion.

>[!WARNING]
>Known to have problems with code editors who don't provide a toolchain, e.g vs code


