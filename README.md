# Firebox Engine

A simple 2D game engine built in C++ using SDL3 and OpenGL, developed alongside a pixel art roguelike game.

## Features

- Layer stack system with event propagation
- SDL3 windowing and input
- OpenGL rendering backend
- ImGui debug overlay
- Logging system via spdlog

## Dependencies

- SDL3
- OpenGL / GLAD
- ImGui
- GLM
- spdlog

## Building

Firebox uses Premake5 as its build system. To generate Visual Studio project files run ``` GenerateProjectFiles.bat ```

Then open the generated solution in Visual Studio and build the solution.

## Platforms

- Windows x64
