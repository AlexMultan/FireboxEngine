#include "EditorViewport.h"
#include "Core/Application.h"
#include "Core/Log.h"
#include "Input/Input.h"
#include "Utils/DebugTools.h"
#include "Utils/String.h"
#include "Rendering/Geometry/PrimitiveShapes.h"
#include "Core/EditorUtils.h"
#include "Rendering/Targets/Framebuffer.h"

#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>

FireboxEditor::EditorViewport::EditorViewport() 
    : Layer("EditorLayer"), io(nullptr), m_HierarchyPanel("Hierarchy", m_EditorContext), m_PropertiesPanel("Details", m_EditorContext),
    m_ViewportPanel("Viewport", m_EditorContext)
{
   
}

FireboxEditor::EditorViewport::~EditorViewport()
{
    
}

void FireboxEditor::EditorViewport::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	io->FontDefault = io->Fonts->AddFontFromFileTTF(FireboxEditor::Paths::Resource("Fonts/JetBrainsMono/JetBrainsMono-Bold.ttf").string().c_str(), 17.0f);
    m_TransformPropertiesFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::Paths::Resource("Fonts/JetBrainsMono/JetBrainsMono-Regular.ttf").string().c_str(), 17.0f);

    ImGui::FireboxEditorStyleClassic();

    Firebox::Window& window = Firebox::Application::Get().GetWindow();
    SDL_Window* sdlWindow = window.GetSDLWindow();
    SDL_GLContext glContext = window.GetGLContext();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(window.GetMainScale());
    style.FontScaleDpi = window.GetMainScale();
    style.TabRounding = 3.0f;
    io->ConfigDpiScaleFonts = true;
    io->ConfigDpiScaleViewports = true;
	io->ConfigDockingAlwaysTabBar = true;
    style.AntiAliasedFill = true;

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 9.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL3_InitForOpenGL(sdlWindow, glContext);
    ImGui_ImplOpenGL3_Init();

    m_MenuBar = FireboxEditor::MenuBar();

    m_AssetBrowser = FireboxEditor::AssetBrowser("Asset Browser");
    m_StatsPanel = FireboxEditor::StatsPanel("Stats");

    if (!m_TransformPropertiesFont) { return; }

    m_CurrentScene = CreateRef<Firebox::Scene>();

    m_EditorCamera = CreateRef<Firebox::PerspectiveCamera>(60.0f, 16.0f / 9.0f,
        0.1f, 1000.0f);
    m_EditorCamera->SetInputEnabled(false);
    m_EditorCamera->SetPosition({ 0.0f, 2.0f, 1.0f });

    m_FloorMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::Paths::Resource("Models/SM_Cube.obj").string());
    m_WoodMaterial = CreateRef<Firebox::Material>();
    m_WoodMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Wood_Planks_BC.png").string()));
    m_WoodMaterial->SetNormalTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Wood_Planks_N.png").string()));
    m_WoodMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Wood_Planks_BC.png").string()));
    m_FloorEntity = m_CurrentScene->CreateEntity("Floor");
    m_FloorEntity.AddComponent<StaticMeshComponent>(m_FloorMesh);
    m_FloorEntity.GetComponent<TransformComponent>().Scale = { 10.0f, 0.5f, 10.0f };
    m_FloorMesh->SetMaterial(0, m_WoodMaterial, 10.0f);

    m_BunnyModel = CreateRef<Firebox::StaticMesh>(FireboxEditor::Paths::Resource("Models/SM_StanfordBunny.obj").string());
    m_BunnyEntity = m_CurrentScene->CreateEntity("Bunny");
    m_BunnyEntity.AddComponent<StaticMeshComponent>(m_BunnyModel);
    m_BunnyEntity.GetComponent<TransformComponent>().Position.y = 1.0f;
    m_BunnyEntity.GetComponent<TransformComponent>().Position.z = -1.0f;
    m_BunnyEntity.GetComponent<TransformComponent>().Scale = { 3.0f, 3.0f, 3.0f };

    m_JerrycanMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::Paths::Resource("Models/SM_Jerrycan.gltf").string());
    m_JerrycanMaterial = CreateRef<Firebox::Material>();
    m_JerrycanMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Jerrycan_BC.png").string()));
    m_JerrycanMaterial->SetNormalTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Jerrycan_N.png").string()));
    m_JerrycanMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Jerrycan_BC.png").string()));
    m_JerrycanMesh->SetMaterial(0, m_JerrycanMaterial);
    m_JerrycanEntity = m_CurrentScene->CreateEntity("Jerrycan");
    m_JerrycanEntity.AddComponent<StaticMeshComponent>(m_JerrycanMesh);
    m_JerrycanEntity.GetComponent<TransformComponent>().Position.y = 0.5f;

    m_DirectionalLight = m_CurrentScene->CreateEntity("Directional Light");
    m_DirectionalLight.AddComponent<DirectionalLightComponent>();
    m_DirectionalLight.GetComponent<DirectionalLightComponent>().Direction = { -0.2f, -1.0f, -0.3f };
    m_DirectionalLight.GetComponent<DirectionalLightComponent>().Color = { 1.0f, 0.89f, 0.96f };

    for (auto& entity : m_CurrentScene->GetAllEntities())
    {
        String msg = "Entity Tag: " + entity.GetComponent<TagComponent>().Tag + ", Entity Id: " + Utils::ToString(entity.GetComponent<IdComponent>().GetId());
        FB_EDITOR_INFO(msg);
    }

    m_PropertiesPanel.SetTransformPropertiesFont(m_TransformPropertiesFont);
    FireboxEditor::EditorUtils::Init(io);
}

