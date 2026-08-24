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

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

extern Firebox::Application* Firebox::CreateApp();

int main(int argc, char** argv)
{

#ifdef defined(__linux__)
#include <cstdlib>
#include <unistd.h>

	if (getenv("__INTERNAL_GPU_FORCED") == nullptr)
	{
		setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 1);
		setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 1);
		
		setenv("DRI_PRIME", "1", 1);
		setenv("__INTERNAL_GPU_FORCED", "1", 1);

		execvp(argv[0], argv);
		std::cerr << "Failed to force dedicated GPU environment\n";
	}

#endif

#ifdef FIREBOX_PLATFORM_WIN64

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Firebox::EngineContent::Init();
	FireboxEditor::EditorContent::Init();
	Firebox::Log::Init();
	auto app = Firebox::CreateApp();
	app->Run();
	_CrtDumpMemoryLeaks();
	delete app;

#endif
}
