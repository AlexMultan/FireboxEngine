#include "Engine/Firebox.h"
#include "Core/EditorViewport.h"

class Editor : public Firebox::Application
{
public:

	Editor()
	{
		PushLayer(new FireboxEditor::EditorViewport());
		Firebox::Application::Get().GetRenderer3D().GetRendererAPI()->SetEditorViewportRendering(true);
	}

	~Editor()
	{

	}
};

Firebox::Application* Firebox::CreateApp()
{
	return new Editor;
}