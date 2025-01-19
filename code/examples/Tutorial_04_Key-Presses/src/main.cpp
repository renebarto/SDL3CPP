#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include "App.h"
#include "SDL3CPP/Events.h"

using namespace SDL3CPP;

int main(int /*argc*/, char * /*args*/[])
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

        // Set default current surface
        app.SelectCurrentImage(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);

        // Hack to get window to stay up
        Event e;
        bool quit = false;
        while (quit == false)
        {
            while (Events::Poll(e))
            {
                // User requests quit
                if (e.Type() == SDL_EVENT_QUIT)
                {
                    quit = true;
                }
                // User presses a key
                else if (e.Type() == SDL_EVENT_KEY_DOWN)
                {
                    // Select surfaces based on key press
                    switch (e.Key())
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_UP:
                        app.SelectCurrentImage(KeyPressSurfaces::KEY_PRESS_SURFACE_UP);
                        break;

                    case SDLK_DOWN:
                        app.SelectCurrentImage(KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
                        break;

                    case SDLK_LEFT:
                        app.SelectCurrentImage(KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
                        break;

                    case SDLK_RIGHT:
                        app.SelectCurrentImage(KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
                        break;

                    default:
                        app.SelectCurrentImage(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
                        break;
                    }
                }
            }

            // Apply the current image
            app.BlitCurrentImageToScreen();

        // Update the surface
        app.UpdateWindowSurface();
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
