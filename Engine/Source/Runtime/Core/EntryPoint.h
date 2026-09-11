#pragma once

#ifdef FIREBOX_PLATFORM_WIN64

#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
#ifdef __cplusplus
}
#endif

#endif

#ifdef defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

extern Firebox::Application* Firebox::CreateApp();

int main(int argc, char** argv)
{
#ifdef defined(_MSC_VER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	Firebox::EngineContent::Init();
	FireboxEditor::EditorContent::Init();
	Firebox::Log::Init();
	auto app = Firebox::CreateApp();
	app->Run();
#ifdef defined(_MSC_VER)
	_CrtDumpMemoryLeaks();
#endif
	delete app;
}
