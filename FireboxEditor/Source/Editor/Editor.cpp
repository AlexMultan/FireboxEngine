#include "Engine/Firebox.h"
#include "Core/EditorViewport.h"

class Editor : public Firebox::Application
{
public:

	Editor()
	{
		PushLayer(new FireboxEditor::EditorViewport());
		
	}

	~Editor()
	{

	}
};

Firebox::Application* Firebox::CreateApp()
{
	return new Editor;
}