# Early Development Notice
 
This engine is in **early, active development**. APIs will change, things will break, and documentation may lag behind the code. Contributions and feedback are welcome, but expect rough edges.
 
---

# Firebox Engine
 
A custom 3D game engine built from scratch in C++, featuring a standalone editor, an entity-component system, and a graphics-API-agnostic rendering pipeline.

## Features
 
- **Editor** - Dedicated editor application with dockable ImGui panels, a viewport, properties panel, debugger, and integrated logging
- **Entity Component System** - Built on top of [EnTT](https://github.com/skypjack/entt) with a UUID-based entity identity system and core components: `Transform`, `Tag`, `Mesh`, `Material`, `Id` and `Light`
- **3D Renderer** - MVP transform pipeline, texture support, orbiting editor camera, delta time, and aspect-ratio-correct viewport rendering
- **Graphics-Agnostic API** - Renderer abstracted behind a graphics API layer for future backend flexibility
- **Event & Input System** - Event system with SDL event translation and input handling
- **Layer System** - Engine core organized around a composable layer stack
- **Shader Pipeline** - Embedded GLSL shaders with a refactored, structured shader pipeline
- **Scene System** - Scene management tied into the ECS for entity lifecycle handling
- **Debugger Panel** - Includes a `STACK` macro for tracking stack-allocated objects and displaying their sizes at runtime

## Dependencies

- SDL3
- OpenGL / GLAD
- ImGui
- GLM
- spdlog
- EnTT
- stb
- assimp

## Project Structure
 
```
├── Engine/       # Core engine library (renderer, ECS, events, input, layers)
├── Editor/       # Standalone editor application (panels, dockspace, menu bar)
└── Game/         # Game project launched from the editor
```

## Getting Started
 
### Prerequisites
 
- Windows (platform-specific editor features; cross-platform support not yet implemented)
- A C++20-compatible compiler (MSVC recommended)

### Build Instructions
 
1. Clone the repository:
```bash
   git clone --recursive https://github.com/AlexMultan/FireboxEngine.git
```

To generate Visual Studio project files run 
``` GenerateProjectFiles.bat ```

3. Open the generated `.sln` in Visual Studio and build the solution.

4. In the Solution Explorer, right click on the FireboxEngine solution and select ``Build Solution`` or press ``Ctrl+Shift+B`` to build the solution.

5. Set FireboxEditor as a startup project if it isn't set already.

6. Run the `FireboxEditor`

## Supported Platforms

- Windows x64
