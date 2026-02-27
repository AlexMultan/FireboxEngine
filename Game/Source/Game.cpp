#include "Engine/Firebox.h"
#include "Engine/Input/Input.h"

class ExampleLayer : public Firebox::Layer
{
public:

	ExampleLayer() : Layer("Example")
	{

	}

	void OnAttach() override
	{
		FIREBOX_WARN("Application has started!");
	}

	void OnUpdate() override
	{
		if (Firebox::Input::IsKeyPressed(Firebox::FBK_KEY_D))
		{
			FIREBOX_TRACE("D key is being pressed!");
		}
	}

	void OnDetach() override
	{
		FIREBOX_WARN("Application has shutdown!");
	}

};

class Game : public Firebox::Application
{
public:

	Game()
	{
		PushLayer(new ExampleLayer());
	}
	
	~Game()
	{
		
	}
};

Firebox::Application* Firebox::CreateApp()
{
	return new Game;
}