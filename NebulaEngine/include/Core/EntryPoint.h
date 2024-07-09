#ifdef _WIN32

extern Nebula::Engine* Nebula::CreateEngine();

int main(int ac, char** av)
{
	auto app = Nebula::CreateEngine();
	app->Run();
	delete app;
}

#endif
