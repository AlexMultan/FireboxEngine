#include "Firebox.h"
#include "Input/Input.h"

class ExampleLayer : public Firebox::Layer
{
public:

	Vector2 playerPosition = Vector2(0, 0);

	ExampleLayer() : Layer("Example")
	{

	}

	void OnAttach() override
	{
		FB_WARN("Application has started!");
	}

	void OnUpdate(float deltaTime) override
	{
		if (Firebox::Input::IsMouseButtonDown(Firebox::FBK_MOUSE_BUTTON_RIGHT))
		{
			FB_INFO("Right mouse button is pressed!");
		}

		if (Firebox::Input::IsKeyDown(Firebox::FBK_KEY_E))
		{
			FB_TRACE("Pressing E");
		}

		if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_SPACE))
		{
			playerPosition.y += 15.0f;
			FB_INFO("Key Space Clicked or otherwise Jump action!");
			FB_INFO(playerPosition.y);
		}
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