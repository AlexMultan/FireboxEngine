#include "MenuBar.h"
#include "Input/Input.h"
#include "Scene/Entity.h"
#include "Components/CoreComponents.h"
#include "Components/RenderComponents.h"
#include "Rendering/Geometry/PrimitiveShapes.h"
#include "Rendering/Renderer3D.h"
#include "Editor/EditorPaths.h"
#include "Core/EditorUtils.h"
#include "UI/ImGuiHelpers.h"

#include <imgui.h>
#include <windows.h>
#include <commdlg.h>

FireboxEditor::MenuBar::MenuBar(FireboxEditor::EditorContext& context) : m_Context(context), m_Scene(nullptr)
{
    m_Context.AddSceneChangeListener([this](const Ref<Firebox::Scene>& newScene)
        {
            m_Scene = newScene;
        });
}

FireboxEditor::MenuBar::~MenuBar()
{
}

void FireboxEditor::MenuBar::RenderMenuBar()
{
    static bool showProjectSettings = false;

    if (showProjectSettings)
    {
        if (ImGui::Begin("Project Settings", &showProjectSettings))
        {
            ImGui::Text("In Progress");
            ImGui::End();
        }
    }

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
            {

            }
            if (ImGui::MenuItem("Open", "Ctrl+O"))
            {
                OPENFILENAMEW ofn;
                wchar_t szFile[260] = L"";

                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
                ofn.lpstrFilter =
                    L"Project (*.fbproject)\0*.fbproject\0"
                    L"All Files (*.*)\0*.*\0\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileNameW(&ofn))
                {
                    std::wstring selectedFile = ofn.lpstrFile;
                    int len = WideCharToMultiByte(CP_UTF8, 0, selectedFile.c_str(), -1, nullptr, 0, nullptr, nullptr);
                    String utf8Path(len, 0);
                    WideCharToMultiByte(CP_UTF8, 0, selectedFile.c_str(), -1, utf8Path.data(), len, nullptr, nullptr);

					FB_EDITOR_INFO("Successfully opened Firebox project!");
                }
            }

            if (ImGui::MenuItem("Save", "Ctrl+Shift+S"))
            {
                FB_EDITOR_INFO("Successfully saved Firebox project!");
            }

            if (ImGui::MenuItem("Exit"))
            {
                std::exit(EXIT_SUCCESS);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z"))
            {

            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false))
            {

            }
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "Ctrl+C"))
            {

            }
            if (ImGui::MenuItem("Paste", "Ctrl+V"))
            {

            }
            if (ImGui::MenuItem("Cut", "Ctrl+X"))
            {
				
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Project Settings"))
            {
                showProjectSettings = true;
            }
            ImGui::EndMenu();
        }

        static bool showSaveSceneWindow = false;
        static bool showNewSceneWindow = false;
		if (ImGui::BeginMenu("Scene"))
		{
            if (ImGui::MenuItem("New"))
            {
                showNewSceneWindow = true;
            }

			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
                showSaveSceneWindow = true;
			}

			if (ImGui::MenuItem("Load", "Ctrl+Shift+L"))
			{
                OPENFILENAMEW ofn;
                wchar_t szFile[260] = L"";

                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
                ofn.lpstrFilter =
                    L"Scene (*.fbscene)\0*.fbscene\0"
                    L"All Files (*.*)\0*.*\0\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileNameW(&ofn))
                {
                    std::wstring selectedFile = ofn.lpstrFile;
                    int len = WideCharToMultiByte(CP_UTF8, 0, selectedFile.c_str(), -1, nullptr, 0, nullptr, nullptr);
                    String utf8Path(len, 0);
                    WideCharToMultiByte(CP_UTF8, 0, selectedFile.c_str(), -1, utf8Path.data(), len, nullptr, nullptr);

                    try
                    {
                        Ref<Firebox::Scene> loadedScene = Firebox::Scene::LoadScene(utf8Path);
                        m_Context.SetCurrentScene(loadedScene);
                    }
                    catch (const std::exception& e) 
                    {
                        FB_EDITOR_ERROR("Failed to load scene: {}", e.what());
                    }
                    catch (...)
                    {
                        FB_EDITOR_ERROR("Failed to load scene: unknown exception");
                    }
                }
			}

			ImGui::EndMenu();
		}

        if (showNewSceneWindow)
        {
            ImVec2 screenSize = EditorUtils::GetScreenSize();
            ImVec2 windowSize = ImVec2(600.0f, 350.0f);
            ImVec2 windowPos = ImVec2((screenSize.x - windowSize.x) * 0.5f, (screenSize.y - windowSize.y) * 0.5f);
            ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

            ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

            if (ImGui::Begin("New Scene", &showNewSceneWindow, flags))
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                static float padding = 12.0f;
                static float thumbnailSize = 256.0f;
                float cellSize = thumbnailSize + padding;

                float panelWidth = ImGui::GetContentRegionAvail().x;
                int columnCount = (int)(panelWidth / cellSize);

                if (columnCount < 1)
                    columnCount = 1;

                ImGui::Columns(columnCount, 0, false);

                if (ImGui::ImageButton("EmptySceneButton", (ImTextureID)(uintptr_t)FireboxEditor::EditorUtils::GetEmptySceneThumbnail(),
                    { 256.0f, 256.0f }))
                {
                    
                }

                ImGui::TextWrapped("Empty Scene");
                ImGui::NextColumn();
                
                if (ImGui::ImageButton("BasicSceneButton", (ImTextureID)(uintptr_t)FireboxEditor::EditorUtils::GetBasicSceneThumbnail(),
                    { 256.0f, 256.0f }))
                {

                }

                ImGui::TextWrapped("Basic");
                ImGui::NextColumn();
                ImGui::PopStyleColor();
                ImGui::End();
            }
            ImGui::Columns(1);
        }

        if (showSaveSceneWindow)
        {
            ImVec2 screenSize = EditorUtils::GetScreenSize();
            ImVec2 windowSize = ImVec2(400.0f, 150.0f);
            ImVec2 windowPos = ImVec2((screenSize.x - windowSize.x) * 0.5f, (screenSize.y - windowSize.y) * 0.5f);
            ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

            ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

            if (ImGui::Begin("Save Scene", &showSaveSceneWindow, flags))
            {
                static char textBuffer[256] = "";
                ImGui::InputText("Scene Name", textBuffer, IM_ARRAYSIZE(textBuffer));
                ImGui::PushStyleColor(ImGuiCol_Button, { 0.12f, 0.85f, 0.12f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.27f, 0.92f, 0.27f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.058f, 0.56f, 0.058f, 1.0f });
                if (ImGui::ButtonCenteredOnLine("Confirm", 0.2f))
                {
                    String sceneName(textBuffer);
                    m_Context.GetCurrentScene()->SetSceneName(sceneName);
                    String destination = "Levels/" + sceneName + ".fbscene";
                    m_Context.GetCurrentScene()->SaveScene(FireboxEditor::EditorContent::Get(destination).string());
                    showSaveSceneWindow = false;
                }
                ImGui::PopStyleColor(3);
                ImGui::SameLine();
                if (ImGui::ButtonCenteredOnLine("Cancel", 0.5f))
                    showSaveSceneWindow = false;

                ImGui::End();
            }
        }

		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Empty Entity"))
			{
				Firebox::Entity emptyEntity = m_Context.GetCurrentScene()->CreateEntity("");
				m_Context.SetSelectedEntity(emptyEntity);
			}

			if (ImGui::BeginMenu("3D Objects"))
			{
				if (ImGui::MenuItem("Plane"))
				{
                    AddStaticMeshEntity("Plane", "Resources/EditorContent/Models/SM_Plane.glb");
				}

				if (ImGui::MenuItem("Cube"))
				{
                    AddStaticMeshEntity("Cube", "Resources/EditorContent/Models/SM_Cube.glb");
				}

				if (ImGui::MenuItem("Sphere"))
				{
                    AddStaticMeshEntity("Sphere", "Resources/EditorContent/Models/SM_Sphere.glb");
				}

				if (ImGui::MenuItem("Cylinder"))
				{
                    AddStaticMeshEntity("Cylinder", "Resources/EditorContent/Models/SM_Cylinder.obj");
				}

				if (ImGui::MenuItem("Cone"))
				{
                    AddStaticMeshEntity("Cone", "Resources/EditorContent/Models/SM_Cone.glb");
				}

				if (ImGui::MenuItem("Monkey"))
				{
                    AddStaticMeshEntity("Monkey", "Resources/EditorContent/Models/SM_Monkey.glb");
				}
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Directional Light"))
			{
				Firebox::Entity directionalLightEntity = m_Context.GetCurrentScene()->CreateEntity("Directional Light");
				m_Context.SetSelectedEntity(directionalLightEntity);
				directionalLightEntity.AddComponent<DirectionalLightComponent>();
				directionalLightEntity.GetComponent<DirectionalLightComponent>().Direction = { -0.2f, -1.0f, -0.3f };
				directionalLightEntity.GetComponent<DirectionalLightComponent>().Color = { 1.0f, 0.89f, 0.96f };
				Firebox::Renderer3D::SetDirectionalLight(directionalLightEntity.GetComponent<DirectionalLightComponent>());
			}

			if (ImGui::MenuItem("Point Light"))
			{
				Firebox::Entity pointLightEntity = m_Context.GetCurrentScene()->CreateEntity("Point Light");
				m_Context.SetSelectedEntity(pointLightEntity);
				pointLightEntity.AddComponent<PointLightComponent>();
				Firebox::Renderer3D::GetPointLights().emplace_back(pointLightEntity.GetComponent<PointLightComponent>());
			}

			if (ImGui::MenuItem("Spot Light"))
			{
				Firebox::Entity spotLightEntity = m_Context.GetCurrentScene()->CreateEntity("Spot Light");
				m_Context.SetSelectedEntity(spotLightEntity);
				spotLightEntity.AddComponent<SpotLightComponent>();
				Firebox::Renderer3D::GetSpotLights().emplace_back(spotLightEntity.GetComponent<SpotLightComponent>());
			}

			if (ImGui::MenuItem("Skybox"))
			{
                Firebox::Entity entity = m_Context.GetCurrentScene()->CreateEntity("Skybox");
                Ref<Firebox::Skybox> skybox = CreateRef<Firebox::Skybox>();
                m_Context.SetSelectedEntity(entity);
                entity.AddComponent<SkyboxComponent>(skybox);
			}

			if (ImGui::MenuItem("Post Process Volume"))
			{
                Firebox::Entity entity = m_Context.GetCurrentScene()->CreateEntity("Post Process Volume");
                m_Context.SetSelectedEntity(entity);
                entity.AddComponent<PostProcessComponent>();
			}

			ImGui::EndMenu();
		}

        ImGui::EndMainMenuBar();
    }
}

void FireboxEditor::MenuBar::AddStaticMeshEntity(const String& name, const String& path)
{
    Firebox::Entity entity = m_Context.GetCurrentScene()->CreateEntity(name);
    m_Context.SetSelectedEntity(entity);
    Ref<Firebox::StaticMesh> staticMesh = CreateRef<Firebox::StaticMesh>(path);
    entity.AddComponent<StaticMeshComponent>(staticMesh);
}