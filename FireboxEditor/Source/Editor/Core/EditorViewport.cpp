#include "EditorViewport.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"
#include "Engine/Input/Input.h"
#include "Engine/Utils/DebugTools.h"
#include "Engine/Utils/String.h"
#include "Engine/Rendering/Resources/PrimitiveShapes.h"

#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>

FireboxEditor::EditorViewport::EditorViewport() 
    : Layer("EditorLayer"), io(nullptr), m_SceneHierarchyPanel("Scene Hierarchy", m_EditorContext), m_PropertiesPanel("Properties", m_EditorContext),
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

	io->FontDefault = io->Fonts->AddFontFromFileTTF(FireboxEditor::Paths::Resource("Fonts/Ubuntu_Sans/static/UbuntuSans-Medium.ttf").string().c_str(), 17.0f);
    m_TransformPropertiesFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::Paths::Resource("Fonts/Ubuntu_Sans/static/UbuntuSans-SemiBold.ttf").string().c_str(), 17.0f);

    ImGui::FireboxEditorStyleClassic();

    Firebox::Window& window = Firebox::Application::Get().GetWindow();
    SDL_Window* sdlWindow = window.GetSDLWindow();
    SDL_GLContext glContext = window.GetGLContext();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(window.GetMainScale());
    style.FontScaleDpi = window.GetMainScale();
    style.TabRounding = 0.0f;
    io->ConfigDpiScaleFonts = true;
    io->ConfigDpiScaleViewports = true;
	io->ConfigDockingAlwaysTabBar = true;

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL3_InitForOpenGL(sdlWindow, glContext);
    ImGui_ImplOpenGL3_Init();

    m_MenuBar = FireboxEditor::MenuBar();

    m_AssetBrowser = FireboxEditor::AssetBrowser("Asset Browser");
    m_StatsPanel = FireboxEditor::StatsPanel("Stats");

    if (!m_TransformPropertiesFont) { return; }

    m_Framebuffer = Firebox::Framebuffer::Create({ 800, 600 });

    m_CurrentScene = CreateRef<Firebox::Scene>();

    m_EditorCamera = CreateRef<Firebox::PerspectiveCamera>(60.0f, 16.0f / 9.0f,
        0.1f, 1000.0f);
    m_EditorCamera->SetInputEnabled(false);

    m_CubeMesh = CreateRef<Firebox::Mesh>(Firebox::PrimitiveShapes::Cube().vertices, Firebox::PrimitiveShapes::Cube().indices);
    m_CubeEntity = m_CurrentScene->CreateEntity("Box");
    m_CubeEntity.AddComponent<MeshComponent>(m_CubeMesh);
    m_CubeEntity.AddComponent<MaterialComponent>(Firebox::Renderer3D::GetDefaultMaterial());
    m_CubeEntity.GetComponent<TransformComponent>().Position.x = -2.0f;

    m_BunnyModel = CreateRef<Firebox::StaticMesh>(FireboxEditor::Paths::Resource("Models/SM_StanfordBunny.obj").string());
    m_BunnyEntity = m_CurrentScene->CreateEntity("Bunny");
    m_BunnyEntity.AddComponent<StaticMeshComponent>(m_BunnyModel);
    m_BunnyEntity.GetComponent<TransformComponent>().Position.z = -1.0f;

    /*m_FireaxeModel = CreateRef<Firebox::StaticMesh>(FireboxEditor::Paths::Resource("Models/SM_Fireaxe.obj").string());
    m_FireaxeMaterial = CreateRef<Firebox::Material>(Firebox::Renderer3D::GetDefaultShader());
    m_FireaxeMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Fireaxe_BC.tga").string()));
    m_FireaxeMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_Fireaxe_BC.tga").string()));
    m_FireaxeModel->SetMaterial(0, m_FireaxeMaterial);
    m_FireaxeEntity = m_CurrentScene->CreateEntity("Fireaxe");
    m_FireaxeEntity.AddComponent<StaticMeshComponent>(m_FireaxeModel);*/

    for (auto& entity : m_CurrentScene->GetAllEntities())
    {
        String msg = "Entity Tag: " + entity.GetComponent<TagComponent>().Tag + ", Entity Id: " + Utils::ToString(entity.GetComponent<IdComponent>().GetId());
        FB_EDITOR_INFO(msg);
    }

    if (m_CubeEntity.HasComponent<TransformComponent>())
    {
        FB_EDITOR_WARN("I have a transform component!");
    }

    if (m_CubeEntity.HasComponent<TagComponent>())
    {
        FB_EDITOR_WARN("I have a tag component!");
    }

    m_DirectionalLight.Direction = Vector3(-0.2f, -1.0f, -0.3f);
    m_DirectionalLight.Color = Vector3(1.0f, 1.0f, 0.9f);

    m_PropertiesPanel.SetTransformPropertiesFont(m_TransformPropertiesFont);
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
    m_Framebuffer->BindFramebuffer();

    Firebox::Renderer3D::BeginScene(*m_EditorCamera, m_DirectionalLight);
    m_CurrentScene->OnUpdate(deltaTime);
    Firebox::Renderer3D::EndScene();
    Firebox::Renderer3D::SetGridSize(m_ViewportPanel.GetGridSize());
    Firebox::Renderer3D::SetActiveViewMode(static_cast<Firebox::ViewMode>(m_ViewportPanel.GetViewMode()));
    Firebox::Renderer3D::DrawGrid();

    m_Framebuffer->UnbindFramebuffer();
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

    // Gotta wrap up RenderPanel() calls in some layer so it gets called only once in here and renders every panel there is, instead of calling it separately  
    
    m_ViewportPanel.RenderViewport(m_Framebuffer, m_EditorCamera->GetViewMatrix(), m_EditorCamera->GetPerspective());

    m_ViewportPanel.SetMenuBarHeight(menuBarHeight);
    m_AssetBrowser.RenderPanel();
    m_SceneHierarchyPanel.RenderSceneHierarchyrPanel(m_CurrentScene);

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

