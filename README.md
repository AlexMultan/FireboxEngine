# Early Development Notice
 
This engine is in **early, active development**. APIs will change, things will break, and documentation may lag behind the code. Contributions and feedback are welcome, but expect rough edges.
 
---

# Firebox Engine
 
A custom 3D game engine built from scratch in C++, featuring a standalone editor, an entity-component system, and a graphics-API-agnostic rendering pipeline.

## Features
 
- **Editor** - Dedicated editor application with dockable ImGui panels, a viewport, properties panel, debugger, and integrated logging
- **Entity Component System** - Built on top of [EnTT](https://github.com/skypjack/entt) with a UUID-based entity identity system and core components: `Transform`, `Tag`, `Mesh`, `Material`, `Id`, `StaticMesh`, `SkyboxComponent`, `AnimatorComponent` and `DirectionalLightComponent`
- **3D Renderer** - MVP transform pipeline, texture support, editor camera, delta time, and aspect-ratio-correct viewport rendering
- **Graphics-Agnostic API** - Renderer abstracted behind a graphics API layer for future backend flexibility
- **Event & Input System** - Event system with SDL event translation and input handling
- **Layer System** - Engine core organized around a composable layer stack
- **Scene System** - Scene management tied into the ECS for entity lifecycle handling

## Dependencies

- SDL3
- ImGui
- ImGuizmo
- GLM
- spdlog
- EnTT
- stb
- assimp
- json
- cereal

## Project Structure
 
```
├── Engine/Source/Runtime       # Core engine library (renderer, ECS, events, input, layers)
├── Engine/Source/Editor        # Standalone editor application (panels, dockspace, menu bar)
└── Projects/SampleGame/        # Game project launched from the editor
```

## Getting Started
 
### Prerequisites
 
- Windows (platform-specific editor features; cross-platform support not yet implemented)
- A C++20-compatible compiler (MSVC recommended)

### Build Instructions
 
1. Clone the repository:
```bash
   git clone https://github.com/AlexMultan/FireboxEngine.git -b <branch name>
```

2. In project root directory, run `GenerateVisualStudioFiles.bat`

3. Open the generated `.sln` in Visual Studio and build the solution.

4. Run the `FireboxEditor`

## Supported Platforms

- Windows x64
