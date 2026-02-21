#pragma once

#ifdef FIREBOX_PLATFORM_WIN64

extern Firebox::Application* Firebox::CreateApp();

int main(int argc, char** argv)
{
	Firebox::Log::Init();
	auto app = Firebox::CreateApp();
	app->Run();
	delete app;
}

#endif