#define SDL_MAIN_HANDLED

#include <iostream>
#include "Application/Application.h"
#include "tracing/ConsoleTraceLineWriter.h"
#include "tracing/TraceWriter.h"

// You must include the command line parameters for your main function to be recognized by SDL
int main(int /*argc*/, char* /*argv*/[])
{
    tracing::ConsoleTraceLineWriter traceLineWriter{};
    tracing::TraceWriter traceWriter{ traceLineWriter };
    try
    {
        Application app(&traceWriter);

        app.Init();

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
