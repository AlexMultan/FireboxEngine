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
    m_ViewportPanel("Viewport", m_EditorContext), m_MenuBar(m_EditorContext), m_AssetBrowser("Content Browser", m_EditorContext)
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

	io->FontDefault = io->Fonts->AddFontFromFileTTF(FireboxEditor::EditorContent::Get("Fonts/Geist/static/Geist-Medium.ttf").string().c_str(), 17.0f);

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

    FireboxEditor::EditorUtils::Init(io);

    m_StatsPanel = FireboxEditor::StatsPanel("Stats");

    m_EditorCamera = CreateRef<Firebox::PerspectiveCamera>(60.0f, 16.0f / 9.0f,
        0.1f, 1000.0f);
    m_EditorCamera->SetInputEnabled(false);
    m_EditorCamera->SetPosition({ 0.0f, 2.0f, 1.0f });

    m_BunnyModel = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_StanfordBunny.obj").string());
    m_BunnyEntity = m_EditorContext.GetCurrentScene()->CreateEntity("Bunny");
    m_BunnyEntity.AddComponent<StaticMeshComponent>(m_BunnyModel);
    m_BunnyEntity.GetComponent<TransformComponent>().Position.y = 1.0f;
    m_BunnyEntity.GetComponent<TransformComponent>().Position.z = -1.0f;
    m_BunnyEntity.GetComponent<TransformComponent>().Scale = { 3.0f, 3.0f, 3.0f };

    m_JerrycanMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_Jerrycan.gltf").string());
    m_JerrycanMaterial = CreateRef<Firebox::Material>();
    m_JerrycanMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Jerrycan_BC.png").string()));
    m_JerrycanMaterial->SetNormalTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Jerrycan_N.png").string()));
    m_JerrycanMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Jerrycan_BC.png").string()));
    m_JerrycanMesh->SetMaterial(0, m_JerrycanMaterial);
    m_JerrycanEntity = m_EditorContext.GetCurrentScene()->CreateEntity("Jerrycan");
    m_JerrycanEntity.AddComponent<StaticMeshComponent>(m_JerrycanMesh);
    m_JerrycanEntity.GetComponent<TransformComponent>().Position.y = 0.5f;

#if 0
    m_CharacterModel = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/Ch15_nonPBR.dae").string());
    m_CharacterMaterial1 = CreateRef<Firebox::Material>();
    m_CharacterMaterial1->SetDiffuseTexture(Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Textures/Ch15_1001_Diffuse.png").string()));
    m_CharacterMaterial1->SetNormalTexture(Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Textures/Ch15_1001_Normal.png").string()));
    m_CharacterMaterial1->SetSpecularTexture(Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Textures/Ch15_1001_Specular.png").string()));
    m_CharacterModel->SetMaterial(0, m_CharacterMaterial1);

    m_CharacterEntity = m_EditorContext.GetCurrentScene()->CreateEntity("Soldier");
    m_CharacterEntity.AddComponent<StaticMeshComponent>(m_CharacterModel);
    m_CharacterEntity.GetComponent<TransformComponent>().Position.x = 2.0f;
    m_CharacterEntity.GetComponent<TransformComponent>().Position.y = 0.5f;
    m_CharacterEntity.GetComponent<TransformComponent>().Scale = { 0.01f, 0.01f, 0.01f };

    m_RunningAnim = Firebox::Animation(FireboxEditor::EditorContent::Get("Animations/Running.dae").string(), m_CharacterModel);
    m_CharacterAnimator = CreateRef<Firebox::Animator>(&m_RunningAnim);
    m_CharacterEntity.AddComponent<AnimatorComponent>(m_CharacterAnimator);
    m_CharacterEntity.GetComponent<AnimatorComponent>().Animator->PlayAnimation(&m_RunningAnim);
#endif

    m_LightEntity = m_EditorContext.GetCurrentScene()->CreateEntity("Light");
    m_LightEntity.AddComponent<DirectionalLightComponent>();
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

    if (m_EditorContext.GetSelectedEntity() && Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_DELETE))
        m_EditorContext.GetCurrentScene()->DestroyEntity(m_EditorContext.GetSelectedEntity());
}

void FireboxEditor::EditorViewport::OnRender(float deltaTime)
{
    Firebox::Renderer3D::BeginScene(*m_EditorCamera, m_LightEntity.GetComponent<DirectionalLightComponent>());
    m_EditorContext.GetCurrentScene()->OnUpdate(deltaTime);
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

    
    m_ViewportPanel.RenderViewport(m_EditorCamera->GetViewMatrix(), m_EditorCamera->GetPerspective());

    m_ViewportPanel.SetMenuBarHeight(menuBarHeight);
    m_AssetBrowser.RenderPanel();
    m_HierarchyPanel.RenderHierarchyrPanel(m_EditorContext.GetCurrentScene());

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

