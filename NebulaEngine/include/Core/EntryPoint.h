#ifdef _WIN32

extern Nebula::Application* Nebula::CreateApplication();

int main(int ac, char** av)
{
	auto app = Nebula::CreateApplication();
	app->Run();
	delete app; 
}

#endif
