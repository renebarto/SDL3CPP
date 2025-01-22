#define SDL_MAIN_HANDLED

#include <iostream>
#include "Application.h"

// You must include the command line parameters for your main function to be recognized by SDL
int main(int /*argc*/, char* /*argv*/[])
{
    try
    {
        Application app;
        tracing::ConsoleTraceLineWriter traceLineWriter{};
        tracing::TraceWriter traceWriter{ traceLineWriter };

        app.Init(&traceWriter);

        app.Run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    
    // End the program
    return 0;
}