void FireboxEditor::EditorViewport::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

void FireboxEditor::EditorViewport::OnUpdate(float deltaTime)
{
    if (m_ViewportPanel.IsFocused() && Firebox::Input::IsMouseButtonDown(Firebox::FBK_MOUSE_BUTTON_RIGHT))
    {
        m_EditorCamera->SetInputEnabled(true);
        SDL_HideCursor();
    }
    else if (Firebox::Input::IsMouseButtonReleased(Firebox::FBK_MOUSE_BUTTON_RIGHT))
    {
        m_EditorCamera->SetInputEnabled(false);
        SDL_ShowCursor();
    }
    m_EditorCamera->OnUpdate(deltaTime);
    m_EditorCamera->SetCameraSpeed(m_ViewportPanel.GetCamaraSpeedParam());
    if(m_ViewportPanel.GetViewportSize().x > 0.0f && m_ViewportPanel.GetViewportSize().y > 0.0f)
        m_EditorCamera->SetAspectRatio(m_ViewportPanel.GetViewportSize().x / m_ViewportPanel.GetViewportSize().y);
}

void FireboxEditor::EditorViewport::OnRender(float deltaTime)
{
    Firebox::Renderer3D::BeginScene(*m_EditorCamera, m_DirectionalLight.GetComponent<DirectionalLightComponent>());
    m_CurrentScene->OnUpdate(deltaTime);
    Firebox::Renderer3D::EndScene();
    Firebox::Renderer3D::SetGridSize(m_ViewportPanel.GetGridSize());
    Firebox::Renderer3D::SetActiveViewMode(static_cast<Firebox::ViewMode>(m_ViewportPanel.GetViewMode()));
}

void FireboxEditor::EditorViewport::OnEvent(Firebox::Event& event)
{
    Firebox::Window& window = Firebox::Application::Get().GetWindow();
    window.SetRawEventCallback([](const void* rawEvent)
        {
            ImGui_ImplSDL3_ProcessEvent(static_cast<const SDL_Event*>(rawEvent));
        });
}

void FireboxEditor::EditorViewport::OnEditorUIRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    m_MenuBar.RenderMenuBar();
    float menuBarHeight = ImGui::GetFrameHeight();


    m_DockNodeFlags = ImGuiDockNodeFlags_None;
    m_WindowFlags = ImGuiWindowFlags_NoDocking;

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImVec2 rootPos = viewport->Pos;
    rootPos.y += menuBarHeight;
    ImGui::SetNextWindowPos(rootPos);
    ImVec2 rootSize = viewport->Size;
    rootSize.y -= menuBarHeight;
    ImGui::SetNextWindowSize(rootSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    m_WindowFlags |= ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
    m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1.0f, 0.0f));
    ImGui::Begin("Root", nullptr, m_WindowFlags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspaceID = ImGui::GetID("Root");
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), m_DockNodeFlags);
        
    }
    ImGui::End();

    
    m_ViewportPanel.RenderViewport(Firebox::Renderer3D::GetMainFramebuffer(), m_EditorCamera->GetViewMatrix(), m_EditorCamera->GetPerspective());

    m_ViewportPanel.SetMenuBarHeight(menuBarHeight);
    m_AssetBrowser.RenderPanel();
    m_HierarchyPanel.RenderHierarchyrPanel(m_CurrentScene);

    m_PropertiesPanel.RenderPanel();
    m_ConsolePanel.RenderPanel();
    m_StatsPanel.RenderPanel();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        Firebox::Window& backupMainWindow = Firebox::Application::Get().GetWindow();
        SDL_Window* backupSDLWindow = backupMainWindow.GetSDLWindow();
        SDL_GLContext backupCurrentContext = backupMainWindow.GetGLContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backupSDLWindow, backupCurrentContext);
    }
}

