#pragma once

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef FIREBOX_PLATFORM_WIN64

extern Firebox::Application* Firebox::CreateApp();

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Firebox::EngineAssets::Init();
	FireboxEditor::Paths::Init();
	Firebox::Log::Init();
	auto app = Firebox::CreateApp();
	app->Run();
	_CrtDumpMemoryLeaks();
	delete app;
}

#endif