#include "Firebox.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Components/Components.h"
#include "Editor/EnginePaths.h"

using namespace Firebox;

class GameLayer : public Layer
{
public:

	Entity player;
	Ref<StaticMesh> playerMesh = CreateRef<StaticMesh>("../Resources/EditorContent/Models/SM_Cube.glb");
	Entity ally;
	Ref<StaticMesh> allyMesh = CreateRef<StaticMesh>("../Resources/EditorContent/Models/SM_Sphere.glb");
	Entity enemy;
	Ref<StaticMesh> enemyMesh = CreateRef<StaticMesh>("../Resources/EditorContent/Models/SM_Cone.glb");

	Ref<Scene> forestLevel = CreateRef<Scene>();

	GameLayer() : Layer("Game")
	{
		forestLevel->SetSceneName("Forest");

		player = forestLevel->CreateEntity("Player");
		player.AddComponent<StaticMeshComponent>(playerMesh);

		ally = forestLevel->CreateEntity("Ally");
		ally.AddComponent<StaticMeshComponent>(allyMesh);

		enemy = forestLevel->CreateEntity("Enemy");
		enemy.AddComponent<StaticMeshComponent>(enemyMesh);
	}

	void OnAttach() override
	{
		FB_WARN("Application has started!");

		forestLevel->SaveScene(EngineContent::GetRoot("../Resources/EditorContent/Levels/ForestLevel.fbscene").string());
	}

	void OnUpdate(float deltaTime) override
	{
		if (Input::IsKeyDown(FBK_KEY_D))
		{
			player.GetComponent<TransformComponent>().Position.x += 10.0f * deltaTime;
		}

		if (Input::IsKeyClicked(FBK_KEY_L))
		{
			forestLevel->SaveScene(EngineContent::GetRoot("../Resources/EditorContent/Levels/ForestLevel.fbscene").string());
		}
	}

	void OnDetach() override
	{
		FB_WARN("Application has shutdown!");
	}

};

class Game : public Application
{
public:

	Game()
	{
		PushLayer(new GameLayer());
	}
	
	~Game()
	{
		
	}
};

Application* Firebox::CreateApp()
{
	return new Game;
}