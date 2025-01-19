#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include "SDL3CPP/Events.h"

#include "App.h"

using namespace SDL3CPP;

int main(int /*argc*/, char */*argv*/[])
{
    try
    {
        App app;
        // Start up SDL and create window
        if (!app.Init())
        {
            std::cout << "Failed to initialize!" << std::endl;
            return 1;
        }
        // Load media
        if (!app.LoadMedia())
        {
            std::cout << "Failed to load media!" << std::endl;
            return 1;
        }
        // Apply the image
        app.BlitImageToScreen();

        // Update the surface
        app.UpdateWindowSurface();

        // Hack to get window to stay up
        Event e;
        bool quit = false;
        while (quit == false)
        {
            while (Events::Poll(e))
            {
                if (e.Type() == SDL_EVENT_QUIT)
                    quit = true;
            }
        }

        // Free resources and close SDL
        app.Close();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
