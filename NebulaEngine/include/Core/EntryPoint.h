#ifdef _WIN32

/**
 * \brief Create the application instance.
 *
 * This function is implemented by the client to return an instance of the application.
 * It is the main entry point for the application on Windows.
 *
 * \return Pointer to the created application instance.
 */
extern Nebula::Application* Nebula::CreateApplication();

/**
 * \brief Main entry point for the application on Windows.
 *
 * This is the main function that creates the application, runs it, and then cleans up.
 * It only compiles and runs on Windows (_WIN32).
 *
 * \param ac The number of command-line arguments.
 * \param av The array of command-line arguments.
 * \return int Exit code of the application.
 */
int main(int ac, char** av)
{
	auto app = Nebula::CreateApplication();
	app->Run();
	delete app;
}

#endif
