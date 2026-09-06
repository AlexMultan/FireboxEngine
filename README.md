<img width="1024" height="1024" alt="FireboxLogo_1024x1024" src="https://github.com/user-attachments/assets/8565e6a1-362b-4a57-8575-f7519a5c0839" />

# Early Development Notice
 
This engine is in **early, active development**. APIs will change, things will break, and documentation may lag behind the code. Contributions and feedback are welcome, but expect rough edges.
 
---
 
# Firebox Engine
 
A custom 3D game engine built from scratch in C++, featuring a standalone editor, an entity-component system, a deferred rendering pipeline with PBR, and a graphics-API agnostic rendering architecture.
 
## Features
 
### Editor
- Dedicated editor application with dockable ImGui panels
- Scene hierarchy panel with entity selection
- Details panel with component inspection and PBR material editing
- Asset browser with directory browser side panel
- Transform gizmos via ImGuizmo
- Stats panel showing FPS and ms/frame
- Integrated logging with log file saving
- Runtime entity spawning and destruction
### Entity Component System
- Built on top of [EnTT](https://github.com/skypjack/entt) with a UUID based entity identity system
- Core components: `TransformComponent`, `TagComponent`, `IdComponent`, `MeshComponent`, `MaterialComponent`, `StaticMeshComponent`, `SkyboxComponent`, `AnimatorComponent`, `DirectionalLightComponent`, `PointLightComponent`, `SpotLightComponent`, `PostProcessComponent`
### Rendering
- **Deferred shading pipeline** with fully functional G-Buffer (position, normal, albedo, material properties)
- **Physically Based Rendering (PBR)** with Cook Torrance BRDF, metallic/roughness workflow
- **Cascaded Shadow Maps (CSM)** with Poisson Disc shadow sampling
- **SSAO** (Screen Space Ambient Occlusion)
- **Skybox** rendering via dedicated render pass
- **Post processing** pipeline with configurable settings
- Debug visualization shaders: cascade levels, depth, albedo, metallic, roughness, normal, position
- Gamma correction
- Editor grid
### Material System
- Slot based material system for static meshes (Unreal style material slots)
- PBR material properties: albedo, normal, metallic, roughness, AO
- Basic color support, textures not required
- Material loading via Assimp
### Animation System (WIP)
- Skeletal animation with bone hierarchy extraction via Assimp
- Keyframe interpolation (linear for position/scale, Slerp for rotation)
- GPU skinning via vertex shader
- `AnimatorComponent` drives playback from `Scene::OnUpdate`
### Scene & Serialization
- Scene management tied into the ECS for entity lifecycle handling
- JSON scene serialization and deserialization
- Serialized components: `TransformComponent`, `TagComponent`, `IdComponent`, `DirectionalLightComponent`, `PointLightComponent`, `SpotLightComponent`, `StaticMeshComponent`, `Material`, `Texture`, `PostProcessComponent`
- Relative path serialization for asset references
- SaveScene and LoadScene
### Graphics API Abstraction
- Renderer abstracted behind a graphics API layer (`RendererAPI`)
- APIEnum bitfield flag support (e.g. `API_COLOR_BUFFER_BIT | API_DEPTH_BUFFER_BIT`)
### Engine Systems
- Event system with SDL event translation and input handling
- Layer system
- `Mathf` namespace: `Lerp`, `Slerp`, `Magnitude` and other math utilities
- Random number generator
- Dedicated GPU forcing on Windows (NvOptimus/AMD PowerXpress) and Linux (NV_PRIME/DRI_PRIME), for OpenGL
## Physics System (WIP)
- Powered by Nvidia PhysX
- Physics scene management with adding and removing physics actors at runtime
- BoxCollider class and BoxColliderComponent for rigid body collision
- BoxCollider debug visualization in the editor viewport (WIP, needs polishing)
## Dependencies
 
- SDL3
- Nvidia PhysX
- Dear ImGui
- ImGuizmo
- GLM
- spdlog
- EnTT
- stb
- Assimp
- nlohmann/json
- cereal
## Project Structure
 
```
FireboxEngine/
├── Engine/
│   ├── Source/
│   │   ├── Runtime/        # Core engine library (renderer, ECS, events, input, animation)
│   │   └── Editor/         # Standalone editor application (panels, dockspace, menu bar)
|   ├── Shaders/            # Engine GLSL shaders (.vert, .frag, .geom)
├── ThirdParty/             # Vendored source dependencies
├── Projects/
│   └── SampleGame/         # Sample game project
```
 
## Getting Started
 
### Prerequisites
 
- Windows x64 (cross platform support planned)
- C++20 compatible compiler (MSVC recommended, initial Clang support in progress)
- Visual Studio 2022/2026
### Build Instructions
 
1. Clone the repository:
```bash
git clone https://github.com/AlexMultan/FireboxEngine.git -b <branch name>
```
2. In the project root directory, run `GenerateVisualStudioFiles.bat`
3. Open the generated `.sln` in Visual Studio and build the solution.
4. Run `FireboxEditor`
## Supported Platforms
 
| Platform | Status |
|---|---|
| Windows x64 | Supported |
| Linux | Planned |
 
## Known Issues
 
- Cascaded shadow maps currently broken after transition to deferred shading pipeline
- Animation system functional but needs further work
## Future Plans
 
### Rendering
- Fix cascaded shadow maps in deferred pipeline
- Screen Space Reflections (SSR)
- Screen Space Global Illumination (SSGI)
- Subpixel Morphological Anti-Aliasing (SMAA)
- Image-based lighting (IBL)
- Bloom and other post processing effects
- Point light and spot light shadows
- GPU instancing and batching
- Particle system
### Graphics API
- Complete Vulkan backend via RHI layer (`VulkanSwapchain`, command buffers, render passes)
- Full RHI abstraction so renderer is completely API agnostic
- Eventually deprecate direct OpenGL calls in favor of RHI
### Physics
- SphereCollider, CapsuleCollider and ConvexCollider
- RigidBody component with mass, drag and constraints
- Static and dynamic physics actors
- Physics material (friction, restitution)
- Trigger volumes and collision callbacks
- Raycasting
- Character controller
### Engine
- Full asset manager with UUID based asset registry and asset handles
- Hot reload for shaders and assets
- Prefab system
- Lua scripting
- AngelScript scripting
- Native C++ scripting for performance critical behaviors
### Editor
- Content browser with asset drag and drop into viewport
- Play In Editor with pause and stop
- Editor preferences and project settings
- Undo/redo system
- Material Editor (Unreal Engine style)
### Platform
- Linux support
- Clang compiler full support
 
