#include "Firebox.h"
#include "Input/Input.h"

class GameLayer : public Firebox::Layer
{
public:

	Vector2 playerPosition = Vector2(0, 0);

	GameLayer() : Layer("Game")
	{

	}

	void OnAttach() override
	{
		FB_WARN("Application has started!");
	}

	void OnUpdate(float deltaTime) override
	{
		
	}

	void OnDetach() override
	{
		FB_WARN("Application has shutdown!");
	}

};

class Game : public Firebox::Application
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

Firebox::Application* Firebox::CreateApp()
{
	return new Game;
}